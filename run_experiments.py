import os;
import re;
import numpy as np;
import subprocess;

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

for size in sizes: #generate graph for each given size
    cmndName = "./MHE_PJ " + str(size) +  " -gen_only -gfile \"generated_graph" + str(size).replace("-size","") + ".csv\""
    os.popen(cmndName)