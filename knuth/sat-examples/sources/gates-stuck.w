@i gb_types.w

@*Intro. This program inputs a gate graph and finds a set of test vectors
that will detect most of the ``single stuck-at faults'' for those gates.
It outputs the names of the faults that it wasn't able to cover.

The first command-line parameter is the name of the graph, in
standard Stanford GraphBase format as defined in {\mc GB\_GATES}.
The second parameter is a seed for the random number generator.
An optional third parameter is the probability that an input bit
is set to 1. (It's a floating point number between 0 and 1. It's 0.5
by default.)
An optional fourth parameter is the name of an output file for the
test patterns. An optional fifth parameter is the name of an output
file for the lists of previously undetected faults that are
detected by each pattern.

If the graph has $n$ vertices (gates), there are $2n$ stuck-at faults.
The two faults for a gate named \.{gg} are called \.{0gg} and \.{1gg},
representing the hypothesis that a faulty \.{gg} always produces the value 0
or 1, respectively, irrespective of its inputs.

(Important note: I wrote the above before realizing that I should really apply
these methods to ``wires,'' not ``gates.'' One should use this program
with a graph output by {\mc GATES-TO-WIRES}.)

The method is simply to try random inputs and to see what new faults
they detect, until finding no more. A given sequence of inputs is
tested by computing its behavior with respect to all not-yet-covered
faults, using bitwise operations to handle 64 cases at once.

If the given seed value is $k$ times 1000, or more, we will continue
we've done at least $k+1$ consecutive passes over the circuit without finding
a new pattern.

@c
#include "gb_graph.h"
#include "gb_gates.h"
#include "gb_flip.h"
#include "gb_save.h"
unsigned long long **bits;
Vertex **faults;
int seed;
double bias;
unsigned long long thresh=2147483648>>1;
FILE *pat_file, *fault_file;
main (int argc, char* argv[]) {
  register int i,j,k,n,r,s;
  register unsigned long long udefault, vdefault;
  register Vertex *u,*v;
  register Arc *a;
  register Graph *g;
  int faults_left, faults_found, tolerance;
  @<Process the command line@>;
  n=g->n;
  @<Allocate the auxiliary arrays@>;
  @<Prepend all latches to the list of outputs@>;
  @<Initialize the list of faults remaining@>;
  fprintf(stderr,"(considering %d possible single-stuck-at faults)\n",
                              faults_left);
  tolerance=seed/1000;
  while (faults_left) {
    faults_found=0;
    @<Pass over the circuit with random inputs@>;
    faults_left-=faults_found;
    fprintf(stderr,"(found %d; %d left)\n",
                        faults_found,faults_left);
    if (faults_found) {
      tolerance=seed/1000;
      if (pat_file) @<Output the current test pattern@>;
    }@+else if (--tolerance<0) break;
  }
  @<Print out the remaining faults@>;
}

@ @<Process the command line@>=
if (argc < 3 || argc > 6 || sscanf(argv[2],"%d",&seed)!=1) {
  fprintf(stderr,"Usage: %s gates.gb seed [bias] [patternfile] [faultfile]\n",
                      argv[0]);
  exit(-1);
}
g=restore_graph(argv[1]);
if (!g) {
  fprintf(stderr,"I can't restore the graph `%s'!\n",
                      argv[1]);
  exit(-2);
}
if (argc>3) {
  if (sscanf(argv[3],"%lf",&bias)!=1 || bias<=0.0 || bias>=1.0) {
    fprintf(stderr,
      "The bias should be strictly between 0.0 and 1.0 (default 0.5)!\n");
    exit(-8);
  }
  thresh=bias*2147483648.0; /* $2^{31}$ */
  if (argc>4) {
    pat_file=fopen(argv[4],"w");
    if (!pat_file) {
      fprintf(stderr,"I can't open the pattern file `%s' for writing!\n",
                        argv[4]);
      exit(-3);
    }
    if (argc>5) {  
      fault_file=fopen(argv[5],"w");
      if (!fault_file) {
        fprintf(stderr,"I can't open the fault file `%s' for writing!\n",
                        argv[5]);
        exit(-4);
      }
    }
  }
}
gb_init_rand(seed);

@ @<Allocate the aux...@>=
bits=(unsigned long long**)malloc((n+1)*sizeof(unsigned long long*));
if (!bits) {
  fprintf(stderr,"I can't allocate the bits array!\n");
  exit(-5);
}
k=1+(n>>5); /* this many octabytes needed for the first round of simulation */
if (sizeof(unsigned long long)!=8) {
  fprintf(stderr,"Sorry, I wrote this code assuming 64-bit words!\n");
  exit(-6);
}
for (j=0;j<n;j++) {
  bits[j]=(unsigned long long*)malloc(k*sizeof(unsigned long long));
  if (!bits[j]) {
    fprintf(stderr,"I can't allocate the array bits[%d]!\n",
                              j);
    exit(-7);
  }
}

