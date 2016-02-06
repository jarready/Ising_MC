#include "ising.h"
#include <iostream>
#include <random>
#include <string>
#include <cmath>
void ising::worm(int steps)
{
    //set random functions
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis_pos(0, size - 1);
    std::uniform_int_distribution<> dis_move(0, 3);
    std::uniform_real_distribution<> dis_flip(0, 1);
    double pacc = J/T;

    for(int step=0;step<steps;step++)
    {
        if(irax == mashax && iray == mashay)
        {
            irax = mashax = dis_pos(gen);
            iray = mashay = dis_pos(gen);
        }//end if
        switch(dis_move(gen))
        {
            case 0:
            {
                if(mark[mashax][mashay].ubond==1)
                {
                    mark[mashax][mashay].ubond--;
                    mashay = mark[mashax][mashay].uy;
                    mark[mashax][mashay].dbond--;
                }
                else if(dis_flip(gen)<pacc)
                {
                    mark[mashax][mashay].ubond++;
                    mashay = mark[mashax][mashay].uy;
                    mark[mashax][mashay].dbond++;
                }
                break;
            }
            case 1:
            {
                if(mark[mashax][mashay].dbond==1)
                {
                    mark[mashax][mashay].dbond--;
                    mashay = mark[mashax][mashay].dy;
                    mark[mashax][mashay].ubond--;
                }
                else if(dis_flip(gen)<pacc)
                {
                    mark[mashax][mashay].dbond++;
                    mashay = mark[mashax][mashay].dy;
                    mark[mashax][mashay].ubond++;
                }
                break;
            }
            case 2:
            {
                if(mark[mashax][mashay].lbond==1)
                {
                    mark[mashax][mashay].lbond--;
                    mashax = mark[mashax][mashay].lx;
                    mark[mashax][mashay].rbond--;
                }
                else if(dis_flip(gen)<pacc)
                {
                    mark[mashax][mashay].lbond++;
                    mashax = mark[mashax][mashay].lx;
                    mark[mashax][mashay].rbond++;
                }
                break;
            }
            case 3:
            {
                if(mark[mashax][mashay].rbond==1)
                {
                    mark[mashax][mashay].rbond--;
                    mashax = mark[mashax][mashay].rx;
                    mark[mashax][mashay].lbond--;
                }
                else if(dis_flip(gen)<pacc)
                {
                    mark[mashax][mashay].rbond++;
                    mashax = mark[mashax][mashay].rx;
                    mark[mashax][mashay].lbond++;
                }
                break;
            }

        }//end switch


    }//end for loop
}