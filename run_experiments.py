import os;

import numpy as np;
import matplotlib.pyplot as plt

sizes = {
    "-size_small",
    "-size_middle",
    "-size_large",
    "-size_largest",
    "-size_extralarge"
}

path = "/home/kacpernowak/Repos/MHE_PJ/build/"

#generate graph for each given size
#for size in sizes:
#    cmndName = str(path)+"MHE_PJ " + str(size) +  " -gen_only -gfile \""+str(path)+"generated_graph" + str(size).replace("-size","") + ".csv\""
#    os.popen(cmndName)

#run Stochastic Hill Climb method for graphs of each size specified
for size in sizes:
    per_iteration_time = []
    per_iteration_quality = []
    for iteration in range(1,25):
        for repeat in range(1,25):
            per_repeat_time = []
            per_repeat_quality = []
            cmndName = str(path)+"/MHE_PJ -print_result -hclimb -gfile \""+str(path)+"/generated_graph"+str(size).replace("-size","")+".csv\""+" -iter "+str(iteration)+" -ofile \"hclimb_output"+str(size).replace("-size","")+".txt\""
            result = os.popen(cmndName)
            output = result.read().splitlines()
            st = float(output[0])
            sq = float(output[1])
            per_repeat_time.append(st)
            per_repeat_quality.append(sq)
        per_iteration_time.append(np.mean(per_repeat_time))
        per_iteration_quality.append(np.mean(per_repeat_quality))
    plt.plot(range(1,25), per_iteration_time)
    plt.title('SHC - Czas/iteracje dla rozmiaru zadania: '+str(size).replace("-size",""))
    plt.xlabel('Liczba iteracji')
    plt.ylabel('Średni czas algorytmu')
    plt.show()
    plt.title('SHC - Jakość rozwiązania/iteracje dla rozmiaru zadania: '+str(size).replace("-size",""))
    plt.plot(range(1,25), per_iteration_quality)
    plt.xlabel('Liczba iteracji')
    plt.ylabel('Ilość wyznaczonych wierzchołków')
    plt.show()

#run Random Hill Climb method for graphs of each size specified
for size in sizes:
    per_iteration_time = []
    per_iteration_quality = []
    for iteration in range(1, 2000, 200):
        for repeat in range(1,5):
            per_repeat_time = []
            per_repeat_quality = []
            cmndName = str(path)+"/MHE_PJ -print_result -hclimb_random -burnout 3000 -gfile \""+str(path)+"/generated_graph"+str(size).replace("-size","")+".csv\""+" -iter "+str(iteration)+" -ofile \"hclimb_output"+str(size).replace("-size","")+".txt\""
            result = os.popen(cmndName)
            output = result.read().splitlines()
            st = float(output[0])
            sq = float(output[1])
            per_repeat_time.append(st)
            per_repeat_quality.append(sq)
        per_iteration_time.append(np.mean(per_repeat_time))
        per_iteration_quality.append(np.mean(per_repeat_quality))
    plt.plot(range(1, 2000, 200), per_iteration_time)
    plt.title('Random HC (burnout 3000) - Czas/iteracje dla rozmiaru zadania: '+str(size).replace("-size",""))
    plt.xlabel('Liczba iteracji')
    plt.ylabel('Średni czas algorytmu')
    plt.show()
    plt.title('Random HC (burnout 3000) - Jakość rozwiązania/iteracje dla rozmiaru zadania: '+str(size).replace("-size",""))
    plt.plot(range(1, 2000, 200), per_iteration_quality)
    plt.xlabel('Liczba iteracji')
    plt.ylabel('Ilość wyznaczonych wierzchołków')
    plt.show()

#run Tabu Search method for graphs of each size specified
for size in sizes:
    per_iteration_time = []
    per_iteration_quality = []
    for iteration in range(1, 2000, 200):
        for repeat in range(1,5):
            per_repeat_time = []
            per_repeat_quality = []
            cmndName = str(path)+"/MHE_PJ -print_result -tsearch -tsize 100 -gfile \""+str(path)+"/generated_graph"+str(size).replace("-size","")+".csv\""+" -iter "+str(iteration)+" -ofile \"hclimb_output"+str(size).replace("-size","")+".txt\""
            result = os.popen(cmndName)
            output = result.read().splitlines()
            st = float(output[0])
            sq = float(output[1])
            per_repeat_time.append(st)
            per_repeat_quality.append(sq)
        per_iteration_time.append(np.mean(per_repeat_time))
        per_iteration_quality.append(np.mean(per_repeat_quality))
    plt.plot(range(1, 2000, 200), per_iteration_time)
    plt.title('Tabu search (rozmiar tabu 100) - Czas/iteracje dla rozmiaru zadania: '+str(size).replace("-size",""))
    plt.xlabel('Liczba iteracji')
    plt.ylabel('Średni czas algorytmu')
    plt.show()
    plt.title('Tabu search (rozmiar tabu 100) - Jakość rozwiązania/iteracje dla rozmiaru zadania: '+str(size).replace("-size",""))
    plt.plot(range(1, 2000, 200), per_iteration_quality)
    plt.xlabel('Liczba iteracji')
    plt.ylabel('Ilość wyznaczonych wierzchołków')
    plt.show()