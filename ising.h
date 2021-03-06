#ifndef _ISING_H
#define _ISING_H

#include <iostream>
#include <string>
#include <vector>
class ising
{
private:
    struct neighbor
    {
        int spin;
        int ux, uy;
        int dx, dy;
        int lx, ly;
        int rx, ry;

        //bonds for worm
        int ubond, dbond, lbond, rbond;
    } **mark;
    //ira masha for worm
    int irax, iray, mashax, mashay;

    int size;
    int up_count;
    double up_rate;
    double T;
    double J;
    double H;
    /*
    neighbor is a struct for every lattice info storage
    and mark is a 2 dimensional neighbor pointer
     which contain all the map
    size is the size of the table
    m is the average spin
    T is the temperature
    h is the megnetic field
     */
public:
    ising(  int size_,
            double up_rate_,
            double T_,
            double J_,
            double H_);
    void refresh(   double T_,
                    double J_,
                    double H_);
    //refresh the object's parameters  as you wish!
    //will set all spins up
    void reset( double T_,
                double J_,
                double H_);
    //reset the object's parameters as you wish
    //will not reset spins' direction


    int get_size(); //size getting
    int get_up_count(); //up_count getting
    double get_up_rate(); //up_rate getting
    double get_T();
    double get_J();
    double get_H();
    double get_z(); //z = (exp(2J/T)−1)
    double get_energy(); //get the energy
    double get_m(); //get m = average(s)

    //Algorithms
    void metropolis(int steps);
    void swendsen_wang(int steps);
    void wolff(int steps);
    void worm(int steps);



    //output data methods
    void output_mark_pos(std::string filename);

    void output_mark_bond(std::string filename); //for worm
    void output_n_E_m(  int init_step,
                        int steps,
                        int per_step,
                        std::string filename);
    void output_T_E_C_m(int equi_step,
                        int ave_step,
                        int step_per_ave,
                        double T_start,
                        double T_end,
                        double delta_T,
                        std::string filename);
    void output_H_E_C_m(int equi_step,
                        int ave_step,
                        int step_per_ave,
                        double H_start,
                        double H_end,
                        double delta_H,
                        std::string filename);

    void output_T_H_E_C_m(int equi_step,
                          int ave_step,
                          int step_per_ave,
                          double T_start,
                          double T_end,
                          double delta_T,
                          double H_start,
                          double H_end,
                          double delta_H,
                          std::string filename);
    void output_H_loop_E_C_m(int equi_step,
                             int ave_step,
                             int step_per_ave,
                             double H_start,
                             double H_end,
                             double delta_H,
                             std::string filename);
};
#endif