@*Intro. Given row sum, column sums, and diagonal sums on |stdin|,
this program outputs clauses by which a {\mc SAT} solver can determine if
they are compatible with the existence of an $m\times n$ matrix $x_{ij}$
of zeros and ones.

The row sums are $r_i=\sum_{j=1}^n x_{ij}$, for $1\le i\le m$.
The column sums are $c_j=\sum_{i=1}^m x_{ij}$, for $1\le j\le n$.
And the diagonal sums are $a_d=\sum\{x_{ij}\mid i+j=d+1\}$ and
$b_d=\sum\{x_{ij}\mid i-j=d-n\}$, for $0<d<m+n$. They should appear
one per line in the input, in a format such as `\.{r3=20}'. Zero
sums need not be given. The program deduces $m$ and $n$ from the largest
subscripts that appear, and it makes fairly careful syntax checks.

@d mmax 200 /* should be at most 255 unless I use bigger radix than hex */
@d nmax 100 /* should be at most 255 unless I use bigger radix than hex */

@c
#include <stdio.h>
#include <stdlib.h>
int r[mmax+1],c[mmax+1],a[mmax+nmax],b[mmax+nmax]; /* the given data */
int count[mmax+mmax+nmax+nmax]; /* leaf counts for the BB method */
char buf[80];
char name[mmax+nmax][9];
@<Subroutines@>;
main() {
  register int d,i,j,k,l,m,n,nn,t;
  register char *p;
  @<Input the data@>;
  @<Check the data@>;
  @<Output the clauses@>;
}

@ @<Input the data@>=
m=n=0;
while (1) {
  if (!fgets(buf,80,stdin)) break;
  for (d=0,p=buf+1;*p>='0' && *p<='9';p++) d=10*d+*p-'0';
  if (*p++!='=') {
    fprintf(stderr,"Missing `=' sign!\nBad line: %s",
                           buf);
    exit(-1);
  }
  for (l=0;*p>='0' && *p<='9';p++) l=10*l+*p-'0';
  if (*p!='\n') {
    fprintf(stderr,"Missing \\n character!\nBad line %s",
                           buf);
    exit(-2);
  }
  switch (buf[0]) {
@<Cases for row, column, and diagonal sums@>@;
default: fprintf(stderr,"Data must begin with r, c, a, or b!\nBad line %s",
                                  buf);
  exit(-3);
  }
}

@ @<Cases for row, column, and diagonal sums@>=
case 'r': if (d<1 || d>mmax) {
    fprintf(stderr,"Row index out of range!\nBad line %s",
                         buf);
    exit(-4);
  }
  if (l<0 || l>nmax) {
    fprintf(stderr,"Row data out of range!\nBad line %s",
                         buf);
    exit(-5);
  }
  if (d>m) m=d;
  if (r[d]) {
    fprintf(stderr,"The value of r%d has already been given!\nBad line %s",
                         d,buf);
    exit(-6);
  }
  r[d]=l;
  break;

@ @<Cases for row, column, and diagonal sums@>=
case 'c': if (d<1 || d>nmax) {
    fprintf(stderr,"Column index out of range!\nBad line %s",
                         buf);
    exit(-14);
  }
  if (l<0 || l>mmax) {
    fprintf(stderr,"Column data out of range!\nBad line %s",
                         buf);
    exit(-15);
  }
  if (d>n) n=d;
  if (c[d]) {
    fprintf(stderr,"The value of c%d has already been given!\nBad line %s",
                         d,buf);
    exit(-16);
  }
  c[d]=l;
  break;

@ @<Cases for row, column, and diagonal sums@>=
case 'a': if (d<1 || d>=mmax+nmax) {
    fprintf(stderr,"Diagonal index out of range!\nBad line %s",
                         buf);
    exit(-24);
  }
  if (l<0 || l>mmax || l>nmax) {
    fprintf(stderr,"Diagonal data out of range!\nBad line %s",
                         buf);
    exit(-25);
  }
  if (a[d]) {
    fprintf(stderr,"The value of a%d has already been given!\nBad line %s",
                         d,buf);
    exit(-26);
  }
  a[d]=l;
  break;

@ @<Cases for row, column, and diagonal sums@>=
case 'b': if (d<1 || d>=mmax+nmax) {
    fprintf(stderr,"Diagonal index out of range!\nBad line %s",
                         buf);
    exit(-34);
  }
  if (l<0 || l>mmax || l>nmax) {
    fprintf(stderr,"Diagonal data out of range!\nBad line %s",
                         buf);
    exit(-35);
  }
  if (b[d]) {
    fprintf(stderr,"The value of b%d has already been given!\nBad line %s",
                         d,buf);
    exit(-36);
  }
  b[d]=l;
  break;


