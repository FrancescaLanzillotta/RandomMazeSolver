#include <iostream>
#include <random>
#include <omp.h>
#include <chrono>
#include "Maze.h"
#include "Particle.h"
using namespace std;
using namespace chrono;

bool f(int n, int id){
    bool res = false;
    printf("Thread-%d el:%d\n", id, n);
    if (n == 13){
        printf("Out\n");
        res = true;
    }
    return res;
}

void s_solveMaze(Maze &m, vector<Particle> &particles, int ms=0, float backProb=0.7){


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
            for (auto &p: particles) {
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
    for (auto &c: solution) {
        m.setCellType(c, PATH);
    }

    auto exit = m.getExit();
#pragma omp for schedule(static)
    for (auto &p: particles) {
        if (p.getPosition() != exit){
            auto s = p.backtrack(solution, ms);
            p.followPath(s, ms);
        }

    }
#endif
}
int main() {

    int size = 51;
    int ms = 80;
    int nParticles = 500;

    random_device rd;  // a seed source for the random number engine
    mt19937 rng(rd()); // mersenne_twister_engine seeded with rd()
    // rng.seed(42);
    Maze m(size, rng);

    m.generateMaze(0);

    vector<Particle> particles;
    particles.reserve(nParticles);
    for(int i = 0; i < nParticles; i++){
        particles.emplace_back(m);
    };
    auto start = system_clock::now();
    s_solveMaze(m, particles, 0, 0.85);
    auto end = system_clock::now();
    auto seqElapsed = duration_cast<milliseconds>(end - start);
    printf("Seq time: %4.2f\n", (double)seqElapsed.count());
    // delayedCLS(5000);
    start = system_clock::now();
    p_solveMaze(m, particles, 100, 0, 0.85);
    end = system_clock::now();
    seqElapsed = duration_cast<milliseconds>(end - start);
    printf("Par time: %4.2f\n", (double)seqElapsed.count());

    bool out = false;
    vector<int> v;
    v.reserve(size);
    for (int i = 0; i < size; ++i) {
        v.emplace_back(i);

    }

#ifdef _OPENMP
    if(omp_get_cancellation() != 1)
        cout << "This code uses the OpenMP directive pragma omp cancel parallel in order to stop threads when the "
                "correct password is found. Make sure to set the environment variable OMP_CANCELLATION to TRUE. ";
#endif



//    while (!t){
//#pragma omp parallel shared(t)
//        {
//
//#pragma omp for schedule(static, 4) reduction(||: t)
//            for (auto &el: v) {
//                t |= f(el, omp_get_thread_num());
//                if (t){
//#pragma cancel for
//                }
//#pragma omp cancellation point for
//            }
//        }
//    }

//#ifdef _OPENMP
//#pragma omp parallel
//    {
//#pragma omp single nowait
//        {
//            while (!out){
//#pragma omp taskgroup
//                {
//                    for (auto &el: v) {
//#pragma omp task
//                        {
//                            out = f(el, omp_get_thread_num());
//                        if(out){
//#pragma omp cancel taskgroup
//                        }
//#pragma omp cancellation point taskgroup
//                        }
//                    }
//                }
//            }
//        }
//    }
//#endif



    return 0;

}

