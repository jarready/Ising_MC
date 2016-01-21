import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as ani
def mark_pos(filename):
    x = []
    y = []
    with open(filename,"r") as f:
        line = f.readline().split()
        size = line[1]
        line = f.readline().split()
        T = line[1]
        line = f.readline().split()
        J = line[1]
        line = f.readline().split()
        H = line[1]
        tail = "_"+size+"_T"+T+"_J"+J+"_H"+H
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
    plt.hist2d(x,y,bins = int(size))
    plt.xlim(0,int(size)-1)
    plt.ylim(0,int(size)-1)
    #plt.savefig(filename[:-15]+tail+".png")
    plt.savefig(filename[:-4]+".png")
    plt.close()

def group_mark_pos(step, per_step):
    i = 0
    while i<=step:
        x = []
        y = []
        filename = "./data/gif_dat/mark_pos_metropolis_"+str(i)+".dat"
        with open(filename,"r") as f:
            line = f.readline().split()
            size = line[1]
            line = f.readline().split()
            T = line[1]
            line = f.readline().split()
            J = line[1]
            line = f.readline().split()
            H = line[1]
            tail = "_"+size+"_T"+T+"_J"+J+"_H"+H
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
        plt.hist2d(x,y,bins = int(size))
        plt.xlim(0,int(size)-1)
        plt.ylim(0,int(size)-1)
        #plt.savefig(filename[:-15]+tail+".png")
        plt.savefig(filename[:-4]+".png")
        plt.close()
        i += per_step
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
        tail = "_"+size+"_T"+T+"_J"+J+"_H"+H
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
    plt.plot(n,E,marker = "o", linestyle = "--")
    plt.savefig(filename[:-20]+"n_E"+tail+".png")
    plt.close()

    plt.figure()
    plt.title("step_m")
    plt.xlabel("step")
    plt.ylabel("m")
    plt.ylim(-0.7,1.2)
    plt.plot(n,m,marker = "o", linestyle = "--")
    plt.savefig(filename[:-20]+"n_m"+tail+".png")
    plt.close()


def T_E_C_m(filename):
    T = []
    E = []
    C = []
    m = []
    with open(filename,"r") as f:
        line = f.readline().split()
        size = line[1]
        line = f.readline().split()
        J = line[1]
        line = f.readline().split()
        H = line[1]
        tail = "_"+size+"_J"+J+"_H"+H
        line = f.readline().split()
        while line:
            line = f.readline().split()
            if len(line)==4:
                T.append(float(line[0]))
                E.append(float(line[1]))
                C.append(1e5*float(line[2]))
                m.append(float(line[3]))
    plt.figure()
    plt.title("T_E")
    plt.xlabel("T")
    plt.ylabel("E")
    plt.plot(T,E,marker = "o", linestyle = "--")
    plt.savefig(filename[:-22]+"T_E"+tail+".png")
    plt.close()

    plt.figure()
    plt.title("T_C")
    plt.xlabel("T")
    plt.ylabel("C")
    plt.plot(T,C,marker = "o", linestyle = "--")
    plt.savefig(filename[:-22]+"T_C"+tail+".png")
    plt.close()


    plt.figure()
    plt.title("T_m")
    plt.xlabel("T")
    plt.ylabel("m")
    #plt.ylim(-0.2,1.2)
    plt.plot(T,m,marker = "o", linestyle = "--")
    plt.savefig(filename[:-22]+"T_m"+tail+".png")
    plt.close()


def H_E_C_m(filename):
    H = []
    E = []
    C = []
    m = []
    with open(filename,"r") as f:
        line = f.readline().split()
        size = line[1]
        line = f.readline().split()
        T = line[1]
        line = f.readline().split()
        J = line[1]
        tail = "_"+size+"_T"+T+"_J"+J
        line = f.readline().split()
        while line:
            line = f.readline().split()
            if len(line)==4:
                H.append(float(line[0]))
                E.append(float(line[1]))
                C.append(float(line[2]))
                m.append(float(line[3]))
    plt.figure()
    plt.title("H_E")
    plt.xlabel("H")
    plt.ylabel("E")
    plt.plot(H,E,marker = "o", linestyle = "--")
    plt.savefig(filename[:-22]+"H_E"+tail+".png")
    plt.close()

    plt.figure()
    plt.title("H_C")
    plt.xlabel("H")
    plt.ylabel("C")
    plt.plot(H,C,marker = "o", linestyle = "--")
    plt.savefig(filename[:-22]+"H_C"+tail+".png")
    plt.close()


    plt.figure()
    plt.title("H_m")
    plt.xlabel("H")
    plt.ylabel("m")
    plt.ylim(-1.2,1.2)
    plt.plot(H,m,marker = "o", linestyle = "--")
    plt.savefig(filename[:-22]+"H_m"+tail+".png")
    plt.close()

from mpl_toolkits.mplot3d import Axes3D
def T_H_E_C_m(filename):
    H = []
    T = []
    E = []
    C = []
    m = []
    with open(filename,"r") as f:
        line = f.readline().split()
        size = line[1]
        line = f.readline().split()
        J = line[1]
        tail = "_"+size+"_J"+J
        line = f.readline().split()
        while line:
            line = f.readline().split()
            if len(line)==5:
                H.append(float(line[0]))
                T.append(float(line[1]))
                E.append(float(line[2]))
                C.append(float(line[3]))
                m.append(float(line[4]))
    fig = plt.figure()
    ax = fig.gca(projection='3d')
    ax.plot(H,T,C,linestyle='None',marker = "o")
    plt.show()
    plt.close()


def main():
    group_mark_pos(10000,100)
    #mark_pos("./data/gif_dat/mark_pos_metropolis.dat")
    #n_E_m("./data/n_E_m_metropolis.dat")
    #T_E_C_m("./data/T_E_C_m_metropolis.dat")
    #H_E_C_m("./data/H_E_C_m_metropolis.dat")
    #H_E_C_m("./data/Loop_H_E_C_m_metropolis.dat")
    #T_H_E_C_m("./data/T_H_E_C_m_metropolis.dat")

if __name__ == "__main__":
    main()