@x
@d mmax 100 /* max rows */
@y
In addition to the line totals, it also gives the number of occurrences
of `11' as a substring (for input to {\mc SAT-TOMOGRAPHY-2ND}).

@d mmax 100 /* max rows */
@z
@x
  register int d,j,k,jmax,kmax,t;
@y
  register int d,j,k,jmax,kmax,t,tt;
@z
@x
@ @<Output the counts@>=
for (j=0;j<m;j++) {
  for (t=0,k=0;k<n;k++) t+=rast[j][k];
  printf("r%d=%d\n",
             j+1,t);
}
for (k=0;k<n;k++) {
  for (t=0,j=0;j<m;j++) t+=rast[j][k];
  printf("c%d=%d\n",
             k+1,t);
}
for (d=1;d<m+n;d++) {
  for (t=0,j=0;j<m;j++) {
    k=d-1-j;
    if (k>=0 && k<n) t+=rast[j][k];
  }
  printf("a%d=%d\n",
             d,t);
}
for (d=1;d<m+n;d++) {
  for (t=0,j=0;j<m;j++) {
    k=j+n-d;
    if (k>=0 && k<n) t+=rast[j][k];
  }
  printf("b%d=%d\n",
             d,t);
}
@y
@ @<Output the counts@>=
for (j=0;j<m;j++) {
  for (t=tt=0,k=0;k<n;k++) t+=rast[j][k],tt+=(k<n-1?rast[j][k]*rast[j][k+1]:0);
  printf("r%d=%d,%d\n",
             j+1,t,tt);
}
for (k=0;k<n;k++) {
  for (t=tt=0,j=0;j<m;j++) t+=rast[j][k],tt+=(j<m-1?rast[j][k]*rast[j+1][k]:0);
  printf("c%d=%d,%d\n",
             k+1,t,tt);
}
for (d=1;d<m+n;d++) {
  for (t=tt=0,j=0;j<m;j++) {
    k=d-1-j;
    if (k>=0 && k<n) t+=rast[j][k],
                 tt+=(j<m-1 && k>0? rast[j][k]*rast[j+1][k-1]:0);
  }
  printf("a%d=%d,%d\n",
             d,t,tt);
}
for (d=1;d<m+n;d++) {
  for (t=tt=0,j=0;j<m;j++) {
    k=j+n-d;
    if (k>=0 && k<n) t+=rast[j][k],
                 tt+=(j<m-1 && k<n-1? rast[j][k]*rast[j+1][k+1]:0);
  }
  printf("b%d=%d,%d\n",
             d,t,tt);
}
@z
