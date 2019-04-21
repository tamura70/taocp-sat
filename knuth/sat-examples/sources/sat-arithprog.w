\datethis
\def\[#1]{[\hbox{$\mkern1mu\thickmuskip=\thinmuskip#1\mkern1mu$}]} % Iverson
\let\lor=\vee

@*Intro. Here I try to generate SAT instances for partial van der
Waerden configurations: There are to be no $t$ equally spaced ones,
in $x_1\ldots x_n$. Furthermore I try to make $x_1+\cdots+x_n=r$.

One key idea is to use the Sinz-inspired clauses
with $(n-r)r$ auxiliary variables 
$$s_j^k=\[x_1+\cdots+x_{j+k-1}\ge k],\qquad
\hbox{for $1\le j\le n-r$ and $1\le k\le r$.}$$
[See {\sl Lecture Notes in Computer Science\/ \bf3709} (2005), 827--831.]
The clauses are
$$\vcenter{\halign{$\hfil#$,&\ for #\hfil\cr
\bar s_j^k\lor s_{j+1}^k&$1\le j<n-r$ and $1\le k\le r$;\cr
s_j^k\lor\bar s_j^{k+1}&$1\le j\le n-r$ and $1\le k<r$;\cr
\bar x_{j+k}\lor\bar s_j^k\lor s_j^{k+1}&$1\le j\le n-r$ and $0\le k\le r$;\cr
x_{j+k}\lor s_j^k\lor\bar s_{j+1}^k&$0\le j\le n-r$ and $1\le k\le r$.\cr}}$$
(And we simplify them at the boundaries by using $s_0^k=s_j^{r+1}=0$,
$s_j^0=s_{n-r+1}^k=1$.)

This program uses the code `\.{$j$S$k$}' to denote $s_j^k$ in its output.

I assume the existence of a file \.{free$t$.dat} that contains
the smallest values $n_1$, \dots,~$n_{r-1}$ of $n$ for which this
problem is satisfiable for smaller values of~$r$. For example,
\.{free3.dat} begins with the numbers 1, 2, 4, 5, 9, 11, 13, 14; and I might
be running this program with $t=3$, $n=18$, $r=9$ to see if the
number 18 should come next in that file. [Answer: The clauses
to be generated are unsatisfiable; therefore the next number in the file
must be at least 19. In fact, the next number $F_3(9)$ turns out to be~20.]

Continuing that example, we know that $x_{a+1}+x_{a+2}+x_{a+3}\le2$
for $0\le a\le 15$; similarly $x_{a+1}+\cdots+x_{a+8}\le4$,
$x_{a+1}+\cdots+x_{a+10}\le5$,
$x_{a+1}+\cdots+x_{a+12}\le6$, and
$x_{a+1}+\cdots+x_{a+17}\le8$, according to the previously tabulated
numbers on file. (Two other inequalities,
$x_{a+1}+\cdots+x_{a+4}\le3$ and
$x_{a+1}+\cdots+x_{a+13}\le7$,
also belong to this pattern; but they are trivial consequences of
their predecessors.)

In general if $x_{a+1}+\cdots+x_{a+p}\le q$ for $0\le a\le n-p$, we
can convert that information into useful constraints on the
auxiliary variables $s_j^k$, because $x_1+\cdots+x_{a+p}\ge k$
implies that $x_1+\cdots+x_a\ge k-q$. If we set $b=a-k+q+1$, we can
rewrite this statement as ``$s_{b+p-q}^k$ implies $s_b^{k-q}$'';
that is, the clauses $\bar s_{b+p-q}^k\lor s_b^{k-q}$ must be
valid, for $0\le b\le n-r+1-p+q$ and $q<k\le r$.

For example, when $p=17$ and $q=8$, there are just two special
clauses, $\bar s_9^9\lor s_0^1$ and $\bar s_{10}^9\lor s_1^1$,
which simplify to $\bar s_9^9$ and $s_1^1$. Equivalently,
$x_{18}=1$ and $x_1=1$. (Similar deductions will always occur,
when we're trying to establish extreme values; we'll necessarily have
$x_1=x_n=1$, since the case $n-1$ admits at most $r-1$ 1s.)

This program first generates the clauses in $\lnot x_i$ that enforce
the no-$k$-equally-spaced-ones constraints. Then it generates the
clauses above, and one more to reduce symmetry.

In the example with $n=18$ and $r=9$, the Sinz-plus-subinterval
clauses themselves (without the arithmetic progression clauses)
already force most of the variables $s_j^k$: By unit propagations
they are
$$\pmatrix{
1&1&1&1&1&1&1&1&1\cr
 & & &1&1&1&1&1&1\cr
0& & &1&1&1&1&1&1\cr
0& & & &1&1&1&1&1\cr
0&0&0&0&0&1&1&1&1\cr
0&0&0&0&0& & & &1\cr
0&0&0&0&0&0& & &1\cr
0&0&0&0&0&0& & & \cr
0&0&0&0&0&0&0&0&0\cr
}.$$

@d maxr 100

@c
#include <stdio.h>
#include <stdlib.h>
FILE *infile;
int table[maxr+1];
int t,n,r; /* command-line parameters */
char buf[16];
main(int argc,char*argv[]) {
  register int b,d,i,j,k,p,q;
  @<Process the command line@>;
  @<Input the file \.{free$t$}@>;
  printf("~ sat-arithprog %d %d %d\n",t,n,r);
  @<Output the negative clauses@>;
  @<Output the standard Sinz clauses@>;
  @<Output the special implications@>;
  @<Output the final symmetry-breaking clause@>;
}

@ @<Process the command line@>=
if (argc!=4 || sscanf(argv[1],"%d",&t)!=1 ||
               sscanf(argv[2],"%d",&n)!=1 ||
               sscanf(argv[3],"%d",&r)!=1) {
  fprintf(stderr,"Usage: %s t n r\n",argv[0]);
  exit(-1);
}
if (r>maxr) {
  fprintf(stderr,"Sorry, r (%d) should not exceed %d!\n",r,maxr);
  exit(-2);
}
if (n>=256) {
  fprintf(stderr,"Sorry, n (%d) must not exceed 255!\n",n);
  exit(-3);
}

@ @<Input the file \.{free$t$}@>=
sprintf(buf,"free%d.dat",t);
infile=fopen(buf,"r");
if (!infile) {
  fprintf(stderr,"I can't open file `%s' for reading!\n",buf);
  exit(-5);
}
for (j=1;j<r;j++) {
  if (fscanf(infile,"%d",&table[j])!=1) {
    fprintf(stderr,"I couldn't read item %d in file `%s'!\n",j,buf);
    exit(-6);
  }
}
table[r]=n;

