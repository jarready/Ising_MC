#include "ising.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>

void ising::output_mark_pos(std::string filename)
{
    int** pos;
    std::ofstream FILE(filename);
    if (FILE.is_open())
    {
        FILE << "size" << "\t" << get_size() << "\n";
        FILE << "T" << "\t" << get_T() << "\n";
        FILE << "J" << "\t" << get_J() << "\n";
        FILE << "H" << "\t" << get_H() << "\n";
        FILE << "x" << "\t" << "y" << "\n";
        for (int x = 0; x < size; x++)
        {
            for (int y = 0; y < size; y++)
            {
                if (mark[x][y].spin == 1)
                {
                    FILE << x << "\t" << y << "\n";
                }
            }
        }
    }
    FILE.close();
}

void ising::output_n_E_m(int init_step,
                         int steps,
                         int per_step,
                         std::string filename)
{
    std::ofstream FILE(filename);
    if (FILE.is_open())
    {
        metropolis(init_step);
        FILE << "size" << "\t" << get_size() << "\n";
        FILE << "T" << "\t" << get_T() << "\n";
        FILE << "J" << "\t" << get_J() << "\n";
        FILE << "H" << "\t" << get_H() << "\n";
        FILE << "step-init_step" << "\t" << "E" << "\t" << "m" << "\n";
        for (int n = 0; n <= steps; n += per_step)
        {
            FILE << n << "\t" << get_energy() << "\t" << get_m() << "\n";
            metropolis(per_step);
        }
    }
    FILE.close();
}

void ising::output_T_E_C_m(int equi_step,
                           int ave_step,
                           int step_per_ave,
                           double T_start,
                           double T_end,
                           double delta_T,
                           std::string filename)
{
    std::ofstream FILE(filename);
    if (FILE.is_open())
    {
        std::cout << "output_T_E_C_m: " << "\n";
        FILE << "size" << "\t" << get_size() << "\n";
        FILE << "J" << "\t" << get_J() << "\n";
        FILE << "H" << "\t" << get_H() << "\n";
        FILE << "T" << "\t" << "E" << "\t" << "C" << "\t" << "m" << "\n";
        for (double t = T_start; t < T_end; t += delta_T)
        {
            reset(t, J, H);
            metropolis(equi_step);

            double current_energy = 0,
                   ave_energy = 0,
                   ave_energy2 = 0,
                   C = 0,
                   ave_m = 0;
            for (int count = 0; count < ave_step; count++)
            {
                current_energy = get_energy();
                ave_energy += current_energy;
                ave_energy2 += std::pow(current_energy, 2);
                ave_m += get_m();
                metropolis(step_per_ave);
            }
            ave_energy = ave_energy / ave_step;
            ave_energy2 = ave_energy2 / ave_step;
            C = (ave_energy2 - std::pow(ave_energy, 2)) / std::pow(T, 2);
            ave_m = ave_m / ave_step;

            FILE << t << "\t" << ave_energy << "\t" << C << "\t" << ave_m << "\n";

            std::cout << "\n" << (t - T_start) / (T_end - T_start) * 100 << "%";
        }
    }
    FILE.close();
}