@ @<Check the data@>=
for (i=1,l=0;i<=m;i++) l+=r[i];
nn=l;
for (j=1,l=0;j<=n;j++) l+=c[j];
if (l!=nn) {
  fprintf(stderr,
     "The total of the r's is %d, but the total of the c's is %d!\n",
                    nn,l);
  exit(-40);
}
for (d=1,l=0;d<m+n;d++) l+=a[d];
if (l!=nn) {
  fprintf(stderr,
     "The total of the r's is %d, but the total of the a's is %d!\n",
                    nn,l);
  exit(-41);
}
for (d=1,l=0;d<m+n;d++) l+=b[d];
if (l!=nn) {
  fprintf(stderr,
     "The total of the r's is %d, but the total of the b's is %d!\n",
                    nn,l);
  exit(-41);
}
fprintf(stderr,"Input for %d rows and %d columns successfully read",
                             m,n);
fprintf(stderr," (total %d)\n",
                             nn);
printf("~ sat-tomography (%dx%d, %d)\n",
                           m,n,nn);

@ The variables $x_{ij}$ of the unknown Boolean matrix are denoted
by `\.{$i$x$j$}'. Auxiliary variables by which we check lower and
upper bounds for row sum~$r_i$ are denoted by
`\.{$i$R$l$}'. And similar conventions hold for the column sums and
the diagonal sums. 

@<Output the clauses@>=
for (i=1;i<=m;i++) @<Output clauses to check $r_i$@>;
for (j=1;j<=n;j++) @<Output clauses to check $c_j$@>;
for (d=1;d<m+n;d++) @<Output clauses to check $a_d$@>;
for (d=1;d<m+n;d++) @<Output clauses to check $b_d$@>;

@ We use the methods of Bailleux and Boufkhad
(see {\mc SAT-THRESHOLD-BB-EQUAL}).
Indeed, Bailleux and Boufkhad introduced those methods because they
wanted to study digital tomography problems.

@<Output clauses to check $r_i$@>=
{
  sprintf(buf,"%dR",i);
  for (j=1;j<=n;j++) sprintf(name[j],"%dx%d",i,j);
  gen_clauses(n,r[i]);
}

@ @<Subroutines@>=
void gen_clauses(int n,int r) {
  register int i,j,k,jl,jr,t,tl,tr,swap=0;
  if (r>n-r) swap=1,r=n-r;
  if (r<0) {
    fprintf(stderr,"Negative parameter for case %s!\n",buf);
    exit(-99);
  }
  if (r==0) @<Handle the trivial case directly@>@;
  else {
   @<Build the complete binary tree with $n$ leaves@>;
    for (i=n-2;i;i--) {
      @<Generate the clauses for node $i$@>;
      @<Generate additional clauses for node $i$@>;
    }
    @<Generate the clauses at the root@>;
    @<Generate additional clauses at the root@>;
  }
}

@ The tree has $2n-1$ nodes, with 0 as the root; the leaves start
at node~$n-1$. Nonleaf node $k$ has left child $2k+1$ and right child $2k+2$.
Here we simply fill the |count| array.

@<Build the complete binary tree with $n$ leaves@>=
for (k=n+n-2;k>=n-1;k--) count[k]=1;
for (;k>=0;k--)
  count[k]=count[k+k+1]+count[k+k+2];
if (count[0]!=n) {
  fprintf(stderr,"I'm totally confused.\n");
  exit(-666);
}

@ If there are $t$ leaves below node $i$, we introduce $k=\min(r,t)$
auxiliary variables, beginning with the symbolic name in~|buf| and
ending with two hex digits of~$i+1$ and two hex digits of~$j$,
for $1\le j\le k$. This variable will be~1 if and
only if at least $j$ of those leaf variables are true.
If $t>r$, we also assert that no $r+1$ of those variables are true.

@d x(k) printf("%s%s",swap?"~":"",name[(k)-n+2])
@d xbar(k) printf("%s%s",swap?"":"~",name[(k)-n+2])

@<Generate the clauses for node $i$@>=
{
  t=count[i], tl=count[i+i+1], tr=count[i+i+2];
  if (t>r+1) t=r+1;
  if (tl>r) tl=r;
  if (tr>r) tr=r;
  for (jl=0;jl<=tl;jl++) for (jr=0;jr<=tr;jr++)
    if ((jl+jr<=t) && (jl+jr)>0) {
      if (jl) {
        if (i+i+1>=n-1) xbar(i+i+1);
        else printf("~%s%02x%02x",buf,i+i+2,jl);
      }
      if (jr) {
        printf(" ");
        if (i+i+2>=n-1) xbar(i+i+2);
        else printf("~%s%02x%02x",buf,i+i+3,jr);
      }
      if (jl+jr<=r) printf(" %s%02x%02x\n",buf,i+1,jl+jr);
      else printf("\n");
    }
}    

@ So far we've only propagated the effects of the known 1s among the $x$'s.
Now we propagate the effects of the 0s: If there are fewer than
|tl| 1s in the leaves of the left subtree and fewer than |tr| 1s in those
of the right subtree, there are fewer than |tl+tr-1| in the leaves of
below node~|i|.

