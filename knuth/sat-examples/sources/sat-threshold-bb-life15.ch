@x
With change files we can change the names of the variables $x_i$.
@y
This version changes $x_i$ to \.{$j$a$k$}, where $j-1=\lfloor(i-1)/15\rfloor$
and $k-1=(i-1)\bmod15$.
@z
@x
printf("~ sat-threshold-bb %d %d\n",n,r);
@y
printf("~ sat-threshold-bb-life15 %d %d\n",n,r);
@z
@x
@d xbar(k) printf("~x%d",(k)-n+2)
@y
@d xbar(k) printf("~%da%d",1+(int)(((k)-n+1)/15),1+((k)-n+1)%15)
@z