void ising::output_H_E_C_m(int equi_step,
                           int ave_step,
                           int step_per_ave,
                           double H_start,
                           double H_end,
                           double delta_H,
                           std::string filename)
{
    std::ofstream FILE(filename);
    if (FILE.is_open())
    {
        std::cout << "output_H_E_C_m: " << "\n";
        FILE << "size" << "\t" << get_size() << "\n";
        FILE << "T" << "\t" << T << "\n";
        FILE << "J" << "\t" << J << "\n";
        FILE << "H" << "\t" << "E" << "\t" << "C" << "\t" << "m" << "\n";
        for (double h = H_start; h < H_end; h += delta_H)
        {
            reset(T, J, h);
            metropolis(equi_step);

            double current_energy = 0,
                   ave_energy = 0,
                   ave_energy2 = 0,
                   C = 0,
                   ave_m = 0;
            for (int count = 0; count < ave_step; count++)
            {
                current_energy = get_energy();
                ave_energy += current_energy;
                ave_energy2 += std::pow(current_energy, 2);
                ave_m += get_m();
                metropolis(step_per_ave);
            }
            ave_energy = ave_energy / ave_step;
            ave_energy2 = ave_energy2 / ave_step;
            C = (ave_energy2 - std::pow(ave_energy, 2)) / std::pow(T, 2);
            ave_m = ave_m / ave_step;

            FILE << h << "\t" << ave_energy << "\t" << C << "\t" << ave_m << "\n";


            std::cout << "\n" << (h - H_start) / (H_end - H_start) * 100 << "%";
        }
    }
    FILE.close();
}
void ising::output_T_H_E_C_m(int equi_step,
                             int ave_step,
                             int step_per_ave,
                             double T_start,
                             double T_end,
                             double delta_T,
                             double H_start,
                             double H_end,
                             double delta_H,
                             std::string filename)
{
    std::ofstream FILE(filename);
    if (FILE.is_open())
    {
        std::cout << "output_T_H_E_C_m: " << "\n";
        FILE << "size" << "\t" << get_size() << "\n";
        FILE << "J" << "\t" << get_J() << "\n";
        FILE << "T" << "\t" << "H" << "\t" << "E" << "\t" << "C" << "\t" << "m" << "\n";
        for (double t = T_start; t < T_end; t += delta_T)
        {
            for (double h = H_start; h < H_end; h += delta_H)
            {
                reset(t, J, h);
                metropolis(equi_step);

                double current_energy = 0,
                       ave_energy = 0,
                       ave_energy2 = 0,
                       C = 0,
                       ave_m = 0;
                for (int count = 0; count < ave_step; count++)
                {
                    current_energy = get_energy();
                    ave_energy += current_energy;
                    ave_energy2 += std::pow(current_energy, 2);
                    ave_m += get_m();
                    metropolis(step_per_ave);
                }
                ave_energy = ave_energy / ave_step;
                ave_energy2 = ave_energy2 / ave_step;
                C = (ave_energy2 - std::pow(ave_energy, 2)) / std::pow(T, 2);
                ave_m = ave_m / ave_step;

                FILE << t << "\t" << h << "\t" << ave_energy << "\t" << C << "\t" << ave_m << "\n";

            }
            std::cout << "\n" << (t - T_start) / (T_end - T_start) * 100 << "%";
        }
    }
    FILE.close();
}

void ising::output_H_loop_E_C_m(int equi_step,
                                int ave_step,
                                int step_per_ave,
                                double H_start,
                                double H_end,
                                double delta_H,
                                std::string filename)
{
    std::ofstream FILE(filename);
    if (FILE.is_open())
    {
        std::cout << "output_H_E_C_m: " << "\n";
        FILE << "size" << "\t" << get_size() << "\n";
        FILE << "T" << "\t" << T << "\n";
        FILE << "J" << "\t" << J << "\n";
        FILE << "H" << "\t" << "E" << "\t" << "C" << "\t" << "m" << "\n";
        for (double h = H_start; h < H_end; h += delta_H)
        {
            reset(T, J, h);
            metropolis(equi_step);

            double current_energy = 0,
                   ave_energy = 0,
                   ave_energy2 = 0,
                   C = 0,
                   ave_m = 0;
            for (int count = 0; count < ave_step; count++)
            {
                current_energy = get_energy();
                ave_energy += current_energy;
                ave_energy2 += std::pow(current_energy, 2);
                ave_m += get_m();
                metropolis(step_per_ave);
            }
            ave_energy = ave_energy / ave_step;
            ave_energy2 = ave_energy2 / ave_step;
            C = (ave_energy2 - std::pow(ave_energy, 2)) / std::pow(T, 2);
            ave_m = ave_m / ave_step;

            FILE << h << "\t" << ave_energy << "\t" << C << "\t" << ave_m << "\n";


            std::cout << "\n up" << (h - H_start) / (H_end - H_start) * 100 << "%";
        }
        for (double h = H_end; h > H_start; h -= delta_H)
        {
            reset(T, J, h);
            metropolis(equi_step);

            double current_energy = 0,
                   ave_energy = 0,
                   ave_energy2 = 0,
                   C = 0,
                   ave_m = 0;
            for (int count = 0; count < ave_step; count++)
            {
                current_energy = get_energy();
                ave_energy += current_energy;
                ave_energy2 += std::pow(current_energy, 2);
                ave_m += get_m();
                metropolis(step_per_ave);
            }
            ave_energy = ave_energy / ave_step;
            ave_energy2 = ave_energy2 / ave_step;
            C = (ave_energy2 - std::pow(ave_energy, 2)) / std::pow(T, 2);
            ave_m = ave_m / ave_step;

            FILE << h << "\t" << ave_energy << "\t" << C << "\t" << ave_m << "\n";


            std::cout << "\n down" << (h - H_start) / (H_end - H_start) * 100 << "%";
        }
    }
    FILE.close();
}
