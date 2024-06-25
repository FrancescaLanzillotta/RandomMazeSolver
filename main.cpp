#include <iostream>
#include <random>
#include <omp.h>
#include <chrono>
#include <fstream>
#include <filesystem>
#include "Maze.h"
#include "Particle.h"
using namespace std;
using namespace chrono;


template<typename T>
static string toString(const vector<T>& v) {
    string s = "[";
    for(int i = 0; i < v.size(); i++){
        s += to_string(v[i]);
        if (i < v.size() - 1)
            s += ", ";
        else
            s += "]";
    }
    return s;
}
void s_solveMaze(Maze &m, vector<Particle> &particles, int ms= 0, float backProb= 0.7){

    // move particles randomly until one reaches the exit
    bool out = false;
    vector<pair<int, int>> solution;
    while (!out){
        for(auto& p : particles){
            p.randMove(false, backProb);
            if (p.getPosition() == m.getExit()){
                out = true;
                solution = p.getPath();
                break;
            }
        }
        if (ms > 0){
            delayedCLS(ms);
            cout << m.toString();
        }

    }

    // set all cells in the solution as path
    for (auto c : solution){
        m.setCellType(c, PATH);
    }

    auto exit = m.getExit();
    for (auto &p: particles) {
        if (p.getPosition() != exit){
            auto s = p.backtrack(solution, ms);
            p.followPath(s, ms);
        }

    }
//    while(m.getParticles(m.getExit()) < particles.size()){    // while not all particles are out
//        for(auto& p : particles){
//            if(p.getPosition() != m.getExit()){
//                if (m.getCellType(p.getPosition()) != PATH){    //backtrack to path
//                    auto path = p.getPath();
//                    p.move(path[path.size() - 2], false);
//                } else if (!p.getToExit().empty()){     //follow solution to exit
//                    auto ex = p.getToExit();
//                    p.move(ex.front(), false);
//                    ex.pop_front();
//                    p.setToExit(ex);
//                } else {
//                    int index = 0;                  // find where the particle is on the path
//                    for(int i = 0; i < solution.size(); i++){
//                        if(p.getPosition() == solution[i]){
//                            index = i;
//                            break;
//                        }
//                    }
//                    p.setToExit(deque<pair<int, int>>(solution.begin() + index, solution.end()));
//                }
//            }
//        }
//        if (ms > 0){
//            delayedCLS(ms);
//            cout << m.toString();
//        }
//    }

}

void p_solveMaze(Maze &m, vector<Particle> &particles, int nThreads, int ms=0, float backProb=0.7){
    vector<pair<int, int>> solution;
    bool out = false;
#ifdef _OPENMP
    omp_set_num_threads(nThreads);
    while (!out){
#pragma omp parallel shared(out)
        {
#pragma omp for schedule(static) reduction(||: out)
            for (auto &p : particles) {
                // Particle p = particles[i];
                p.randMove(0, backProb);
                if (p.getPosition() == m.getExit()){
                    out = true;
                    solution = p.getPath();
#pragma cancel for
                }
#pragma omp cancellation point for
            }
        }
        if(ms > 0){
            delayedCLS(ms);
            cout << m.toString();
        }
    }

#pragma omp for schedule(static)
    for (int i = 0; i < solution.size(); i++) {
        m.setCellType(solution[i], PATH);
    }

    auto exit = m.getExit();
#pragma omp for schedule(static)
    for (int i = 0; i < particles.size(); i++) {
        Particle p = particles[i];
        if (p.getPosition() != exit){
            auto s = p.backtrack(solution, ms);
            p.followPath(s, ms);
        }

    }
#endif
}

