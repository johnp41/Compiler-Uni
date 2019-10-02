#!/bin/bash

Oflag=0
asmout=false
irout=false
file=""
while [ $# -gt 0 ]
do
    case "$1" in
        -O0)  Oflag=0;;
        -O1)  Oflag=1;;
        -O2)  Oflag=2;;
        -O3)  Oflag=3;;
        -i)   irout=true;;
        -f)   asmout=true;;
        -*)   ;;
        *)    file="$1"
    esac
    shift
done

optf=""
if [ $Oflag -ne 0 ]; then
    optf=-O$Oflag
fi


if [ "$file" == ""  ] 
then 
	echo "Need a file !!!"
	exit 1
fi


echo "Compiling $file "
./pcl < $file > pcl-ir.ll || exit 1
echo "Waiting for optimizations"
opt-6.0 $optf pcl-ir.ll -S -o pcl-ir-opt.ll
echo "Time to use the assembler"

llc-6.0 $optf pcl-ir-opt.ll -o pcl-assemb.s

clang++-6.0 pcl-assemb.s ./edsger_lib/lib.a -o a.out


exit 0
