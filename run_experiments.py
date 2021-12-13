import os;
import re;

import subprocess;
import numpy as np;

statistics = {
    "-hclimb":[]
}

sizes = {
    "-size_small",
    #"-size_middle",
    #"-size_large",
    #"-size_largest",
    #"-size_extralarge"
}

path = "/home/kacpernowak/Repos/MHE_PJ/build/"

#generate graph for each given size
#for size in sizes:
#    cmndName = str(path)+"MHE_PJ " + str(size) +  " -gen_only -gfile \""+str(path)+"generated_graph" + str(size).replace("-size","") + ".csv\""
#    os.popen(cmndName)

#run hill climb method for graphs of each size specified
for method_name in statistics:
    for size in sizes:
        for iteration in range(1,20):
            per_size_time = []
            per_size_quality = []
            for repeat in range(1,25):
                cmndName = str(path)+"/MHE_PJ "+" -print_result "+str(method_name)+" -gfile \""+str(path)+"/generated_graph"+str(size).replace("-size","")+".csv\""+" -iter "+str(iteration)+" -ofile \"hclimb_output"+str(size).replace("-size","")+".txt\""
                #print(cmndName)
                result = os.popen(cmndName)
                output = result.read().splitlines()
                st = float(output[0])
                sq = float(output[1])
                per_size_time.append(st)
                per_size_quality.append(sq)
            mean_time_per_iter_size = np.mean(per_size_time)
            mean_quality_per_iter_size = np.mean(per_size_quality)
            statistics[method_name].append([size, iteration, mean_time_per_iter_size, mean_quality_per_iter_size])

for method_name in statistics:
    print(statistics[method_name])