# LLOV:  A Fast Static Data-Race Checker for OpenMP Programs.  

LLOV stands for LLVM OpenMP Verifier.  It is a static data race detection 
tools in LLVM for OpenMP Programs.
LLOV can detect data races in OpenMP v4.5 programs written in C/C++ and FORTRAN.  

LLOV uses polyhedral compilation techniques to detect race conditions at 
compile time.  

Unlike other race detection tool, LLOV can mark a region of code as Data 
Race Free.

## How to Run LLOV
#### Running LLOV on OpenMP C/C++ code from clang
```
./bin/clang -Xclang -disable-O0-optnone -Xclang -load -Xclang ./lib/OpenMPVerify.so  \
  -fopenmp -g tests/1.race1.c
./bin/clang++ -Xclang -disable-O0-optnone -Xclang -load -Xclang ./lib/OpenMPVerify.so  \
  -fopenmp -g test.cpp
```

#### Running LLOV on OpenMP C/C++ code from opt
```
./bin/clang -fopenmp -S -emit-llvm -g tests/1.race1.c -o test.ll
./bin/opt -mem2reg test.ll -S -o test.ssa.ll
./bin/opt -load ./lib/OpenMPVerify.so -openmp-forceinline \
  -inline -openmp-resetbounds test.ssa.ll -S -o test.resetbounds.ll
./bin/opt -load ./lib/OpenMPVerify.so \
  -disable-output \
  -openmp-verify \
  test.resetbounds.ll
```

#### Running LLOV on OpenMP FORTRAN code
```
flang -fopenmp -S -emit-llvm -g test.f95 -o test.ll
./bin/opt -O1 test.ll -S -o test.ssa.ll
./bin/opt -load ./lib/OpenMPVerify.so -openmp-forceinline \
  -inline -openmp-resetbounds test.ssa.ll -S -o test.resetbounds.ll
./bin/opt -load ./lib/OpenMPVerify.so \
  -disable-output \
  -openmp-verify \
  test.resetbounds.ll
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
@article{bora2019llov,
title={LLOV: A Fast Static Data-Race Checker for OpenMP Programs},
author={Bora, Utpal and Das, Santanu and Kukreja, Pankaj and Joshi, Saurabh and Upadrasta, Ramakrishna and Rajopadhye, Sanjay},
journal={arXiv preprint arXiv:1912.12189},
year={2019}
}
```

## Current Limitations
Following are the limitations of the current version of LLOV.  
* Does not support explicit synchronization in OpenMP. This might result 
  in FN cases for programs with dependences across SCoPs.
* Does not handle dynamic control flow.
* Does not support target offloading constructs.
* Does not support OpenMP tasks.
* Can not handle irregular accesses (a[b[i]]).
* Might produce FP for tiled and/or parallel code generated by 
  automatic code generation tools such as Pluto, Polly and PolyOPT.
* Might produce FP for OpenMP sections construct.
* Function calls within OpenMP constructs are handled only if the 
  function can be inlined.
* For some cases, source line number mapping in Polly is not preserved. 
  For those cases, race is flagged at the corresponding loop line number.

## Contact
If you have any query, please contact "Utpal Bora" &lt;cs14mtech11017@iith.ac.in&gt;.  
Please file a bug if you find the race checker is not working as required.  

Regards,  
Utpal

