@x
To test this, I'll see if certain extensions of the clauses are satisfiable.
@y
To test this, I'll see if certain extensions of the clauses are satisfiable.

The present program generates extra clauses to see if it's possible
to have $r+1$ {\it distinct} states $X_0\to X_1\to\cdots\to X_r$.
Here $X_0$ is {\it not\/} necessarily the initial state.

A second command-line parameter names an auxiliary input file,
which is contains a set of lemmas that should
have been proved to be invariant. Such invariants tend to
remove inaccessible states from the possibilities.

(Well actually you can use non-invariant lemmas too, if you know
what you are doing.)
@z
@x
int r; /* command-line parameter, the number of time steps to emulate */
@y
int r; /* command-line parameter, the number of time steps to emulate */
FILE *lemma_file;
@z
@x
  @<Generate the initial clauses@>;
@y
@z
@x
  for (t=0;t<r;t++)
    @<Generate the transitions from time |t| to time |t+1|@>;
  @<Generate clauses to force concurrent critical sections at time |r|@>;
@y
  t=-1;
  @<Generate clauses to forbid nonunique states for A at time |t+1|@>;
  @<Generate clauses to forbid nonunique states for B at time |t+1|@>;
  for (t=0;t<r;t++) {
    register int u;
    @<Generate the transitions from time |t| to time |t+1|@>;
    for (u=0;u<=t;u++)
      @<Generate clauses to ensure that $X_u!=X_{t+1}$@>;
  }
  @<Generate the clauses that deal with the lemmas@>;
