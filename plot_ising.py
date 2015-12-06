import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as ani
def mark_pos(filename,size):
    x = []
    y = []
    with open(filename,"r") as f:
        line = f.readline().split()
        while line:
            line = f.readline().split()
            if len(line)==2:
                x.append(int(line[0]))
                y.append(int(line[1]))
    fig = plt.figure(figsize = (5,5))
    plt.title("mark_pos")
    plt.xlabel("x")
    plt.ylabel("y")
    #plt.plot(x,y,marker = ",", linestyle = "None")
    plt.hist2d(x,y,bins = size)
    plt.xlim(0,size-1)
    plt.ylim(0,size-1)
    plt.savefig(filename[:-3]+"png")
    plt.close()

def group_mark_pos():
    i = 0
    step = 100000
    size = 128
    while i<=step:
        mark_pos("/Users/Jarready/Desktop/Ising_MC/data/gif_dat/mark_pos_metropolis_"+str(i)+".dat",size)
        i += 1000
        if (step//i != step//(i+1)):
            print(step//i)

def n_E_m(filename):
    n = []
    E = []
    m = []
    with open(filename,"r") as f:
        line = f.readline().split()
        size = line[1]
        line = f.readline().split()
        T = line[1]
        line = f.readline().split()
        J = line[1]
        line = f.readline().split()
        H = line[1]
        tail = "_"+size+"_"+T+"_"+J+"_"+H
        line = f.readline().split()
        while line:
            line = f.readline().split()
            if len(line)==3:
                n.append(int(line[0]))
                E.append(float(line[1]))
                m.append(float(line[2]))
    plt.figure()
    plt.title("n_E")
    plt.xlabel("n")
    plt.ylabel("E")
    plt.plot(n,E)
    plt.savefig(filename[:-18]+"n_E"+tail+".png")
    plt.close()

    plt.figure()
    plt.title("n_m")
    plt.xlabel("n")
    plt.ylabel("m")
    plt.ylim(-1.2,1.2)
    plt.plot(n,m)
    plt.savefig(filename[:-18]+"n_m"+tail+".png")
    plt.close()


def T_E_m(filename):
    T = []
    E = []
    m = []
    with open(filename,"r") as f:
        line = f.readline().split()
        size = line[1]
        line = f.readline().split()
        J = line[1]
        line = f.readline().split()
        H = line[1]
        tail = "_"+size+"_"+J+"_"+H
        line = f.readline().split()
        while line:
            line = f.readline().split()
            if len(line)==3:
                T.append(float(line[0]))
                E.append(float(line[1]))
                m.append(float(line[2]))
    plt.figure()
    plt.title("T_E")
    plt.xlabel("T")
    plt.ylabel("E")
    plt.plot(T,E)
    plt.savefig(filename[:-20]+"T_E"+tail+".png")
    plt.close()

    plt.figure()
    plt.title("T_m")
    plt.xlabel("T")
    plt.ylabel("m")
    plt.ylim(-0.2,1.2)
    plt.plot(T,m)
    plt.savefig(filename[:-20]+"T_m"+tail+".png")
    plt.close()


def main():
    #group_mark_pos()
    #n_E_m("/Users/Jarready/Desktop/Ising_MC/data/E_m_metropolis.dat")
    T_E_m("/Users/Jarready/Desktop/Ising_MC/data/T_E_m_metropolis.dat")


if __name__ == "__main__":
    main()