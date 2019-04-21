@*Intro. This quickie outputs clauses that are unsatisfiable because they
state that there exists a partial ordering on $m$ elements in which
no element is maximal. (All backtrack proofs of this fact are known
to require $\Omega(2^m)$ steps.)

Variable \.{$j$.$k$} means that $j\prec k$ in the partial ordering.

@c
#include <stdio.h>
#include <stdlib.h>
int m;
main(int argc, char*argv[]) {
  register i,j,k;
  @<Process the command line@>;
  @<Generate the clauses for irreflexivity@>;
  @<Generate the clauses for transitivite@>;
  @<Generate the clauses for nonmaximality@>;
}

@ @<Process the command line@>=
if (argc!=2 || sscanf(argv[1],"%d",&m)!=1) {
  fprintf(stderr,"Usage: %s m\n",argv[0]);
  exit(-1);
}
printf("~ sat-poset-nomax %d\n",m);

@ @<Generate the clauses for irreflexivity@>=
for (j=1;j<=m;j++)
  printf("~%d.%d\n",j,j);

@ @<Generate the clauses for transitivite@>=
for (i=1;i<=m;i++) for (j=1;j<=m;j++) if (i!=j) {
  for (k=1;k<=m;k++) if (j!=k) {
    printf("~%d.%d ~%d.%d %d.%d\n",
             i,j,j,k,i,k);
  }
}

@ @<Generate the clauses for nonmaximality@>=
for (j=1;j<=m;j++) {
  for (k=1;k<=m;k++) printf(" %d.%d",j,k);
  printf("\n");
}

@*Index.


