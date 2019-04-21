#!/bin/bash
sat13="sat13 h14 b1000 T50000000000"
for ((k=1; k<=30; k++))
do
    for ((m=2*k-1; m<=2*k; m++))
    do
        echo "# $k $m "
        ./taocpsat dadda tri_palindrome $k $m | ./taocpsat bchain encode | $sat13 2>/dev/null | ./taocpsat decode log N TT
        echo
    done
done
