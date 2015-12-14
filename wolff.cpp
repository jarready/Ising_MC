#include "ising.h"
#include <iostream>
#include <random>
#include <string>
#include <cmath>
#include <set>
void ising::wolff(int steps)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis_pos(0, size - 1);
    // for random position get
    // int order to get the X_n in Makov chain

    std::uniform_real_distribution<> dis_flip(0, 1);

    double p = 1 - std::exp(-2 * J / T);
    int u_x, u_y, d_x, d_y, l_x, l_y, r_x, r_y; //neighbors store
    int x, y;
    std::set<int> C, F_old, F_new;
    //store pos info use int
    //x*size + y
    for (int step = 0; step < steps; step++)//evolve steps times
    {
        x = dis_pos(gen); y = dis_pos(gen);
        C.insert(x * size + y); F_old.insert(x * size + y);
        while (!F_old.empty())
        {
            F_new.clear();
            for (std::set<int>::iterator it = F_old.begin(); it != F_old.end(); it++)
            {
                u_x = mark[(*it) / size][(*it) % size].ux; u_y = mark[(*it) / size][(*it) % size].uy;
                d_x = mark[(*it) / size][(*it) % size].dx; d_y = mark[(*it) / size][(*it) % size].dy;
                l_x = mark[(*it) / size][(*it) % size].lx; l_y = mark[(*it) / size][(*it) % size].ly;
                r_x = mark[(*it) / size][(*it) % size].rx; r_y = mark[(*it) / size][(*it) % size].ry;

                if (mark[u_x][u_y].spin == mark[(*it) / size][(*it) % size].spin   && C.find(u_x * size + u_y) == C.end() && dis_flip(gen) < p)
                {
                    F_new.insert(u_x * size + u_y);
                    C.insert(u_x * size + u_y);
                    //if this neighbor is inserted,
                    //should give set a new pointer to it
                }

                if (mark[d_x][d_y].spin == mark[(*it) / size][(*it) % size].spin   && C.find(d_x * size + d_y) == C.end() && dis_flip(gen) < p)
                {
                    F_new.insert(d_x * size + d_y);
                    C.insert(d_x * size + d_y);
                }
                if (mark[l_x][l_y].spin == mark[(*it) / size][(*it) % size].spin   && C.find(l_x * size + l_y) == C.end() && dis_flip(gen) < p)
                {
                    F_new.insert(l_x * size + l_y);
                    C.insert(l_x * size + l_y);
                }
                if (mark[r_x][r_y].spin == mark[(*it) / size][(*it) % size].spin   && C.find(r_x * size + r_y) == C.end() && dis_flip(gen) < p)
                {
                    F_new.insert(r_x * size + r_y);
                    C.insert(r_x * size + r_y);
                }
                //end insert neighbor
            }
            F_old = F_new;
        }
        for (std::set<int>::iterator it = C.begin(); it != C.end(); it++)
        {
            //std::cout << (*it)[0] << " " << (*it)[1] << " " << mark[(*it) / size][(*it) % size].spin << "\n";
            mark[(*it) / size][(*it) % size].spin = - mark[(*it) / size][(*it) % size].spin;
        }
    }
}