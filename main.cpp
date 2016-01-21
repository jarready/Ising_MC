#include <iostream>
#include <ctime>
#include "ising.h"

int main()
{
  std::clock_t c_start = std::clock();
  //ising(int size_, double up_rate_, double T_, double J_, double H_);

  //anamation get
  ising miao(128, 0.2, 2.5, 1, 0);
  miao.metropolis(10000);
  std::string outputfile;

  int steps = 10000;
  int per_step = 100;
  for (int n = 0; n <= steps; n += per_step)
  {
    outputfile = "./data/gif_dat/mark_pos_metropolis_";
    outputfile += std::to_string(n);
    outputfile += ".dat";
    miao.output_mark_pos(outputfile);
    miao.wolff(per_step);
    std::cout << n << " " << steps << std::endl;
  }

  /*
  ising::ising(int size_,
           double up_rate_,
           double T_,
           double J_,
           double H_)
   */

  //ising miao(128, 0, 4, 1, 0.5);
  //miao.metropolis(100000000);
  //miao.output_mark_pos("./data/gif_dat/mark_pos_metropolis.dat");

  //void output_E_m(int init_step; int steps, int per_step, std::string filename);

  /*
  miao.output_n_E_m(0,
                    40000,
                    10,
                    "./data/n_E_m_metropolis.dat");
  */
  /*
  void ising::output_T_E_C_m(int equi_step,
                             int ave_step,
                             int step_per_ave,
                             double T_start,
                             double T_end,
                             double delta_T,
                             std::string filename)
  */

  /*
  miao.output_T_H_E_C_m(10000,
                        1000,
                        1000,
                        0.5,
                        5,
                        0.1,
                        - 5,
                        5,
                        0.2,
                        "./data/T_H_E_C_m_metropolis.dat");
  */
  /*
  miao.output_T_E_C_m(500000,
                      1000,
                      10000,
                      0.1, 4, 0.1,
                      "./data/T_E_C_m_metropolis.dat");
  */

  /*
  miao.output_H_E_C_m(500000,
                      1000,
                      10000,
                      -10, 10, 0.5,
                      "./data/H_E_C_m_metropolis.dat");
  */
  /*
  miao.output_H_loop_E_C_m(500000,
                           1000,
                           10000,
                           -10, 10, 0.5,
                           "./data/Loop_H_E_C_m_metropolis.dat");
  */

  std::clock_t c_end = std::clock();
  std::cout << "\n used " << (c_end - c_start) / CLOCKS_PER_SEC << " seconds";
  return 0;
}