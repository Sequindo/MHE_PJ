import os;
import re;

import subprocess;
import numpy as np;
import matplotlib.pyplot as plt

statistics = {
    "-hclimb":[]
}

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

#run hill climb method for graphs of each size specified
for method_name in statistics:
    for size in sizes:
        per_iteration_time = []
        per_iteration_quality = []
        for iteration in range(1,25):
            for repeat in range(1,25):
                per_repeat_time = []
                per_repeat_quality = []
                cmndName = str(path)+"/MHE_PJ "+" -print_result "+str(method_name)+" -gfile \""+str(path)+"/generated_graph"+str(size).replace("-size","")+".csv\""+" -iter "+str(iteration)+" -ofile \"hclimb_output"+str(size).replace("-size","")+".txt\""
                result = os.popen(cmndName)
                output = result.read().splitlines()
                st = float(output[0])
                sq = float(output[1])
                per_repeat_time.append(st)
                per_repeat_quality.append(sq)
            per_iteration_time.append(np.mean(per_repeat_time))
            per_iteration_quality.append(np.mean(per_repeat_quality))
        print(per_iteration_time)
        print(per_iteration_quality)
        plt.plot(range(1,25), per_iteration_time)
        plt.xlabel('Liczba iteracji')
        plt.ylabel('Średni czas algorytmu')
        plt.show()
        plt.plot(range(1,25), per_iteration_quality)
        plt.xlabel('Liczba iteracji')
        plt.ylabel('Ilość wyznaczonych wierzchołków')
        plt.show()

