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
    int *pos;  //pos
    int *u_nei, *d_nei, *l_nei, *r_nei; //neighbors store
    std::set<int*> C, F_old, F_new;

    for (int step = 0; step < steps; step++)//evolve steps times
    {
        pos = new int[2];
        pos[0] = dis_pos(); pos[1] = dis_pos();
        C.insert(pos); F_old.insert(pos);
        while (!F_old.empty())
        {
            F_new.clear();
            u_nei = new int[2]; d_nei = new int[2]; l_nei = new int[2]; r_nei = new int[2];
            for (std::set<int*>::iterator it = F_old.begin(); it != F_old.end(); it++)
            {
                u_nei[0] = mark[(*it)[0]][(*it)[1]].ux; u_nei[1] = mark[(*it)[0]][(*it)[1]].uy;
                d_nei[0] = mark[(*it)[0]][(*it)[1]].dx; d_nei[1] = mark[(*it)[0]][(*it)[1]].dy;
                l_nei[0] = mark[(*it)[0]][(*it)[1]].lx; l_nei[1] = mark[(*it)[0]][(*it)[1]].ly;
                r_nei[0] = mark[(*it)[0]][(*it)[1]].rx; r_nei[1] = mark[(*it)[0]][(*it)[1]].ry;

                if (mark[u_nei[0]][u_nei[1]].spin == mark[(*it)[0]][(*it)[1]].spin   && C.find(u_nei) != C.end() && dis_flip(gen) < p)
                {
                    F_new.insert(u_nei);
                    C.insert(u_nei);
                    u_nei = new int[2];
                    //if this neighbor is inserted,
                    //should give set a new pointer to it
                }

                if (mark[d_nei[0]][d_nei[1]].spin == mark[(*it)[0]][(*it)[1]].spin   && C.find(d_nei) != C.end() && dis_flip(gen) < p)
                {
                    F_new.insert(d_nei);
                    C.insert(d_nei);
                    d_nei = new int[2];
                }
                if (mark[l_nei[0]][l_nei[1]].spin == mark[(*it)[0]][(*it)[1]].spin   && C.find(l_nei) != C.end() && dis_flip(gen) < p)
                {
                    F_new.insert(l_nei);
                    C.insert(l_nei);
                    l_nei = new int[2];
                }
                if (mark[r_nei[0]][r_nei[1]].spin == mark[(*it)[0]][(*it)[1]].spin   && C.find(r_nei) != C.end() && dis_flip(gen) < p)
                {
                    F_new.insert(r_nei);
                    C.insert(r_nei);
                    r_nei = new int[2];
                }
                //end insert neighbor
            }
            F_old = F_new;
        }
        for (std::set<int*>::iterator it = C.begin(); it != C.end(); it++)
        {
            mark[(*it)[0]][(*it)[1]].spin = - mark[(*it)[0]][(*it)[1]].spin;
        }
    }
}