@z
@x
if (argc!=2 || sscanf(argv[1],"%d",&r)!=1) {
  fprintf(stderr,"Usage: %s r < foo.dat\n",argv[0]);
@y
if (argc!=3 || sscanf(argv[1],"%d",&r)!=1) {
  fprintf(stderr,"Usage: %s r foo.lemmas < foo.dat\n",argv[0]);
@z
@x
if (r<=0) {
  fprintf(stderr,"Parameter r must be positive!\n");
@y
if (r<=0 || r>=100) {
  fprintf(stderr,"Parameter r must be between 1 and 99!\n");
@z
@x
printf("~ sat-mutex %d\n",r);
@y
lemma_file=fopen(argv[2],"r");
if (!lemma_file) {
  fprintf(stderr,"I can't open file `%s' for reading!\n",argv[2]);
  exit(-3);
}                                       
printf("~ sat-mutex-distinct-lemmas %d %s\n",r,argv[3]);
@z
@x
    if (state[astep[k]].crit==0) /* a \.{maybe} step */
@y
    if (0) /* a \.{maybe} step can be treated as if it were \.{critical} */
@z
@x
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
@y
@ We can make a mild optimization, ruling out cases that obviously
don't change the state.

@<Generate clauses for when A is bumped in an \.{if} step@>=
{
  if (strncmp(state[astep[k]].name,state[astep[k]].lab,4)==0) {
    printf("~%03d@@ ~%03d%.4s %03d%.4s\n",
              t,t,state[astep[k]].name,tprime,state[astep[k]].elab);
    printf("~%03d@@ ~%03d%.4s %s%03d%.2s\n",
              t,t,state[astep[k]].name,
              state[astep[k]].val?"~":"",t,state[astep[k]].var);
  }@+else if(strncmp(state[astep[k]].name,state[astep[k]].elab,4)==0) {
    printf("~%03d@@ ~%03d%.4s %03d%.4s\n",
              t,t,state[astep[k]].name,tprime,state[astep[k]].lab);
    printf("~%03d@@ ~%03d%.4s %s%03d%.2s\n",
              t,t,state[astep[k]].name,
              state[astep[k]].val?"":"~",t,state[astep[k]].var);
  }@+else {
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
}
@z
@x
    if (state[bstep[k]].crit==0) /* a \.{maybe} step */
@y
    if (0) /* a \.{maybe} step can be treated as if it were \.{critical} */
@z
@x
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
@y
@ @<Generate clauses for when B is bumped in an \.{if} step@>=
{
  if (strncmp(state[bstep[k]].name,state[bstep[k]].lab,4)==0) {
    printf("%03d@@ ~%03d%.4s %03d%.4s\n",
              t,t,state[bstep[k]].name,tprime,state[bstep[k]].elab);
    printf("%03d@@ ~%03d%.4s %s%03d%.2s\n",
              t,t,state[bstep[k]].name,
              state[bstep[k]].val?"~":"",t,state[bstep[k]].var);
  }@+else if(strncmp(state[bstep[k]].name,state[bstep[k]].elab,4)==0) {
    printf("%03d@@ ~%03d%.4s %03d%.4s\n",
              t,t,state[bstep[k]].name,tprime,state[bstep[k]].lab);
    printf("%03d@@ ~%03d%.4s %s%03d%.2s\n",
              t,t,state[bstep[k]].name,
              state[bstep[k]].val?"":"~",t,state[bstep[k]].var);
  }@+else {
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
}
@z
@x
@*Index.
@y
@ Inequality between states $u$ and $v$ is indicated by variables
$u$$v$$\alpha$, where $u$ and $v$ are given as 2-digit codes and
$\alpha$ is either a state name or a variable name.

@<Generate clauses to ensure that $X_u!=X_{t+1}$@>=
{
  for (j=0;j<m;j++) {
    printf("~%02d%02d%.4s %03d%.4s\n",
                u,tprime,state[j].name,u,state[j].name);
    printf("~%02d%02d%.4s ~%03d%.4s\n",
                u,tprime,state[j].name,tprime,state[j].name);
  }
  for (j=0;j<n;j++) {
    printf("~%02d%02d%.2s %03d%.2s %03d%.2s\n",
               u,tprime,vars[j],u,vars[j],tprime,vars[j]);
    printf("~%02d%02d%.2s ~%03d%.2s ~%03d%.2s\n",
               u,tprime,vars[j],u,vars[j],tprime,vars[j]);
  }
  for (j=0;j<m;j++) printf(" %02d%02d%.4s",u,tprime,state[j].name);
  for (j=0;j<n;j++) printf(" %02d%02d%.2s",u,tprime,vars[j]);
  printf("\n");
}

@ If the $i$th lemma is $l_1\lor\cdots\lor l_k$, we essentially output
the clauses $l_{t1}\lor\cdots\lor l_{tk}$ for $0\le t\le r$. The effect is to
assert that this lemma is true until (and including) time~$r$.

@<Generate the clauses that deal with the lemmas@>=
for (i=1;;i++) {
  register char *p,*q;
  char hold;
  if (!fgets(buf,bufsize,lemma_file)) break;
  for (t=0;t<=r;t++)
    @<Generate the clauses for $\Phi(t)$@>;
}
fprintf(stderr,"(%d lemmas satisfactorily read and appended)\n",i-1);

@ @<Generate the clauses for $\Phi(t)$@>=
{
  for (p=buf;*p==' ';p++) ;
  while (*p!='\n') {
    if (*p=='~') j=1,p++;@+else j=0;
    for (q=p;*q!=' '&&*q!='\n';q++) ;
    hold=*q, *q='\0';
    printf(" %s%03d%s",j?"~":"",t,p);
    p=q, *p=hold;
    for (;*p==' ';p++) ;
  }
  printf("\n");
}

@ @<Disallow certain states based on parameter |p|@>=
if (p) {
  for (j=0;j<m;j++) if (state[j].var[0]==0 &&@|
      ((state[j].name[0]=='A' && p<0) || (state[j].name[0]=='B' && p>0))) {
    if (state[j].crit==0 || p<-1 || p>1)
      for (t=0;t<=r;t++) printf("~%03d%.4s\n",t,state[j].name);
  }
}

@*Index.
@z