@ The $k$th fault that is still untested is identified in |faults[k]|.

Some \CEE/ hacking is used to represent stuck-at faults as pointers
to vertices: If |v| points to a gate, we add 1 to the numerical value
of |v| to indicate ``|v| stuck at~1.''

@d stuck_at_one(v) (Vertex*)((unsigned long long)(v)+1)
@d how_stuck(v) (int)((unsigned long long)(v)&1)
@d clean(v) ((Vertex*)((unsigned long long)(v)&-2))

@<Allocate the aux...@>=
faults=(Vertex**)malloc((n+n+1)*sizeof(Vertex*));
if (!faults) {
  fprintf(stderr,"I can't allocate the faults array!\n");
  exit(-8);
}

@ If |g| contains latches, they must follow the inputs and precede all
other gates. I'll want to treat the source of each latch as an output,
in a ``combinational'' circuit that computes a function of inputs and latches.

In this program the |val| field of vertex |v| is nonzero if and only if
|v| is an output.

@<Prepend all latches to the list of outputs@>=
for (v=g->vertices;v<g->vertices+n && v->typ=='I';v++) v->val=0;
for (;v<g->vertices+n && v->typ=='L';v++) {
  v->val=0;
  a=gb_virgin_arc();
  a->next=g->outs;
  a->tip=v->alt;
  g->outs=a;
}
for (;v<g->vertices+n;v++) v->val=0;
for (k=0,a=g->outs;a;a=a->next)
  a->tip->val=++k;

@ A fault at gate |v| is unresolved if and only if |v->stuck0| or
|v->stuck1| is nonzero.

@d stuck0 u.I /* utility field |u| of a vertex */
@d stuck1 v.I /* utility field |v| of a vertex */

@<Initialize the list of faults remaining@>=
faults_left=0;
for (v=g->vertices;v<g->vertices+n;v++)
  v->stuck0=v->stuck1=1,faults_left+=2;

@*Passing over the circuit. The heart of this computation is a
loop in which we pass over the gates one by one, evaluating them
with respect to each of the pending fault scenarios. Variable |s| is
the current number of faults under consideration.

We pack 64 scenarios per
octabyte in the |bits| table of each vertex; fault $k$ is
bit |k&0x3f| from the right in |bits[j][k>>6]|, when |v=g->vertices+j|.

``Fault 0'' is
the normal case where everything is operating correctly. This default value
for a gate, which appears in the least significant bit of |bits[j][0]|,
is assumed to apply in all scenarios $>s$.
(Hey, ``default'' means ``no faults,'' get it?)

During this processing
we set |vdefault| to 0 or |-1|, according as the default value for |v|
is 0 or 1.

The value of |s| at vertex |v| is stored in |v->size|.

@d size w.I /* utility field |w| of a vertex */

@<Pass over the circuit with random inputs@>=
for (s=j=0;j<n;j++) {
  v=g->vertices+j;  
  @<Compute |vdefault| and |bits[j]|@>;
  if (v->stuck0) {
    s++;
    faults[s]=v;
    if ((s&0x3f)==0) bits[j][s>>6]=vdefault;
    bits[j][s>>6]&=~(1ULL<<(s&0x3f));
  }
  if (v->stuck1) {
    s++;
    faults[s]=stuck_at_one(v);
    if ((s&0x3f)==0) bits[j][s>>6]=vdefault;
    bits[j][s>>6]|=1ULL<<(s&0x3f);
  }
  v->size=s;
  if (v->val) @<See if we've covered any faults@>;
}    

@ @<Compute |vdefault| and |bits[j]|@>=
switch (v->typ) {
case 'I': case 'L': @<Assign a random input@>;@+break;
case '&': @<Process an AND gate@>;@+break;
case '|': @<Process an OR gate@>;@+break;
case '^': @<Process an XOR gate@>;@+break;
case '~': @<Process an inverter@>;@+break;
case 'F': @<Process a clone gate@>;@+break;
default: fprintf(stderr,"Vertex %s (%d) has unknown gate type `%c'!\n",
                      v->name,j,(char)v->typ);
  exit(-10);
}

@ @<Assign a random input@>=
vdefault=-(gb_next_rand()<thresh);
for (k=0;k<=s>>6;k++) bits[j][k]=vdefault;