@<Generate additional clauses for node $i$@>=
if (t>r) t=r;
for (jl=1;jl<=tl+1;jl++) for (jr=1;jr<=tr+1;jr++) if (jl+jr<=t+1) {
  if (jl<=tl) {
    if (i+i+1>=n-1) x(i+i+1);
    else printf("%s%02x%02x",buf,i+i+2,jl);
    printf(" ");
  }
  if (jr<=tr) { /* note that we can't have both |jl>tl| and |jr>tr| */
    if (i+i+2>=n-1) x(i+i+2);
    else printf("%s%02x%02x",buf,i+i+3,jr);
    printf(" ");
  }
  printf("~%s%02x%02x\n",buf,i+1,jl+jr-1);
}

@ Finally, we assert that at most $r$ of the $x$'s are true, by
implicitly asserting that the (nonexistent) variable for $i=0$ and $j=r+1$
is false.

@<Generate the clauses at the root@>=
tl=count[1], tr=count[2];
for (jl=1;jl<=tl;jl++) {
  jr=r+1-jl;
  if (jr>0 && jr<=tr) {
    if (1>=n-1) xbar(1);
    else printf("~%s02%02x",buf,jl);
    printf(" ");
    if (2>=n-1) xbar(2);
    else printf("~%s03%02x",buf,jr);
    printf("\n");
  }
}    

@ To make {\it exactly\/} $r$ of the $x$'s true, we also assert that
the (nonexistent) variable for $i=1$ and $j=r$ is true.

@<Generate additional clauses at the root@>=
for (jl=1;jl<=r;jl++) {
  jr=r+1-jl;
  if (jr>0) {
    if (jl<=tl) {
      if (1>=n-1) x(1);
      else printf("%s02%02x",buf,jl);
      printf(" ");
    }
    if (jr<=tr) {
      if (2>=n-1) x(2);
      else printf("%s03%02x",buf,jr);
    }
    printf("\n");
  }
}    

@ @<Handle the trivial case directly@>=
{
  for (i=1;i<=n;i++) {
    xbar(n-2+i);
    printf("\n");
  }
}

@ @<Output clauses to check $c_j$@>=
{
  sprintf(buf,"%dC",j);
  for (i=1;i<=m;i++) sprintf(name[i],"%dx%d",i,j);
  gen_clauses(m,c[j]);
}

@ @<Output clauses to check $a_d$@>=
{
  sprintf(buf,"%dA",d);
  if (m<=n) {
    if (d<=m) {
      for (i=1;i<=d;i++) sprintf(name[i],"%dx%d",i,d+1-i);
      gen_clauses(d,a[d]);
    }@+else if (d<=n) {
      for (i=1;i<=m;i++) sprintf(name[i],"%dx%d",i,d+1-i);
      gen_clauses(m,a[d]);
    }@+else {
      for (t=1;t<=m+n-d;t++) sprintf(name[t],"%dx%d",d+t-n,n+1-t);
      gen_clauses(m+n-d,a[d]);
    }
  }@+else {
    if (d<=n) {
      for (i=1;i<=d;i++) sprintf(name[i],"%dx%d",i,d+1-i);
      gen_clauses(d,a[d]);
    }@+else if (d<=m) {
      for (j=1;j<=n;j++) sprintf(name[j],"%dx%d",d+1-j,j);
      gen_clauses(n,a[d]);
    }@+else {
      for (t=1;t<=m+n-d;t++) sprintf(name[t],"%dx%d",d+t-n,n+1-t);
      gen_clauses(m+n-d,a[d]);
    }
  }
}

@ @<Output clauses to check $b_d$@>=
{
  sprintf(buf,"%dB",d);
  if (m<=n) {
    if (d<=m) {
      for (i=1;i<=d;i++) sprintf(name[i],"%dx%d",i,n+i-d);
      gen_clauses(d,b[d]);
    }@+else if (d<=n) {
      for (i=1;i<=m;i++) sprintf(name[i],"%dx%d",i,n+i-d);
      gen_clauses(m,b[d]);
    }@+else {
      for (j=1;j<=m+n-d;j++) sprintf(name[j],"%dx%d",j+d-n,j);
      gen_clauses(m+n-d,b[d]);
    }
  }@+else {
    if (d<=n) {
      for (i=1;i<=d;i++) sprintf(name[i],"%dx%d",i,n+i-d);
      gen_clauses(d,b[d]);
    }@+else if (d<=m) {
      for (j=1;j<=n;j++) sprintf(name[j],"%dx%d",j+d-n,j);
      gen_clauses(n,b[d]);
    }@+else {
      for (j=1;j<=m+n-d;j++) sprintf(name[j],"%dx%d",j+d-n,j);
      gen_clauses(m+n-d,b[d]);
    }
  }
}

@*Index.
