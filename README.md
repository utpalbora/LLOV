# LLOV:  A Fast Static Data-Race Checker for OpenMP Programs.  
(Make sure to first install `git lfs` before cloning the repo.
Binaries were compiled on Ubuntu 20.04.)
```
sudo apt-get install git-lfs
git-lfs install
```

LLOV stands for LLVM OpenMP Verifier.  It is a static data race detection 
tools in LLVM for OpenMP Programs.
LLOV can detect data races in OpenMP v4.5 programs written in C/C++ and FORTRAN.  

LLOV uses two static analysis techniques to detect data races at compile time.  
1. Polyhedral Dependence Analysis
2. May-Happen-in-Parallel Analysis

Unlike other race detection tool, LLOV can mark a region of code as Data 
Race Free.

## How to Run LLOV
If OpenMP is not installed on your system or the path is not properly set,
you can point to the included header & lib with additional compiler flags.
`-Iinclude/ -Llib/`

#### Running LLOV on OpenMP C/C++ code from clang
```
./bin/clang -Xclang -disable-O0-optnone -Xclang -load -Xclang ./lib/OpenMPVerify.so  \
  -fopenmp -g test/1.race1.c
./bin/clang++ -Xclang -disable-O0-optnone -Xclang -load -Xclang ./lib/OpenMPVerify.so  \
  -fopenmp -g test.cpp
```

#### Running LLOV on OpenMP C/C++ code from opt
```
./bin/clang -fopenmp -S -emit-llvm -g -Xclang -disable-O0-optnone \
  test/1.race1.c -o test.ll
./bin/opt -mem2reg -loop-simplify -simplifycfg test.ll -S -o test.ssa.ll
./bin/opt -load ./lib/OpenMPVerify.so -openmp-resetbounds -test.ssa.ll \
  -S -o test.rb.ll
./bin/opt -load ./lib/OpenMPVerify.so -openmp-forceinline -inline test.rb.ll \
  -S -o test.in.ll
./bin/opt -load ./lib/OpenMPVerify.so -openmp-split-basicblock test.in.ll \
  -S -o test.sb.ll
./bin/opt -load ./lib/OpenMPVerify.so \
  -disable-output \
  -openmp-verify-mhp \
  test.sb.ll
```

#### Running LLOV on OpenMP FORTRAN code
```
flang -fopenmp -S -emit-llvm -g test.f95 -o test.ll
./bin/opt -mem2reg -loop-simplify -simplifycfg test.ll -S -o test.ssa.ll
./bin/opt -load ./lib/OpenMPVerify.so -openmp-resetbounds -test.ssa.ll \
  -S -o test.rb.ll
./bin/opt -load ./lib/OpenMPVerify.so -openmp-forceinline -inline test.rb.ll \
  -S -o test.in.ll
./bin/opt -load ./lib/OpenMPVerify.so -openmp-split-basicblock test.in.ll \
  -S -o test.sb.ll
./bin/opt -load ./lib/OpenMPVerify.so \
  -disable-output \
  -openmp-verify-mhp \
  test.sb.ll
```
For more FORTRAN examples with known race conditions, check out our 
microbenchmark 
[DataRaceBench FORTRAN](https://github.com/utpalbora/drb_fortran)

## Authors
Utpal Bora <cs14mtech11017@iith.ac.in>.  

## Credits
The following people contirbuted to LLOV in different ways.  
Pankaj Kukreja &lt;cs15btech11029@iith.ac.in&gt;  
Santanu Das &lt;cs15mtech11018@iith.ac.in&gt;  
Shraiysh Vaishay &lt;cs17btech11050@iith.ac.in&gt;  
Saurabh Joshi [website](https://sbjoshi.github.io)  
Ramakrishna Upadrasta [website](https://www.iith.ac.in/~ramakrishna/)  
Sanjay Rajopadhye [website](https://www.cs.colostate.edu/~svr/)  

## Release
Source of LLOV will be released soon under BSD license.  

## Docker container
Docker Registry: [hub.docker.com](https://hub.docker.com/r/utpalbora/llvm/tags)  
repository: llvm  
tag: llov  

The docker image contians LLOV, along with the following race detection tools-  
TSan-LLVM, Archer, SWORD, Helgrind, and Valgrind DRD.  

There are three OpenMP benchmarks for experimentation-  
[DataRaceBench v1.2](https://github.com/LLNL/dataracebench),  
[DataRaceBench FORTRAN](https://github.com/utpalbora/drb_fortran), and  
[OmpSCR v2.0](https://github.com/utpalbora/OmpSCR_v2.0).  

## How to cite LLOV in a publication

```
@article{Bora/taco/2020,
  author = {Bora, Utpal and Das, Santanu and Kukreja, Pankaj and Joshi, Saurabh and Upadrasta, Ramakrishna and Rajopadhye, Sanjay},
  title = {{LLOV: A Fast Static Data-Race Checker for OpenMP Programs}},
  year = {2020},
  issue_date = {November 2020},
  publisher = {Association for Computing Machinery},
  address = {New York, NY, USA},
  volume = {17},
  number = {4},
  issn = {1544-3566},
  url = {https://doi.org/10.1145/3418597},
  doi = {10.1145/3418597},
  abstract = {In the era of Exascale computing, writing efficient parallel programs is indispensable, and, at the same time, writing sound parallel programs is very difficult. Specifying parallelism with frameworks such as OpenMP is relatively easy, but data races in these programs are an important source of bugs. In this article, we propose LLOV, a fast, lightweight, language agnostic, and static data race checker for OpenMP programs based on the LLVM compiler framework. We compare LLOV with other state-of-the-art data race checkers on a variety of well-established benchmarks. We show that the precision, accuracy, and the F1 score of LLOV is comparable to other checkers while being orders of magnitude faster. To the best of our knowledge, LLOV is the only tool among the state-of-the-art data race checkers that can verify a C/C++ or FORTRAN program to be data race free.},
  journal = {ACM Trans. Archit. Code Optim.},
  month = dec,
  articleno = {35},
  numpages = {26},
  keywords = {OpenMP, program verification, polyhedral compilation, static analysis, data race detection, shared memory programming}
}
```
```
@inproceedings{Bora-llvm-hpc-2021,
  author = {Bora, Utpal and Vaishay, Shraiysh and Joshi, Saurabh and Upadrasta, Ramakrishna},
  booktitle = {{2021 IEEE/ACM 7th Workshop on the LLVM Compiler Infrastructure in HPC (LLVM-HPC)}},
  title = {{OpenMP aware MHP Analysis for Improved Static Data-Race Detection}},
  year = {2021},
  volume = {},
  number = {},
  pages = {1-11},
  keywords = {},
  doi = {10.1109/LLVMHPC54804.2021.00006},
  series = {{LLVM-HPC '21}},
  issn = {},
  month = nov,
}
```

## Current Limitations
Following are the limitations of the current version of LLOV.  
* Does not support OpenMP tasks.
* Might produce FN when the same shared variable in a parallel construct is marked 
  as reduction in one nested construct but shared in another nested construct.
* Might produce FP for tiled and/or parallel code generated by 
  automatic code generation tools such as Pluto, Polly and PolyOPT.
* Might produce FP for code with mutual exclusion using locks.
* For some cases, source line number mapping in Polly is not preserved. 
  For those cases, race is flagged at the corresponding loop line number.

## Contact
If you have any query, please contact "Utpal Bora" &lt;cs14mtech11017@iith.ac.in&gt;.  
Please file a bug if you find the race checker is not working as required.  

Regards,  
Utpal