@ @<Output the negative clauses@>=
for (d=1;1+(t-1)*d<=n;d++) {
  for (i=1;i+(t-1)*d<=n;i++) {
    for (j=0;j<t;j++) printf(" ~x%d",i+j*d);
    printf("\n");
  }
}

@ @<Output the standard Sinz clauses@>=
for (j=1;j<n-r;j++) for (k=1;k<=r;k++)
  printf("~%dS%d %dS%d\n",j,k,j+1,k);
for (j=1;j<=n-r;j++) for (k=1;k<r;k++)
  printf("%dS%d ~%dS%d\n",j,k,j,k+1);
for (j=1;j<=n-r;j++) for (k=0;k<=r;k++) {
  printf("~x%d",j+k);
  if (k>0) printf(" ~%dS%d",j,k);
  if (k<r) printf(" %dS%d",j,k+1);
  printf("\n");
}
for (j=0;j<=n-r;j++) for (k=1;k<=r;k++) {
  printf("x%d",j+k);
  if (j>0) printf(" %dS%d",j,k);
  if (j<n-r) printf(" ~%dS%d",j+1,k);
  printf("\n");
}

@ @<Output the special...@>=
for (q=2;q<r;q++) if (table[q+1]>table[q]+1) {
  p=table[q+1]-1;
  for (b=0;b<=n-r+1-p+q;b++) for (k=q+1;k<=r;k++) {
    if (b+p-q<=n-r) printf("~%dS%d",b+p-q,k);
    if (b>0) printf(" %dS%d",b,k-q);
    printf("\n");
  }
}

@ The left-to-right reflection of any solution is also a solution.
Therefore we can conclude that any solution with
$s_{\lceil(n-r)/2\rceil}^{\lceil r/2\rceil}=1$ implies a solution with
$s_{\lceil(n-r)/2\rceil}^{\lceil r/2\rceil}=0$,
if $r$ is odd. On the other hand if $n$ and $r$ are both even, we can assume
that $x_1+\cdots+x_{n/2}\ge r/2$.

@<Output the final...@>=
if (r&1) {
  j=(n-r+1)>>1,k=(r+1)>>1;
  printf("~%dS%d\n",j,k);
}@+else if (!(n&1)) {
  j=(n-r)>>1,k=r>>1;
  printf("%dS%d\n",j+1,k);
}


@*Index.


