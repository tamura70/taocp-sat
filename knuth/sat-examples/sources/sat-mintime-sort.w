@*Intro. We generate clauses that are satisfiable if and only if
there's a sorting network on $n$ lines for which (a)~certain
initial comparators are specified, and (b)~all subsequent comparators
can be done in $t$ parallel steps.

We assume that $n<16$, so that all lines can be
identified by a single hexadecimal digit. Furthermore $t$ is a
single digit number, because 16 elements can be sorted in 9 rounds.

There are variables \.{$ij$C$t$}, denoting the existence of
comparator $[i{:}j]$ at time~$t$; \.{$k$$j$B$t$}, denoting internal
nodes to check for interference/use of lines at time~$t$;
and \.{$xi$V$t$}, denoting the value on line~$i$ at time~$t$ when the
input is~$x$. (Here $x$ is given as four hexadecimal digits.)

@d maxr 20 /* at most this many initial comparators */

@c
#include <stdio.h>
#include <stdlib.h>
int n,tt,ii,jj; /* command-line parameters */
int mask[maxr+maxr],m[16];
int leaf[32];
char needed[1<<16];
main(int argc,char*argv[]) {
  register int i,is,j,js,k,l,r,t,x,y,z;
  @<Process the command line@>;
  @<Generate the \.B and \.C clauses@>;
  @<Generate the \.V clauses@>;
  @<Generate the unit clauses@>;
}

@ @<Process the command line@>=
if (argc==1 || (argc&1)==0 || argc>maxr+maxr+3 ||@|
      sscanf(argv[1],"%d",
                        &n)!=1 ||
      sscanf(argv[2],"%d",
                        &tt)!=1) {
  fprintf(stderr,"Usage: %s n t i1 j1 ... ir jr\n",
                                              argv[0]);
  exit(-1);
}
if (n<3 || n>15) {
  fprintf(stderr,"Sorry, n must be between 3 and 15!\n");
  exit(-2);
}
printf("~ sat-mintime-sort %d %d",
                     n,tt);
for (j=3;argv[j];j++) printf(" %s",
                              argv[j]);
printf("\n");

@ There are $n-1$ potential comparators that use line $k$, namely
$[1{:}k]$, \dots, $[k{-}1{:}k]$, $[k{:}k{+}1]$, \dots, $[k{:}n]$.
Place these at nodes $n-1$ through $2n-3$ of the complete binary
tree with $n-1$ leaves. The $n-2$ internal nodes of this tree represent
the condition that exactly one leaf in their subtree is true.

@<Generate the \.B and \.C clauses@>=
for (t=1;t<=tt;t++) for (k=1;k<=n;k++) {
  for (i=n-1,j=1;j<=n;j++) {
    if (j<k) leaf[i++]=(j<<4)+k;
    else if (j>k) leaf[i++]=(k<<4)+j;
  }
  for (j=n-2;j;j--) {
    if (j+j>=n-1) printf("~%xC%d",
                                  leaf[j+j],t);
    else printf("~%x%xB%d",
                       k,j+j,t);
    if (j+j+1>=n-1) printf(" ~%xC%d\n",
                                  leaf[j+j+1],t);
    else printf(" ~%x%xB%d\n",
                       k,j+j+1,t);
    if (j+j>=n-1) printf("~%xC%d %x%xB%d\n",
                                  leaf[j+j],t,k,j,t);
    else printf("~%x%xB%d %x%xB%d\n",
                       k,j+j,t,k,j,t);
    if (j+j+1>=n-1) printf("~%xC%d %x%xB%d\n",
                                  leaf[j+j+1],t,k,j,t);
    else printf("~%x%xB%d %x%xB%d\n",
                       k,j+j+1,t,k,j,t);
    printf("~%x%xB%d",
                   k,j,t);
    if (j+j>=n-1) printf(" %xC%d",
                          leaf[j+j],t);
    else printf(" %x%xB%d",
                          k,j+j,t);
    if (j+j+1>=n-1) printf(" %xC%d\n",
                          leaf[j+j+1],t);
    else printf(" %x%xB%d\n",
                          k,j+j+1,t);
  }
}    

@ @<Generate the \.V clauses@>=
@<Set up the masks@>;
@<Generate all the input cases@>;
for (x=2;x<(1<<n);x++) if (needed[x]) {
  for (t=1;t<=tt;t++) {
    for (i=1,is=1<<(n-1);is;i++,is>>=1) for (j=i+1,js=is>>1;js;j++,js>>=1)
      @<Generate the clauses for $i{:}j$ on $x$ at time $t$@>;
    for (i=1,is=1<<(n-1);is;i++,is>>=1)
      @<Generate the clauses for untouched line $i$ on $x$ at time $t$@>;
  }
}

@ @<Set up the masks@>=
for (i=0;argv[i+i+3];i++) {
  if (sscanf(argv[i+i+3],"%d",
                         &ii)!=1 ||
      sscanf(argv[i+i+4],"%d",
                         &jj)!=1 ||
      ii<1 | ii>n | jj<=ii | jj>n) {
    fprintf(stderr,"Invalid comparator [%s:%s"
                             "]\n",argv[i+i+3],argv[i+i+4]);
    exit(-3);
  }
  mask[i]=((1<<n)>>ii) | ((1<<n)>>jj);
}
r=i;

@ (Minor trick here: A binary number $x$ is already ``sorted'' if and only if
|x&(x+1)| is zero.)

@<Generate all the input cases@>=
for (x=2;x<(1<<n);x++) {
  for (y=x,i=0;i<r;i++) {
    t=mask[i]&-mask[i];
    if ((y&mask[i])==mask[i]-t) y^=mask[i];
  }
  if (y&(y+1)) needed[y]=1;
}

