#include <iostream>
#include <cmath>
#include <random>
#include "ising.h"

ising::ising(int size_,
             double up_rate_,
             double T_,
             double J_,
             double H_)
{
    size = size_;
    up_rate = up_rate_;
    T = T_;
    J = J_;
    H = H_;
    up_count = 0;
    mark = new neighbor*[size];
    for (int i = 0; i < size; i++)
    {
        mark[i] = new neighbor[size];
    }//set mark

    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            mark[x][y].ux = x; mark[x][y].dx = x;
            mark[x][y].ly = y; mark[x][y].ry = y;

            mark[x][y].uy = (y + 1 + size) % size;
            mark[x][y].dy = (y - 1 + size) % size;
            mark[x][y].lx = (x - 1 + size) % size;
            mark[x][y].rx = (x + 1 + size) % size;

            mark[x][y].spin = -1;
        }
    }//make neighbors right

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, size - 1);
    //set random function

    int count = 0;
    int x, y;
    while (count < int(up_rate * size * size))
    {
        x = dis(rd); y = dis(rd);
        if (mark[x][y].spin == -1)
        {
            mark[x][y].spin = 1;
            count++;
            up_count++;
        }
    }//set up spin with up_rate;

    //std::cout << "end of init" << std::endl;
}//End of init


void ising::refresh(double T_, double J_, double H_)
{
    T = T_;
    J = J_;
    H = H_;
    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            mark[x][y].spin = 1;
        }
    }//make neighbors right

}

void ising::reset(double T_, double J_, double H_)
{
    T = T_;
    J = J_;
    H = H_;
}


int ising::get_size()
{
    return size;
}
int ising::get_up_count()
{
    return up_count;
}
double ising::get_up_rate()
{
    return 1.0 * up_count / (size * size);
}

double ising::get_T()
{
    return T;
}

double ising::get_J()
{
    return J;
}

double ising::get_H()
{
    return H;
}

double ising::get_z()
{
    return std::exp(2 * J / T) - 1;
}


double ising::get_energy()
{
    double energy = 0;
    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            energy += -J * mark[x][y].spin * mark[mark[x][y].ux][mark[x][y].uy].spin;
            energy += -J * mark[x][y].spin * mark[mark[x][y].dx][mark[x][y].dy].spin;
            energy += -J * mark[x][y].spin * mark[mark[x][y].lx][mark[x][y].ly].spin;
            energy += -J * mark[x][y].spin * mark[mark[x][y].rx][mark[x][y].ry].spin;
            energy += -4 * H * mark[x][y].spin;

        }
    }
    energy = energy / 4;
    energy = energy / (size * size);
    return energy;
}

double ising::get_m()
{
    double m = 0;
    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            m += mark[x][y].spin;
        }
    }
    m = m / (size * size);
    return m;
}



