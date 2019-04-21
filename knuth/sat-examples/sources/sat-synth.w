@*Intro. Given an input file that contains a partial specification of a
Boolean function of $N$ variables, this program generates clauses that are
satisfiable if and only if the function has a disjunctive normal form
with at most $K$~terms. Parameters $N$ and $K$ are given on the command line.

The main variables are \.{$i$+$j$} (meaning that term~$i$ contains $x_j$)
and \.{$i$-$j$} (meaning that term~$i$ contains $\bar x_j$), for
$1\le i\le K$ and $1\le j\le N$. There also are subsidiary
variables \.{$i$.$k$} for $1\le i\le K$ and $1\le k\le T$, if $T$ of
the specified function values are true.

For example, the input file
$$\vcenter{\halign{\tt#\hfil\cr
101:1\cr
001:0\cr
100:1\cr
111:0\cr
011:1\cr
}}$$
informs us that $f(1,0,1)=1$, $f(0,0,1)=0$, \dots, $f(0,1,1)=1$;
here $N=3$ and $T=3$. If we specify $K=2$, the satisfiability problem
will be satisfied, for example, by \.{1+1}, \.{1-2}, \.{2-1}, \.{2+2};
that is, $f(x_1,x_2,x_3)=x_1\bar x_2\lor\bar x_1x_2$ agrees with the
given specifications. [This example is taken from a paper by Kamath,
Karmarker, Ramakrishnan, and Resende, {\sl Mathematical Programming\/ \bf57}
(1992), 215--238, where the problem is introduced and many examples
are given.]

The first line of input in the example above generates seven clauses:
$$\catcode`\~=11\vcenter{\halign{\tt#\hfil\quad&#\hfil\cr
1.1 2.1&(term 1 or term 2 must be true at 101)\cr
~1.1 ~1-1&(if term 1 is true at 101, it doesn't contain $\bar x_1$)\cr
~1.1 ~1+2&(if term 1 is true at 101, it doesn't contain $     x_2$)\cr
~1.1 ~1-3&(if term 1 is true at 101, it doesn't contain $\bar x_3$)\cr
~2.1 ~1-1&(if term 2 is true at 101, it doesn't contain $\bar x_1$)\cr
~2.1 ~1+2&(if term 2 is true at 101, it doesn't contain $     x_2$)\cr
~2.1 ~1-3&(if term 2 is true at 101, it doesn't contain $\bar x_3$)\cr
}}$$
And the second line generates two:
$$\vcenter{\halign{\tt#\hfil\quad&#\hfil\cr
1+1 1+2 1-3&(term 1 is false at 001, so it contains $x_1$, $x_2$, or $\bar x_3$)\cr
2+1 2+2 2-3&(term 2 is false at 001, so it contains $x_1$, $x_2$, or $\bar x_3$)\cr
}}$$
In general, a `true' line in the input generates one clause of size~$K$
and $NK$ clauses of size~2; a `false' line generates $K$ clauses of size~$N$.

@d maxn 100 /* we assume that $N$ doesn't exceed this */
@d O "%" /* used for percent signs in format strings */

@c
#include <stdio.h>
#include <stdlib.h>
char buf[maxn+4];
int K,N; /* command-line parameters */
main (int argc,char*argv[]) {
  register int i,j,k,t;
  @<Process the command line@>;
  printf("~ sat-synth %d %d\n",N,K);
  t=0; /* this many `true' lines so far */
  while (1) {
    if (!fgets(buf,N+4,stdin)) break;
    @<Generate clauses based on |buf|@>;
  }
}

@ @<Process the command line@>=
if (argc!=3 || sscanf(argv[1],""O"d",&N)!=1 ||
               sscanf(argv[2],""O"d",&K)!=1) {
  fprintf(stderr,"Usage: "O"s N K\n",argv[0]);
  exit(-1);
}
if (N>maxn) {
  fprintf(stderr,
   "That N ("O"d) is too big for me, I'm set up for at most "O"d!\n",N,maxn);
  exit(-2);
}

@ The buffer should now hold $N$ digits, then
colon, digit, |'\n'|, and |'\0'|.

@<Generate clauses based on |buf|@>=
if (buf[N]!=':' || buf[N+1]<'0' || buf[N+1]>'1' || buf[N+2]!='\n' || buf[N+3])
  fprintf(stderr,"bad input line `"O"s' is ignored!\n",buf);
else {
  for (k=0;k<N;k++) if (buf[k]<'0' || buf[k]>'1') break;
  if (k<N) fprintf(stderr,"nonbinary data `"O"s' is ignored!\n",buf);
  else if (buf[N+1]=='0') @<Generate clauses for a `false' line@>@;
  else @<Generate clauses for a `true' line@>;
}

@ @<Generate clauses for a `false' line@>=
{
  for (i=1;i<=K;i++) {
    for (j=1;j<=N;j++)
      printf(" "O"d"O"c"O"d",i,buf[j-1]=='0'? '+': '-',j);
    printf("\n");
  }
}

@ @<Generate clauses for a `true' line@>=
{
  t++;
  for (i=1;i<=K;i++) printf(" "O"d."O"d",i,t);
  printf("\n");
  for (i=1;i<=K;i++) for (j=1;j<=N;j++)
    printf("~"O"d."O"d ~"O"d"O"c"O"d\n",i,t,i,buf[j-1]=='0'? '+':'-',j);
}
  

@*Index.
