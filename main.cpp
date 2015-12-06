#include <iostream>
#include <ctime>
#include "ising.h"

int main()
{
    std::clock_t c_start = std::clock();
    //ising(int size_, double up_rate_, double T_, double J_, double H_);

    //anamation get
    /*
    ising miao(128, 0.2, 2, 1, 0);
    std::string outputfile;
    int steps = 100000;
    int per_step = 1000;
    for (int n = 0; n <= steps; n += per_step)
    {
        outputfile = "/Users/Jarready/Desktop/Ising_MC/data/gif_dat/mark_pos_metropolis_";
        outputfile += std::to_string(n);
        outputfile += ".dat";
        miao.output_mark_pos(outputfile);
        miao.metropolis(per_step);
    }
    */

    ising miao(128, 0, 0, 1, 0);
    //void output_E_m(int init_step; int steps, int per_step, std::string filename);
    //miao.output_n_E_m(0, 1000000, 100, "/Users/Jarready/Desktop/Ising_MC/data/n_E_m_metropolis.dat");

    //void output_T_E_m(int equi_step, double T_start, double T_end, double delta_T, std::string filename);
    miao.output_T_E_m(500000, 0, 4, 0.01, "/Users/Jarready/Desktop/Ising_MC/data/T_E_m_metropolis.dat");

    std::clock_t c_end = std::clock();
    std::cout << "\nused " << (c_end - c_start) / CLOCKS_PER_SEC << " seconds";
    return 0;
}