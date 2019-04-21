@*Intro. Data for {\mc DANCE}: The problem of Langford pairs.
Namely, place $\{1,1,2,2,\ldots,n,n\}$ in a row
so that exactly $k$ slots appears between the two $k$s.

The command line should contain $n$.

I save a factor of two by putting $n$ in the left half
(or, if $n$ straddles the center, by putting $n-1$ in the left half).

@c
#include <stdio.h>
#include <stdlib.h>
int n;
main(int argc, char *argv[])
{
  register int i, j, k, nn;
  if (argc!=2 || sscanf(argv[1],"%d",&n)!=1) {
    fprintf(stderr,"Usage: %s n\n",argv[0]);
    exit(-1);
  }
  nn=n+n;
  @<Print the header line@>;
  for (i=1;i<=n;i++) for (j=1;;j++) {
    k=i+j+1;
    if (k>nn) break;
    if (i==n-((n&1)==0) && j>n/2) break;
    printf("d%d s%d s%d\n",i,j,k);
  }
}

@ @<Print the header line@>=
for (j=1;j<=n;j++) printf("d%d ",j);
for (j=1;j<=nn;j++) printf("s%d ",j);
printf("\n");

@*Index.
