# PCL 

PCL is a programming language created for the compilers class in NTUA. The lexer and parser are built using flex and bison and the code generation is done using LLVM.

## Dependencies :
```
LLVM 6.0
flex 2.5.39
bison 3.0.4
g++-8 gcc-8
```

## Building :
```shell
cd pcl/
make
```

## Execution:
To run the compiler on a sample file :
```shell
./do.sh examp_pcl2/48_primes.pcl
```

The executable supports a number of flags
```shell
-f     Program in stdin x86_64 Assembly in stdout.
-i     Program in stdin LLVM IR in stdout.
-O<n>  Optimization flag where n = {0,1,2,3}(Applied to the IR and the Assembly code)
```
The compiled executable will be called `a.out`



