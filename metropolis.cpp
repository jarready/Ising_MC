#include "ising.h"
#include <iostream>
#include <random>
#include <cstring>
#include <cmath>
void ising::metropolis(int steps = 1)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis_pos(0, size - 1);
    // for random position get
    // int order to get the X_n in Makov chain

    std::uniform_real_distribution<> dis_flip(0, 1);

    //evolve for steps step

    int x, y;
    double old_local_energy, new_local_energy;
    for (int step = 0; step < steps; step++)
    {
        x = dis_pos(gen);
        y = dis_pos(gen);

        //calculate the old local_enerfy
        old_local_energy = 0;
        old_local_energy += -J * mark[x][y].spin * mark[mark[x][y].ux][mark[x][y].uy].spin;
        old_local_energy += -J * mark[x][y].spin * mark[mark[x][y].dx][mark[x][y].dy].spin;
        old_local_energy += -J * mark[x][y].spin * mark[mark[x][y].lx][mark[x][y].ly].spin;
        old_local_energy += -J * mark[x][y].spin * mark[mark[x][y].rx][mark[x][y].ry].spin;
        old_local_energy += -H * mark[x][y].spin;

        //flip this one
        mark[x][y].spin = -mark[x][y].spin;

        //reset up_count and up_rate
        if (mark[x][y].spin == 1)  up_count ++;
        else up_count--;
        up_rate = up_count / (size * size);

        //calculate the new local_enerfy
        new_local_energy = 0;
        new_local_energy += -J * mark[x][y].spin * mark[mark[x][y].ux][mark[x][y].uy].spin;
        new_local_energy += -J * mark[x][y].spin * mark[mark[x][y].dx][mark[x][y].dy].spin;
        new_local_energy += -J * mark[x][y].spin * mark[mark[x][y].lx][mark[x][y].ly].spin;
        new_local_energy += -J * mark[x][y].spin * mark[mark[x][y].rx][mark[x][y].ry].spin;
        new_local_energy += -H * mark[x][y].spin;


        //if new_local_energy is higher,
        //flip back with probability 1-exp(-(new-old)/kT)
        if (new_local_energy > old_local_energy)
        {
            if (dis_flip(gen) > std::exp(-(new_local_energy - old_local_energy) / T))
            {
                //set back mark[x][y]
                mark[x][y].spin = -mark[x][y].spin;

                //set back up_count and up_rate
                if (mark[x][y].spin == 1)  up_count ++;
                else up_count--;
                up_rate = up_count / (size * size);
            }
        }
        /*
        if (step % ( steps / 100) == 0)
        {
            std::cout << "\r\t\r" << step * 100 / steps;
        }
        */
    }//end of steps loop
}//end of metropolis