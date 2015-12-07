#include "ising.h"
#include <iostream>
#include <fstream>
#include <cstring>

void ising::output_mark_pos(std::string filename)
{
	int** pos;
	std::ofstream FILE(filename);
	if (FILE.is_open())
	{
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

void ising::output_n_E_m(int init_step, int steps, int per_step, std::string filename)
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


void ising::output_T_E_m(int equi_step, int ave_step, double T_start, double T_end, double delta_T, std::string filename)
{
	std::ofstream FILE(filename);
	if (FILE.is_open())
	{
		FILE << "size" << "\t" << get_size() << "\n";
		FILE << "J" << "\t" << get_J() << "\n";
		FILE << "H" << "\t" << get_H() << "\n";
		FILE << "T" << "\t" << "E" << "\t" << "m" << "\n";
		for (double t = T_start; t < T_end; t += delta_T)
		{
			refresh(t, J, H);
			metropolis(equi_step);

			double ave_energy = 0, ave_m = 0;
			for (int count = 0; count < ave_step; count++)
			{
				ave_energy += get_energy();
				ave_m += get_m();
				metropolis(100);
			}
			ave_energy = ave_energy / ave_step;
			ave_m = ave_m / ave_step;
			FILE << t << "\t" << ave_energy << "\t" << ave_m << "\n";
			std::cout << "\r\t" << (t - T_start) / (T_end - T_start) * 100 << "%";
		}
	}
	FILE.close();
}






