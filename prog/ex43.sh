#!/bin/bash
sat13="sat13 h14 b1000 T50000000000"
for ((n=1; n<=30; n++))
do
    for ((m=2*n-1; m<=2*n; m++))
    do
        echo "# $n $m "
        ./taocpsat dadda ex43 $n $m | ./taocpsat bchain encode | $sat13 2>/dev/null | ./taocpsat decode log X Y Z
        echo
    done
done
