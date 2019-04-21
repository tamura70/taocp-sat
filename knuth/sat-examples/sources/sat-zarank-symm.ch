@x
@d nmax 1000 /* upper bound on $m\times n$ */
@y
In this version I require the solution to be equal to its transpose.

@d nmax 1000 /* upper bound on $m\times n$ */
@z
@x
  @<Generate the clauses for the rectangle constraints@>;
@y
  @<Generate the clauses for the rectangle constraints@>;
  @<Generate the clauses for symmetry under reflection@>;
@z
@x
printf("~ sat-zarank %d %d %d %d %d\n",
                          m,n,r,p,q);
@y
if (m!=n) {
  fprintf(stderr,"In this version m must equal n!\n");
  exit(-5);
}
printf("~ sat-zarank-symm %d %d %d %d %d\n",
                          m,n,r,p,q);
@z
@x
@*Index.
@y
@ @<Generate the clauses for symmetry under reflection@>=
for (i=0;i<m;i++) for (j=0;j<n;j++) if (i!=j)
  printf("%d.%d ~%d.%d\n",
              i,j,j,i);

@*Index.
@z
