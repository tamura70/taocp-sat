@s step int

@*Intro. This is a quick-and-dirty way to go from a
slightly symbolic description of proposed mutual-exclusion algorithms
to a corresponding set of clauses, so that I can
use the clauses for bounded model checking.

In other
words, I want to see whether the given concurrent
algorithms can violate the mutex property by permitting
simultaneous execution of two critical sections, or whether
they can lead to livelock or starvation, in a given number of steps.
To test this, I'll see if certain extensions of the clauses are satisfiable.

First I have to describe the input language. Each step/state of an algorithm
is given a name, which begins with an uppercase letter
and has at most four characters.
Every shared variable is also given a number, which begins with a lowercase
letter and has at most two characters.

Only four elementary kinds of primitive operations are permitted at each step:

\smallskip
1) Compute non-critically, then optionally go to step $l$.
(Here $l$ is a step name.)

2) Compute critically, then go to step $l$. (Likewise.)

3) Set $V\gets v$, then goto $l$.
(Here $V$ is a shared variable and $v$ is a constant.)

4) If $V=v$, goto $l$, else goto $l'$.  (Likewise.)

\smallskip\noindent
These steps specify state transitions in an fairly obvious way;
precise semantics will be explained later.

Here's a simple example of possible input:
$$\vcenter{\halign{\tt#\hfil\cr
{\char`\~} separate locks\cr
A0 maybe goto A1\cr
A1 a=1 goto A2\cr
A2 if b=1 goto A2 else A3\cr
A3 critical goto A4\cr
A4 a=0 goto A0\cr
B0 maybe goto B1\cr
B1 b=1 goto B2\cr
B2 if a=1 goto B2 else B3\cr
B3 critical goto B4\cr
B4 b=0 goto B0\cr
}}$$
The first line, which begins with `{\tt\char`\~}', is simply a
comment that will be passed to the output file.
It is followed by steps of types 1, 3, 4, 2, 3, 1, 3, 4, 2, 3, respectively.
The shared variables are \.a and \.b.
The concurrent occurrence of critical states should never occur.

(I do not claim that these programs solve the mutex problem;
they simply provide an example.)

At present I assume that all step names begin with either A or B,
and that all shared variables are Boolean. But those restrictions
might well be lifted later, after I get some experience with this
simpler scheme.

@ Here then is the basic outline of this program.

@d maxsteps 100 /* at most this many steps */
@d bufsize 1024 /* must exceed the length of the longest input line */

@c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
@<Type definitions@>;
step state[maxsteps]; /* internal representation of the programs */
char vars[maxsteps][2]; /* the distinct shared-variable names */
int astep[maxsteps],bstep[maxsteps]; /* steps for processes A and B */
int r; /* command-line parameter, the number of time steps to emulate */
char buf[bufsize]; /* input from |stdin| goes here */
main(int argc,char*argv[]) {
  register int i,j,k,m,n,t,ma,mb;
  @<Process the command line@>;
  @<Parse the input into the |state| table@>;
  @<Generate the initial clauses@>;
  for (t=0;t<r;t++)
    @<Generate the transitions from time |t| to time |t+1|@>;
  @<Generate clauses to force concurrent critical sections at time |r|@>;
}

@ @<Process the command line@>=
if (argc!=2 || sscanf(argv[1],"%d",&r)!=1) {
  fprintf(stderr,"Usage: %s r < foo.dat\n",argv[0]);
  exit(-1);
}
if (r<=0) {
  fprintf(stderr,"Parameter r must be positive!\n");
  exit(-2);
}
printf("~ sat-mutex %d\n",r);

@ Every non-comment line of input is recorded in an abbreviated form.

@<Type...@>=
typedef struct state_struct {
  char name[4],lab[4],elab[4]; /* the name of this step and its successors */
  char var[2]; /* the shared variable */
  char val; /* its value */
  char crit; /* is this a critical step? */
} step;

@ I don't attempt to provide much syntactic sugar for the user (since
I expect to be the only user). If I need something fancier, I'll probably
write a preprocessor to convert fancy output into the primitive form
that is understood by this program.

@<Parse the input into the |state| table@>=
for (m=n=ma=mb=0;;) {
  if (!fgets(buf,bufsize,stdin)) break;
  if (buf[0]=='~') printf("%s",buf);
  else {
    char *curp=buf;
    if (m>=maxsteps) {
      fprintf(stderr,"Recompile me -- I only have room for %d steps!\n",
                                        maxsteps);
      exit(-666);
    }
    @<Scan the |name| field@>;
    if (strncmp(curp,"maybe ",6)==0) @<Scan a \.{maybe} step@>@;
    else if (strncmp(curp,"critical ",9)==0) @<Scan a \.{critical} step@>@;
    else if (strncmp(curp,"if ",3)==0) @<Scan an \.{if} step@>@;
    else @<Scan an assignment step@>;
    m++;
  }
}
@<Check for missing steps@>;
if (state[astep[0]].crit+state[bstep[0]].crit>1) {
  fprintf(stderr,"Both processes are initially in critical sections!\n");
  exit(-555);
}
fprintf(stderr,"(%d+%d steps with %d shared variables successfully input)\n",
                           ma,mb,n);

@ @d abrt(m,t) {@+fprintf(stderr,"Oops, %s!\n> %s\n",m,buf);@+exit(t);@+}

@<Scan the |name| field@>=
for (j=0;*curp&&*curp!=' '&&*curp!='\n';j++,curp++)
  if (j<4) state[m].name[j]=*curp;
if (j>4) abrt("the name is too long",-10);
if (state[m].name[0]<'A' || state[m].name[0]>'B')
  abrt("the step name must begin with A or B",-11);
for (j=0;j<m;j++) if (strncmp(state[j].name,state[m].name,4)==0)
  abrt("that name has already been used",-12);
if (state[m].name[0]=='A') astep[ma++]=m;
else bstep[mb++]=m;
if (*curp++!=' ') abrt("step is incomplete",-13);

@ @<Scan a \.{maybe} step@>=
{
  curp+=5;
  @<Scan the |lab| field@>;
  if (*curp!='\n') abrt("maybe step ends badly",-14);
}

@ @<Scan a \.{critical} step@>=
{
  curp+=8;
  state[m].crit=1;
  @<Scan the |lab| field@>;
  if (*curp!='\n') abrt("critical step ends badly",-15);
}

@ @<Scan the |lab| field@>=
if (strncmp(curp," goto ",6)!=0) abrt("missing goto",-16);
curp+=6;
for (j=0;*curp&&*curp!=' '&&*curp!='\n';j++,curp++)
   if (j<4) state[m].lab[j]=*curp;
if (j>4) abrt("the label is too long",-17);

@ @<Scan an \.{if} step@>=
{
  curp+=3;
  @<Scan the |var| field@>;
  if (*curp++!='=') abrt("missing `=' in an if step",-18);
  @<Scan the |val| field@>;
  @<Scan the |lab| field@>;
  @<Scan the |elab| field@>;
  if (*curp!='\n') abrt("that if step ends badly",-19);
}

@ @<Scan the |var| field@>=
for (j=0;*curp&&*curp!='='&&*curp!='\n';j++,curp++)
  if (j<2) state[m].var[j]=vars[n][j]=*curp;
if (j>2) abrt("the variable name is too long",-20);
if (state[m].var[0]<'a' || state[m].var[0]>'z')
  abrt("a variable name must begin with a lowercase letter",-21);
for (j=0;j<n;j++) if (strncmp(vars[j],state[m].var,2)==0) break;
if (j==n) n++;
else vars[n][1]=0;

@ @<Scan the |val| field@>=
if (*curp<'0' || *curp>'1') abrt("the value must be 0 or 1",-22);
state[m].val=*curp++-'0';

@ @<Scan the |elab| field@>=
if (strncmp(curp," else ",6)!=0) abrt("missing else",-23);
curp+=6;
for (j=0;*curp&&*curp!='\n';j++,curp++) if (j<4) state[m].elab[j]=*curp;
if (j>4) abrt("the else label is too long",-24);

@ @<Scan an assignment step@>=
{
  @<Scan the |var| field@>;
  if (*curp++!='=') abrt("missing `=' in an assignment step",-25);
  @<Scan the |val| field@>;
  @<Scan the |lab| field@>;
  if (*curp!='\n') abrt("assignment step ends badly",-26);
}

@ @<Check for missing steps@>=
if (ma==0) {
  fprintf(stderr,"There are no steps for process A!\n");
  exit(-99);
}
if (mb==0) {
  fprintf(stderr,"There are no steps for process B!\n");
  exit(-98);
}
for (k=t=0;k<m;k++) {
  if (state[k].lab[0]) {
    for (j=0;j<m;j++) if (strncmp(state[j].name,state[k].lab,4)==0) break;
    if (j==m) {
      fprintf(stderr,"Missing step %.4s!\n",state[k].lab);
      t++;
    }
  }
  if (state[k].elab[0]) {
    for (j=0;j<m;j++) if (strncmp(state[j].name,state[k].elab,4)==0) break;
    if (j==m) {
      fprintf(stderr,"Missing step %.4s!\n",state[k].elab);
      t++;
    }
  }
}
if (t) exit(-30);

@ The generated clauses involve variables like `\.{2A1}', meaning that
process~A is in state \.{A1} at time~2;
also variables like `\.{3b}', meaning that shared variable~\.b is 1 (true)
at time~3;
also variables like `\.{1@@}', meaning that process~A took a turn at
time~1. (The negations of these variables, namely
\.{\char`\~2A1},
\.{\char`\~3b},
\.{\char`\~1@@},
mean respectively that A is not in state \.{A1} at time~2,
\.b is 0 (false) at time~3, and
process~B took a turn at time~1.)

At time 0, all shared variables are 0 and each process is in its
first-mentioned state.

@<Generate the initial clauses@>=
{
  for (j=0;j<n;j++) printf("~000%.2s\n",vars[j]);
  printf("000%.4s\n",state[astep[0]].name);
  for (j=1;j<ma;j++) printf("~000%.4s\n",state[astep[j]].name);
  printf("000%.4s\n",state[bstep[0]].name);
  for (j=1;j<mb;j++) printf("~000%.4s\n",state[bstep[j]].name);
}

@ Speaking of turns reminds me that I promised to define precise semantics.

At each time |t| one of the processes, chosen nondeterministically, is
granted permission to take a turn, which means intuitively that it
performs the step corresponding to its current state. We say that
the selected process is ``bumped.''

Every process is in a unique state at time~|t|. The state of a process
remains the same at time~|t+1| if it's not bumped. But if it's bumped,
the next state is
(1)~either the same or |lab|, nondeterministically, after a \.{maybe} step;
(2)~|lab| after a critical step or an assignment step;
(2)~either |lab| or |elab| after an \.{if} step, depending on whether or not
the shared variable has the specified value.

The value of a shared variable at time |t+1| is the same as the
value that it had at time~|t|, unless the bumped process assigned another
value to it. In particular, if two processes are trying to change the same
shared variable, the bumped process changes it first.

When the bumped process executes an \.{if} statement at the same time
as another process is trying to write the same variable, the other process
does not influence the result of the \.{if}; the change it wants to make
will have to wait. [This rule means that weaker algorithms can get by,
but they need stronger (and presumably more expensive and/or
slower) hardware support. I'm using this rule in all the early examples
of mutex in TAOCP, because it is easier to explain; the harder rule can be
considered later, after algorithms pass this simpler criterion.]

@<Generate the transitions from time |t| to time |t+1|@>=
{
  @<Generate clauses to forbid nonunique states for A at time |t+1|@>;
  @<Generate clauses to forbid nonunique states for B at time |t+1|@>;
  @<Generate the state transition clauses when A is bumped@>;
  @<Generate the state transition clauses when B is bumped@>;
  @<Generate the variable transition clauses@>;
}

@ I introduce auxiliary variables here, using Heule's exclusion
clauses, so that we don't have quadratic blowup when the programs are large.

@d printprevA() if (j) printf("%03d_A%d",t+1,i-1);
    else printf("~%03d%.4s",t+1,state[astep[k-1]].name);

@<Generate clauses to forbid nonunique states for A at time |t+1|@>=
k=ma;
if (k>1) {
  i=j=0;
  if (k==2) printf("~%03d%.4s ~%03d%.4s\n",
                       t+1,state[astep[0]].name,t+1,state[astep[1]].name);
  while (k>4) {
    printprevA();  printf(" ~%03d%.4s\n",
                t+1,state[astep[k-2]].name);
    printprevA(); printf(" ~%03d%.4s\n",
                t+1,state[astep[k-3]].name);
    printprevA(); printf(" ~%03d_A%d\n",
                t+1,i);
    printf("~%03d%.4s ~%03d%.4s\n",
                t+1,state[astep[k-2]].name,t+1,state[astep[k-3]].name);
    printf("~%03d%.4s ~%03d_A%d\n",
                t+1,state[astep[k-2]].name,t+1,i);
    printf("~%03d%.4s ~%03d_A%d\n",
                t+1,state[astep[k-3]].name,t+1,i);
    i++,j=1,k-=2;
  }
  printprevA(); printf(" ~%03d%.4s\n",
                t+1,state[astep[k-2]].name);
  printprevA(); printf(" ~%03d%.4s\n",
                t+1,state[astep[k-3]].name);
  printf("~%03d%.4s ~%03d%.4s\n",
                t+1,state[astep[k-2]].name,t+1,state[astep[k-3]].name);
  if (k>3) {
    printprevA(); printf(" ~%03d%.4s\n",
                t+1,state[astep[k-4]].name);
    printf("~%03d%.4s ~%03d%.4s\n",
                  t+1,state[astep[k-2]].name,t+1,state[astep[k-4]].name);
    printf("~%03d%.4s ~%03d%.4s\n",
                  t+1,state[astep[k-3]].name,t+1,state[astep[k-4]].name);
  }
}

@ @d printprevB() if (j) printf("%03d_B%d",t+1,i-1);
    else printf("~%03d%.4s",t+1,state[bstep[k-1]].name);

@<Generate clauses to forbid nonunique states for B at time |t+1|@>=
k=mb;
if (k>1) {
  i=j=0;
  if (k==2) printf("~%03d%.4s ~%03d%.4s\n",
                       t+1,state[bstep[0]].name,t+1,state[bstep[1]].name);
  while (k>4) {
    printprevB(); printf(" ~%03d%.4s\n",
                t+1,state[bstep[k-2]].name);
    printprevB(); printf(" ~%03d%.4s\n",
                t+1,state[bstep[k-3]].name);
    printprevB(); printf(" ~%03d_B%d\n",
                t+1,i);
    printf("~%03d%.4s ~%03d%.4s\n",
                t+1,state[bstep[k-2]].name,t+1,state[bstep[k-3]].name);
    printf("~%03d%.4s ~%03d_B%d\n",
                t+1,state[bstep[k-2]].name,t+1,i);
    printf("~%03d%.4s ~%03d_B%d\n",
                t+1,state[bstep[k-3]].name,t+1,i);
    i++,j=1,k-=2;
  }
  printprevB(); printf(" ~%03d%.4s\n",
              t+1,state[bstep[k-2]].name);
  printprevB(); printf(" ~%03d%.4s\n",
              t+1,state[bstep[k-3]].name);
   printf("~%03d%.4s ~%03d%.4s\n",
                t+1,state[bstep[k-2]].name,t+1,state[bstep[k-3]].name);
  if (k>3) {
    printprevB(); printf(" ~%03d%.4s\n",
                   t+1,state[bstep[k-4]].name);
    printf("~%03d%.4s ~%03d%.4s\n",
                  t+1,state[bstep[k-2]].name,t+1,state[bstep[k-4]].name);
    printf("~%03d%.4s ~%03d%.4s\n",
                  t+1,state[bstep[k-3]].name,t+1,state[bstep[k-4]].name);
  }
}

@ @d tprime (t+1)

@<Generate the state transition clauses when A is bumped@>=
for (k=0;k<ma;k++) {
  printf("%03d@@ ~%03d%.4s %03d%.4s\n",
               t,t,state[astep[k]].name,tprime,state[astep[k]].name);
  if (state[astep[k]].var[0]==0) {
    if (state[astep[k]].crit==0) /* a \.{maybe} step */
      printf("~%03d@@ ~%03d%.4s %03d%.4s %03d%.4s\n",
                   t,t,state[astep[k]].name,
                    tprime,state[astep[k]].name,tprime,state[astep[k]].lab);
    else printf("~%03d@@ ~%03d%.4s %03d%.4s\n",
                   t,t,state[astep[k]].name,
                    tprime,state[astep[k]].lab); /* a \.{critical} step */
  }@+else if (state[astep[k]].elab[0]==0) { /* an assignment step */
    printf("~%03d@@ ~%03d%.4s %03d%.4s\n",
                   t,t,state[astep[k]].name,tprime,state[astep[k]].lab);
  }@+else @<Generate clauses for when A is bumped in an \.{if} step@>;
}

@ @<Generate clauses for when A is bumped in an \.{if} step@>=
{
  printf("~%03d@@ ~%03d%.4s",
              t,t,state[astep[k]].name);
  printf(" %s%03d%.2s %03d%.4s\n",
              state[astep[k]].val?"~":"",t,state[astep[k]].var,
              tprime,state[astep[k]].lab);
  printf("~%03d@@ ~%03d%.4s",
              t,t,state[astep[k]].name);
  printf(" %s%03d%.2s %03d%.4s\n",
              state[astep[k]].val?"":"~",t,state[astep[k]].var,
              tprime,state[astep[k]].elab);
}

@ @<Generate the state transition clauses when B is bumped@>=
for (k=0;k<mb;k++) {
  printf("~%03d@@ ~%03d%.4s %03d%.4s\n",
               t,t,state[bstep[k]].name,tprime,state[bstep[k]].name);
  if (state[bstep[k]].var[0]==0) {
    if (state[bstep[k]].crit==0) /* a \.{maybe} step */
      printf("%03d@@ ~%03d%.4s %03d%.4s %03d%.4s\n",
                   t,t,state[bstep[k]].name,
                    tprime,state[bstep[k]].name,tprime,state[bstep[k]].lab);
    else printf("%03d@@ ~%03d%.4s %03d%.4s\n",
                   t,t,state[bstep[k]].name,
                    tprime,state[bstep[k]].lab); /* a \.{critical} step */
  }@+else if (state[bstep[k]].elab[0]==0) { /* an assignment step */
    printf("%03d@@ ~%03d%.4s %03d%.4s\n",
                   t,t,state[bstep[k]].name,tprime,state[bstep[k]].lab);
  }@+else @<Generate clauses for when B is bumped in an \.{if} step@>;
}

@ @<Generate clauses for when B is bumped in an \.{if} step@>=
{
  printf("%03d@@ ~%03d%.4s",
              t,t,state[bstep[k]].name);
  printf(" %s%03d%.2s %03d%.4s\n",
              state[bstep[k]].val?"~":"",t,state[bstep[k]].var,
              tprime,state[bstep[k]].lab);
  printf("%03d@@ ~%03d%.4s",
              t,t,state[bstep[k]].name);
  printf(" %s%03d%.2s %03d%.4s\n",
              state[bstep[k]].val?"":"~",t,state[bstep[k]].var,
              tprime,state[bstep[k]].elab);
}

@ @<Generate the variable transition clauses@>=
for (k=0;k<n;k++) {
  /* first consider all cases where the value changes */
  for (j=0;j<m;j++)
    if (strncmp(state[j].var,vars[k],2)==0 && state[j].elab[0]==0)
      printf("%s%03d@@ ~%03d%.4s %s%03d%.2s\n",
               state[j].name[0]=='A'?"~":"",t,t,state[j].name,
               state[j].val==0?"~":"",tprime,state[j].var);
  /* now consider all cases where the value doesn't change */
  printf("~%03d@@ %03d%.2s",
               t,t,vars[k]); /* A bumped and val is 0 */
  for (j=0;j<m;j++)
    if (strncmp(state[j].var,vars[k],2)==0 && state[j].elab[0]==0
               && state[j].name[0]=='A')
      printf(" %03d%.4s",
                 t,state[j].name); /* not changed by A */
  printf(" ~%03d%.2s\n",
               tprime,vars[k]); /* it stays 0 */
  printf("%03d@@ %03d%.2s",
               t,t,vars[k]); /* B bumped and val is 0 */
  for (j=0;j<m;j++)
    if (strncmp(state[j].var,vars[k],2)==0 && state[j].elab[0]==0
               && state[j].name[0]=='B')
      printf(" %03d%.4s",
                 t,state[j].name); /* not changed by B */
  printf(" ~%03d%.2s\n",
               tprime,vars[k]); /* it stays 0 */
  printf("~%03d@@ ~%03d%.2s",
               t,t,vars[k]); /* A bumped and val is 1 */
  for (j=0;j<m;j++)
    if (strncmp(state[j].var,vars[k],2)==0 && state[j].elab[0]==0
               && state[j].name[0]=='A')
      printf(" %03d%.4s",
                 t,state[j].name); /* not changed by A */
  printf(" %03d%.2s\n",
               tprime,vars[k]); /* it stays 1 */
  printf("%03d@@ ~%03d%.2s",
               t,t,vars[k]); /* B bumped and val is 1 */
  for (j=0;j<m;j++)
    if (strncmp(state[j].var,vars[k],2)==0 && state[j].elab[0]==0
               && state[j].name[0]=='B')
      printf(" %03d%.4s",
                 t,state[j].name); /* not changed by B */
  printf(" %03d%.2s\n",
               tprime,vars[k]); /* it stays 1 */
}

@ The different ways of going jointly critical are \.{C0}, \.{C1}, etc.

@<Generate clauses to force concurrent critical sections at time |r|@>=
for (i=j=0;j<ma;j++) if (state[astep[j]].crit) {
  for (k=0;k<mb;k++) if (state[bstep[k]].crit) {
    printf("~C%d %03d%.4s\n",
                i,r,state[astep[j]].name);
    printf("~C%d %03d%.4s\n",
                i,r,state[bstep[k]].name);
    i++;
  }
}
for (j=0;j<i;j++)
  printf(" C%d",
             j);
printf("\n");

@*Index.