@ @<Process an inverter@>=
if (!v->arcs || v->arcs->next) {
  fprintf(stderr,"Inverter %s (%d) should have exactly one operand!\n",
                           v->name,j);
  exit(-11);
}
u=v->arcs->tip;
i=u-g->vertices;
udefault=-(bits[i][0]&1), r=u->size;
vdefault=~udefault;
for (k=0;k<=r>>6;k++) bits[j][k]=~bits[i][k];
for (;k<=s>>6;k++) bits[j][k]=vdefault;

@ A ``clone gate'' is really a wire that's a fanout branch. It should
copy the value of its lone parameter (which is a fanout stem).

@<Process a clone gate@>=
if (!v->arcs || v->arcs->next) {
  fprintf(stderr,"Fanout branch %s (%d) should have exactly one operand!\n",
                           v->name,j);
  exit(-11);
}
u=v->arcs->tip;
i=u-g->vertices;
udefault=-(bits[i][0]&1), r=u->size;
vdefault=udefault;
for (k=0;k<=r>>6;k++) bits[j][k]=bits[i][k];
for (;k<=s>>6;k++) bits[j][k]=vdefault;

@ I think some interesting optimization is possible here
(and elsewhere in this program),
but I'm eschewing it today.

@<Process an AND gate@>=
vdefault=-1;
for (k=0;k<=s>>6;k++) bits[j][k]=vdefault;
for (a=v->arcs;a;a=a->next) {
  u=a->tip, i=u-g->vertices;
  udefault=-(bits[i][0]&1), r=u->size;
  for (k=0;k<=r>>6;k++) bits[j][k]&=bits[i][k];
  if (udefault==0) {
    vdefault=0;
    for (;k<=s>>6;k++) bits[j][k]=0;
  }
}

@ @<Process an OR gate@>=
vdefault=0;
for (k=0;k<=s>>6;k++) bits[j][k]=vdefault;
for (a=v->arcs;a;a=a->next) {
  u=a->tip, i=u-g->vertices;
  udefault=-(bits[i][0]&1), r=u->size;
  for (k=0;k<=r>>6;k++) bits[j][k]|=bits[i][k];
  if (udefault) {
    vdefault=-1;
    for (;k<=s>>6;k++) bits[j][k]=-1;
  }
}

@ @<Process an XOR gate@>=
vdefault=0;
for (k=0;k<=s>>6;k++) bits[j][k]=vdefault;
for (a=v->arcs;a;a=a->next) {
  u=a->tip, i=u-g->vertices;
  udefault=-(bits[i][0]&1), r=u->size;
  for (k=0;k<=r>>6;k++) bits[j][k]^=bits[i][k];
  if (udefault) {
    vdefault^=udefault;
    for (;k<=s>>6;k++) bits[j][k]^=-1;
  }
}

@ When we reach an output gate, any scenarios that don't agree with
|vdefault| are now covered by the current random inputs.

@<See if we've covered any faults@>=
{
  for (k=0;k<=s>>6;k++) if (bits[j][k]^vdefault) {
    udefault=bits[j][k]^vdefault;
    for (i=0;i<64;i++) if (udefault&(1ULL<<i)) {
      u=faults[(k<<6)+i];
      if (how_stuck(u)) {
        u=clean(u);
        if (u->stuck1) {
          faults_found++,u->stuck1=0;
          if (fault_file) fprintf(fault_file," 1%s",
                                            u->name);
        }
      }@+else {
        if (u->stuck0) {
          faults_found++,u->stuck0=0;
          if (fault_file) fprintf(fault_file," 0%s",
                                            u->name);
        }
      }
    }
  }
}      

@* Output. Now that the algorithm is fully implemented, we need only
write the code that communicates its results.

@<Print out the remaining faults@>=
for (k=1;k<=faults_left;k++) {
  v=clean(faults[k]);
  printf(" %c%s",
          how_stuck(faults[k])? '1': '0', v->name);
}
printf("\n");
if (pat_file) {
  fprintf(stderr,"Test patterns written on file `%s'",
                   argv[4]);
  if (fault_file) fprintf(stderr,"; covered faults written on file `%s'.\n",
                               argv[5]);
  else fprintf(stderr,".\n");
}

@ Each test pattern is a string of input bits (\.0 or \.1), followed by~\.{->},
followed by a string of correct output bits, followed by a newline character.

@<Output the current test pattern@>=
{
  for (j=0;j<n;j++) {
    v=g->vertices+j;
    if (v->typ=='I' || v->typ=='L')
      fprintf(pat_file,"%c",
             (char)('0'+(bits[j][0]&1)));
  }
  fprintf(pat_file,"->");
  for (a=g->outs;a;a=a->next) {
    v=a->tip;
    fprintf(pat_file,"%c",
             (char)('0'+(bits[v-g->vertices][0]&1)));
  }
  fprintf(pat_file,"\n");
  if (fault_file) fprintf(fault_file,"\n");
}  

@*Index.
