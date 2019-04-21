@x
@d mmax 200 /* should be at most 255 unless I use bigger radix than hex */
@y
Well actually, the above should be amended: This version works not only
with sums of ones, it also uses sums of `11's (that is, consecutive
occurrences of 1s in the same line). The second-order sums are
given after a comma; for example, `$\.{r3=20,8}'.

@d mmax 200 /* should be at most 255 unless I use bigger radix than hex */
@z
@x
int r[mmax+1],c[mmax+1],a[mmax+nmax],b[mmax+nmax]; /* the given data */
@y
int r[mmax+1],c[mmax+1],a[mmax+nmax],b[mmax+nmax]; /* the given data */
int rr[mmax+1],cc[mmax+1],aa[mmax+nmax],bb[mmax+nmax]; /* and its extensions */
@z
@x
  register int d,i,j,k,l,m,n,nn,t;
@y
  register int d,i,j,k,l,ll,m,n,nn,t;
@z
@x
  if (*p!='\n') {
@y
  if (*p++!=',') {
    fprintf(stderr,"Missing comma!\nBad line %s",
                         buf);
    exit(-12);
  }
  for (ll=0;*p>='0' && *p<='9';p++) ll=10*ll+*p-'0';
  if (*p!='\n') {
@z
@x
  r[d]=l;
@y
  r[d]=l,rr[d]=ll;
@z
@x
  c[d]=l;
@y
  c[d]=l,cc[d]=ll;
@z
@x
  a[d]=l;
@y
  a[d]=l,aa[d]=ll;
@z
@x
  b[d]=l;
@y
  b[d]=l,bb[d]=ll;
@z
@x
printf("~ sat-tomography (%dx%d, %d)\n",
@y
printf("~ sat-tomography-2nd (%dx%d, %d)\n",
@z
@x
  gen_clauses(n,r[i]);
@y
  gen_clauses(n,r[i]);
  gen_clauses1(n-1,rr[i]);
@z
@x
  gen_clauses(n,n-r[i]);
@y
  gen_clauses(n,n-r[i]);
  gen_clauses2(n-1,n-1-rr[i]);
@z
@x
  gen_clauses(m,c[j]);
@y
  gen_clauses(m,c[j]);
  gen_clauses1(m-1,cc[j]);
@z
@x
  gen_clauses(m,m-c[j]);
@y
  gen_clauses(m,m-c[j]);
  gen_clauses2(m-1,m-1-cc[j]);
@z
@x
      gen_clauses(d,a[d]);
@y
      gen_clauses(d,a[d]);
      gen_clauses1(d-1,aa[d]);
@z
@x
      gen_clauses(m,a[d]);
@y
      gen_clauses(m,a[d]);
      gen_clauses1(m-1,aa[d]);
@z
@x
      gen_clauses(m+n-d,a[d]);
@y
      gen_clauses(m+n-d,a[d]);
      gen_clauses1(m+n-d-1,aa[d]);
@z
@x
      gen_clauses(d,a[d]);
@y
      gen_clauses(d,a[d]);
      gen_clauses1(d-1,aa[d]);
@z
@x
      gen_clauses(n,a[d]);
@y
      gen_clauses(n,a[d]);
      gen_clauses1(n-1,aa[d]);
@z
@x
      gen_clauses(m+n-d,a[d]);
@y
      gen_clauses(m+n-d,a[d]);
      gen_clauses1(m+n-d-1,aa[d]);
@z
@x
      gen_clauses(d,d-a[d]);
@y
      gen_clauses(d,d-a[d]);
      gen_clauses2(d-1,d-1-aa[d]);
@z
@x
      gen_clauses(m,m-a[d]);
@y
      gen_clauses(m,m-a[d]);
      gen_clauses2(m-1,m-1-aa[d]);
@z
@x
      gen_clauses(m+n-d,m+n-d-a[d]);
@y
      gen_clauses(m+n-d,m+n-d-a[d]);
      gen_clauses2(m+n-d-1,m+n-d-1-aa[d]);
@z
@x
      gen_clauses(d,d-a[d]);
@y
      gen_clauses(d,d-a[d]);
      gen_clauses2(d-1,d-1-aa[d]);
@z
@x
      gen_clauses(n,n-a[d]);
@y
      gen_clauses(n,n-a[d]);
      gen_clauses2(n-1,n-1-aa[d]);
@z
@x
      gen_clauses(m+n-d,m+n-d-a[d]);
@y
      gen_clauses(m+n-d,m+n-d-a[d]);
      gen_clauses2(m+n-d-1,m+n-d-1-aa[d]);
@z
@x
      gen_clauses(d,b[d]);
@y
      gen_clauses(d,b[d]);
      gen_clauses1(d-1,bb[d]);
@z
@x
      gen_clauses(m,b[d]);
@y
      gen_clauses(m,b[d]);
      gen_clauses1(m-1,bb[d]);
@z
@x
      gen_clauses(m+n-d,b[d]);
@y
      gen_clauses(m+n-d,b[d]);
      gen_clauses1(m+n-d-1,bb[d]);
@z
@x
      gen_clauses(d,b[d]);
@y
      gen_clauses(d,b[d]);
      gen_clauses1(d-1,bb[d]);
@z
@x
      gen_clauses(n,b[d]);
@y
      gen_clauses(n,b[d]);
      gen_clauses1(n-1,bb[d]);
@z
@x
      gen_clauses(m+n-d,b[d]);
@y
      gen_clauses(m+n-d,b[d]);
      gen_clauses1(m+n-d-1,bb[d]);
@z
@x
      gen_clauses(d,d-b[d]);
@y
      gen_clauses(d,d-b[d]);
      gen_clauses2(d-1,d-1-bb[d]);
@z
@x
      gen_clauses(m,m-b[d]);
@y
      gen_clauses(m,m-b[d]);
      gen_clauses2(m-1,m-1-bb[d]);
@z
@x
      gen_clauses(m+n-d,m+n-d-b[d]);
@y
      gen_clauses(m+n-d,m+n-d-b[d]);
      gen_clauses2(m+n-d-1,m+n-d-1-bb[d]);
@z
@x
      gen_clauses(d,d-b[d]);
@y
      gen_clauses(d,d-b[d]);
      gen_clauses2(d-1,d-1-bb[d]);
@z
@x
      gen_clauses(n,n-b[d]);
@y
      gen_clauses(n,n-b[d]);
      gen_clauses2(n-1,n-1-bb[d]);
@z
@x
      gen_clauses(m+n-d,m+n-d-b[d]);
@y
      gen_clauses(m+n-d,m+n-d-b[d]);
      gen_clauses2(m+n-d-1,m+n-d-1-bb[d]);
@z
@x
@*Index.
@y
@ Now we have new subroutines analogous to the old. But where
|gen_clauses| makes $x_1+\cdots+x_n\le r$, |gen_clauses1| makes
$x_1x_2+\cdots+x_nx_{n+1}\le r$.

We needn't produce any output if $r=n-1$, because the total number
of 1s has already been tested by |gen_clauses|.

@<Subroutines@>=
void gen_clauses1(int n,int r) {
  register int i,j,k,jl,jr,t,tl,tr;
  if (r<0) {
    fprintf(stderr,"Negative parameter for case <%s!\n",buf);
    exit(-99);
  }
  if (r==0) for (j=1;j<=n;j++) printf("%s %s\n",name[j],name[j+1]);
  else if (r<n-1) { /* if $r\ge n-1$ we won't need any clauses */
    @<Build the complete binary tree with $n$ leaves@>;
    for (i=n-2;i;i--) @<Generate the clauses1 for node $i$@>;
    @<Generate the clauses1 at the root@>;
  }
}

@ The symbolic name in |buf| is preceded by \.<, to distinguish
these clauses from those of |gen_clauses|. (As a result, the
maximum number of diagonals is limited to 99, in order to keep
from generating nine-character names.)

@<Generate the clauses1 for node $i$@>=
{
  t=count[i], tl=count[i+i+1], tr=count[i+i+2];
  if (t==2) @<Generate clauses1 just above two leaves@>@;
  else if (t==3) @<Generate clauses1 just above a leaf@>@;
  else {
    if (t>r+1) t=r+1;
    if (tl>r+1) tl=r+1;
    if (tr>r+1) tr=r+1;
    for (jl=0;jl<=tl;jl++) for (jr=0;jr<=tr;jr++)
      if ((jl+jr<=t) && (jl+jr)>0) {
        if (jl) printf("~<%s%02x%02x",buf,i+i+2,jl);
        if (jr) printf(" ~<%s%02x%02x",buf,i+i+3,jr);
        printf(" <%s%02x%02x\n",buf,i+1,jl+jr);
      }
  }
}    

@ Here |tl=tr=1|.

@<Generate clauses1 just above two leaves@>=
{
  printf("%s %s <%s%02x01\n",name[i+i-n+3],name[i+i-n+4],buf,i+1);
  printf("%s %s <%s%02x01\n",name[i+i-n+4],name[i+i-n+5],buf,i+1);
  printf("%s %s %s <%s%02x02\n",
       name[i+i-n+3],name[i+i-n+4],name[i+i-n+5],buf,i+1);
}

@ And here |tl=2| and |tr=1|.

@<Generate clauses1 just above a leaf@>=
{
  printf("~<%s%02x01 <%s%02x01\n",buf,i+i+2,buf,i+1);
  printf("%s %s <%s%02x01\n",name[i+i-n+4],name[i+i-n+5],buf,i+1);
  printf("~<%s%02x02 <%s%02x02\n",buf,i+i+2,buf,i+1);
  printf("~<%s%02x01 %s %s <%s%02x02\n",
           buf,i+i+2,name[i+i-n+4],name[i+i-n+5],buf,i+1);
  printf("~<%s%02x02 %s %s <%s%02x03\n",
           buf,i+i+2,name[i+i-n+4],name[i+i-n+5],buf,i+1);
}

@ Finally, we assert that at most $r$ of the $x$'s are true, by
implicitly asserting that the (nonexistent) variable for $i=1$ and $j=r+1$
is false.

@<Generate the clauses1 at the root@>=
if (n==3) { /* then |r=1| */
  printf("%s %s %s\n",name[1],name[2],name[3]);
  printf("%s %s %s\n",name[2],name[3],name[4]);
}@+else {
  tl=count[1], tr=count[2];
  for (jl=0;jl<=tl;jl++) {
    jr=r+1-jl;
    if (jr>=0 && jr<=tr) {
      if (jl) printf("~<%s02%02x",buf,jl);
      if (jr) printf(" ~<%s03%02x",buf,jr);
      printf("\n");
    }
  }    
}

@ Similarly, |gen_clauses2| makes
$\overline{x_1x_2}+\cdots+\overline{x_nx_{n+1}}\le r$.

We always call |gen_clauses2(n,n-r)| after |gen_clauses1(n,r)|.
Thus no output is needed to supplement the output of |gen_clauses|
in the case |r=0|.

@<Subroutines@>=
void gen_clauses2(int n,int r) {
  register int i,j,k,jl,jr,t,tl,tr;
  if (r<0) {
    fprintf(stderr,"Negative parameter for case >%s!\n",buf);
    exit(-99);
  }
  if (r>0 && r<n) { /* otherwise we won't need any clauses */
    @<Build the complete binary tree with $n$ leaves@>;
    for (i=n-2;i;i--) @<Generate the clauses2 for node $i$@>;
    @<Generate the clauses2 at the root@>;
  }
}

@ @<Generate the clauses2 for node $i$@>=
{
  t=count[i], tl=count[i+i+1], tr=count[i+i+2];
  if (t==2) @<Generate clauses2 just above two leaves@>@;
  else if (t==3) @<Generate clauses2 just above a leaf@>@;
  else {
    if (t>r+1) t=r+1;
    if (tl>r+1) tl=r+1;
    if (tr>r+1) tr=r+1;
    for (jl=0;jl<=tl;jl++) for (jr=0;jr<=tr;jr++)
      if ((jl+jr<=t) && (jl+jr)>0) {
        if (jl) printf("~>%s%02x%02x",buf,i+i+2,jl);
        if (jr) printf(" ~>%s%02x%02x",buf,i+i+3,jr);
        printf(" >%s%02x%02x\n",buf,i+1,jl+jr);
      }
  }
}    

@ Here |tl=tr=1|.

@<Generate clauses2 just above two leaves@>=
{
  printf("%s >%s%02x01\n",name[i+i-n+3],buf,i+1);
  printf("%s >%s%02x01\n",name[i+i-n+4],buf,i+1);
  printf("%s >%s%02x01\n",name[i+i-n+5],buf,i+1);
  printf("%s >%s%02x02\n",name[i+i-n+4],buf,i+1);
  printf("%s %s >%s%02x02\n",name[i+i-n+3],name[i+i-n+5],buf,i+1);
}

@ And here |tl=2| and |tr=1|.

@<Generate clauses2 just above a leaf@>=
{
  printf("~>%s%02x01 >%s%02x01\n",buf,i+i+2,buf,i+1);
  printf("%s >%s%02x01\n",name[i+i-n+4],buf,i+1);
  printf("%s >%s%02x01\n",name[i+i-n+5],buf,i+1);
  printf("~%s%02x02 >%s%02x02\n",buf,i+i+2,buf,i+1);
  printf("~>%s%02x01 %s >%s%02x02\n",buf,i+i+2,name[i+i-n+4],buf,i+1);
  printf("~>%s%02x01 %s >%s%02x02\n",buf,i+i+2,name[i+i-n+5],buf,i+1);
  printf("~>%s%02x02 %s >%s%02x03\n",buf,i+i+2,name[i+i-n+4],buf,i+1);
  printf("~>%s%02x02 %s >%s%02x03\n",buf,i+i+2,name[i+i-n+5],buf,i+1);
}

@ Finally, we assert that at most $r$ of the $x$'s are true, by
implicitly asserting that the (nonexistent) variable for $i=1$ and $j=r+1$
is false.

@<Generate the clauses2 at the root@>=
if (n==2) { /* then |r=1| */
  printf("%s\n",name[2]);
  printf("%s %s\n",name[1],name[3]);
}@+else if (n==3) {
  if (r==2) {
    printf("%s %s\n",name[1],name[3]);
    printf("%s %s\n",name[2],name[3]);
    printf("%s %s\n",name[2],name[4]);
  }@+else { /* |r==1| */
    printf("%s\n",name[2]);
    printf("%s\n",name[3]);
    printf("%s %s\n",name[1],name[4]);
  }
}@+else {
  tl=count[1], tr=count[2];
  for (jl=0;jl<=tl;jl++) {
    jr=r+1-jl;
    if (jr>=0 && jr<=tr) {
      if (jl) printf("~>%s02%02x",buf,jl);
      if (jr) printf(" ~>%s03%02x",buf,jr);
      printf("\n");
    }
  }    
}

@*Index.
@z