@ There are six clauses, each of which should also include $\bar C_{ij}^t$:
$(\bar v_i^t\lor v_i^{t-1})$;
$(\bar v_i^t\lor v_j^{t-1})$;
$(v_i^t\lor\bar v_i^{t-1}\lor\bar v_j^{t-1})$;
$(\bar v_j^t\lor v_i^{t-1}\lor v_j^{t-1})$;
$(v_j^t\lor\bar v_i^{t-1})$;
$(v_j^t\lor\bar v_j^{t-1})$.
We change $v_i^t$ to $x_i$ when $t=0$ and to $y_i$ when |t=tt|;
and we omit clauses that are always true.

Let $m_i=2^{n-i}-1$. The first four of these clauses are always true when
|x<=m[i]|, because $v_i^t=0$ for all~$t$ in that case. Similarly, the
second clause and the last three are always true when |(x+1)&m[j-1]==0|, because
$v_j^t=1$ for all~$t$ in that case. These simplifications are
important, because the {\mc SAT} solver will not immediately
discover them via unit propagation.

@d xi (x&is)
@d xj (x&js)
@d yi (y&is)
@d yj (y&js)

@<Set up the masks@>=
for (i=0;i<=n;i++) m[i]=(1<<(n-i))-1;

@ @<Generate the clauses for $i{:}j$ on $x$ at time $t$@>=
{
  for (y=x;z=y&(y+1);y-=z>>1); /* sort |x| */
  if (x<=m[i] || (t==1 && xi) || (t==tt && !yi)) ;
  else {
    printf("~%x%xC%d",
               i,j,t);
    if (t!=tt) printf(" ~%04x%xV%d",
                     x,i,t);
    if (t!=1) printf(" %04x%xV%d",
                     x,i,t-1);
    printf("\n");
  }
  if (x<=m[i] || ((x+1)&m[j-1])==0 || (t==1 && xj) || (t==tt && !yi)) ;
  else {
    printf("~%x%xC%d",
               i,j,t);
    if (t!=tt) printf(" ~%04x%xV%d",
                     x,i,t);
    if (t!=1) printf(" %04x%xV%d",
                     x,j,t-1);
    printf("\n");
  }
  if (x<=m[i] || (t==1 && (!xi || !xj)) || (t==tt && yi)) ;
  else {
    printf("~%x%xC%d",
               i,j,t);
    if (t!=tt) printf(" %04x%xV%d",
                     x,i,t);
    if (t!=1) {
      printf(" ~%04x%xV%d",
                     x,i,t-1);
      if ((x+1)&m[j-1]) printf(" ~%04x%xV%d",
                     x,j,t-1);
    }
    printf("\n");
  }
  if (x<=m[i] || ((x+1)&m[j-1])==0 || (t==1 && !xi) || (t==tt && yj)) ;
  else {
    printf("~%x%xC%d",
               i,j,t);
    if (t!=tt) printf(" %04x%xV%d",
                     x,j,t);
    if (t!=1) printf(" ~%04x%xV%d",
                     x,i,t-1);
    printf("\n");
  }
  if (((x+1)&m[j-1])==0 || (t==1 && !xj) || (t==tt && yj)) ;
  else {
    printf("~%x%xC%d",
               i,j,t);
    if (t!=tt) printf(" %04x%xV%d",
                     x,j,t);
    if (t!=1) printf(" ~%04x%xV%d",
                     x,j,t-1);
    printf("\n");
  }
  if (((x+1)&m[j-1])==0 || (t==1 && (xi || xj)) || (t==tt && !yj)) ;
  else {
    printf("~%x%xC%d",
               i,j,t);
    if (t!=tt) printf(" ~%04x%xV%d",
                     x,j,t);
    if (t!=1) {
      if (x>m[i]) printf(" %04x%xV%d",x,i,t-1);
      printf(" %04x%xV%d",
                     x,j,t-1);
    }
    printf("\n");
  }
}

@ If \.{$i$1B$t$} is false, we have $v_i^t=v_i^{t-1}$.

@<Generate the clauses for untouched line $i$ on $x$ at time $t$@>=
{
  if (x<=m[i] || ((x+1)&m[i-1])==0 || (t==1 && xi) || (t==tt && !yi)) ;
  else {
    printf("%x1B%d",
              i,t);
    if (t!=tt) printf(" ~%04x%xV%d",
                          x,i,t);
    if (t!=1) printf(" %04x%xV%d",
                          x,i,t-1);
    printf("\n");
  }
  if (x<=m[i] || ((x+1)&m[i-1])==0 || (t==1 && !xi) || (t==tt && yi)) ;
  else {
    printf("%x1B%d",
              i,t);
    if (t!=tt) printf(" %04x%xV%d",
                          x,i,t);
    if (t!=1) printf(" ~%04x%xV%d",
                          x,i,t-1);
    printf("\n");
  }
}

@ Finally, we append unit clauses to suppress comparators that are redundant.

@<Generate the unit clauses@>=
for (i=0;i<r;i++) {
  for (j=i+1;j<r;j++) {
    if (mask[i]&mask[j]) break;
  }
  if (j==r) {
    for (j=1,t=1<<(n-1);t;j++,t>>=1) {
      if (mask[i]&t) break;
    }
    for (k=j+1,t>>=1;t;k++,t>>=1) {
      if (mask[i]&t) break;
    }
    printf("~%x%xC1\n",
                j,k);
  }
}                           

@*Index.
