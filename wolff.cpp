#include "ising.h"
#include <iostream>
#include <random>
#include <cstring>
#include <cmath>
void ising::wolff(int steps)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis_pos(0, size - 1);
    // for random position get
    // int order to get the X_n in Makov chain

    std::uniform_real_distribution<> dis_flip(0, 1);

    double p = 1 - std::exp(-2 * J / T);
    int x, y;  //pos


    /*
        struct chain  //set of mark points,
        {
            int pos[2];
            chain* next = NULL;
        } *C, *C_tail, *F_old, *F_old_tail, *F_new, *F_new_tail;
        C = new chain[1]; F_old = new chain[1];
        //C is the set of points to flip
        //F_old, F_new is for adding new points use
        for (int i = 0; i < steps; i++)
        {
            x = dis_pos(gen);
            y = dis_pos(gen);
            C = C_tail = new chain[1]; F_old = F_old_tail = new chain[1];
            C->pos[0] = x; C->pos[1] = y; C - next = NULL;
            F_old->pos[0] = x; F_old->pos[1] = y; F_old->next = NULL;
            while (F_old)
            {
                F_new = F_new_tail = NULL;
                for (chain * miao = F_old; miao; miao = miao->next;)
                {
                    if ( (mark[mark[miao->pos[0]][miao->pos[1]].ux][mark[miao->pos[0]][miao->pos[1]].uy].spin == mark[miao->pos[0]][miao->pos[1]].spin) && dis_flip(gen) < p)
                    {
                    }
                }
            }

        }
    */

    //std::cout << "This is worff algorithm" << std::endl;
}