int main() {
    /*
     * Better speedup   -> n particles >>>
		                -> size >>
     */

    int size = 81;
    int ms = 0;
    int nParticles = 75000;
    float backProb = 0.85;
    vector<int> nThreads = {2, 4, 8, 16, 32, 64, 128, 256};
    int nTests = 10;
    bool saveResults = true;
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y%m%d-%H%M%S");   // results files have a timestamp
    string resultsPath = R"(C:\Users\franc\CLionProjects\RandomMaze\results\results-)" + ss.str() + ".txt";

    printf("------------------ Experiments parameters ------------------\n");
    printf("Square maze size: %d\n", size);
    printf("Number of particles: %d\n", nParticles);
    printf("Backward probability removal: %4.2f\n", backProb);
    printf("Number of tests for each experiment: %d\n", nTests);




    random_device rd;  // a seed source for the random number engine
    mt19937 rng(rd()); // mersenne_twister_engine seeded with rd()
    // rng.seed(42);

    Maze m(size, rng);
    m.generateMaze(0);


    printf("\n------------------ Sequential Experiment ------------------\n");
    vector<double> sTimes = {};
    for(int i = 0; i < nTests; i++){
        printf("Test %d out of %d\n", i + 1, nTests);
        vector<Particle> particles;
        particles.reserve(nParticles);
        for(int k = 0; k < nParticles; k++){
            particles.emplace_back(m);
        }
        auto start = system_clock::now();
        s_solveMaze(m, particles, ms, backProb);
        auto end = system_clock::now();
        auto seqElapsed = duration_cast<milliseconds>(end - start);
        sTimes.push_back((double)seqElapsed.count());
        printf("Maze solved (%4.2f ms)\n", sTimes.back());
        m.resetMaze();
    }
    double sAvg = accumulate(sTimes.begin(), sTimes.end(), 0.0) / (double)sTimes.size();
    printf("Average time per experiment (ms): %4.2f\n", sAvg);


    printf("------------------ Parallel Experiment ------------------\n");
    vector<double> pAvg = {};
    vector<double> v1speedUps = {};
    // vector<double> v2speedUps = {};
    m.resetMaze();

    for (auto &threads: nThreads) {
        vector<double> pTimes = {};
        printf("\nThreads used: %d\n", threads);
        for (int i = 0; i < nTests; ++i) {
            vector<Particle> particles;
            particles.reserve(nParticles);
            for(int k = 0; k < nParticles; k++){
                particles.emplace_back(m);
            }
            printf("Test %d out of %d\n", i + 1, nTests);
            auto start = system_clock::now();
            p_solveMaze(m, particles, threads, ms, backProb);
            auto end = system_clock::now();
            auto parElapsed = duration_cast<milliseconds>(end - start);
            pTimes.push_back((double)parElapsed.count());
            printf("Maze solved (%4.2f ms)\n", pTimes.back());
            m.resetMaze();
        }
        pAvg.push_back(accumulate(pTimes.begin(), pTimes.end(), 0.0) / (double)pTimes.size());
        v1speedUps.push_back(sAvg / pAvg.back());
        //v2speedUps.push_back(v2sAvg/ pAvg.back());
        printf("\nAverage time per %d threads: %4.2f \n\n", threads, pAvg.back());
        printf("Speedup: %4.2fx\n", v1speedUps.back());

    }


    if (saveResults){
        ofstream resultsFile(resultsPath);  // creates and/or opens results file
        resultsFile << "------------------ Experiments parameters ------------------\n";
        resultsFile << "Square maze size: " <<  size;
        resultsFile << "\nNumber of particles: " <<  nParticles;
        resultsFile << "\nBackward probability removal: " << backProb;
        resultsFile << "\nNumber of tests for each experiment: " << nTests;
        resultsFile << "\n------------------ Sequential experiment v1------------------\n";
        resultsFile << "\nAverage time per experiment (ms): " << sAvg;
        resultsFile << "\n------------------ Parallel experiment ------------------\n";
        resultsFile << "\nNumber of threads tested: " << toString(nThreads);
        resultsFile << "\nAverage time per experiments (ms): " << toString(pAvg);
        resultsFile << "\nSpeedups : " << toString(v1speedUps);

    }

    return 0;

}

