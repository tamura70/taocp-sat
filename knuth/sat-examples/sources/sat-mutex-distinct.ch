@x
To test this, I'll see if certain extensions of the clauses are satisfiable.
@y
To test this, I'll see if certain extensions of the clauses are satisfiable.

The present program generates extra clauses to see if it's possible
to have $r+1$ {\it distinct} states $X_0\to X_1\to\cdots\to X_r$.
Here $X_0$ is the initial state; I don't require $X_r$ to violate the
mutual exclusion property.
@z
@x
  for (t=0;t<r;t++)
    @<Generate the transitions from time |t| to time |t+1|@>;
  @<Generate clauses to force concurrent critical sections at time |r|@>;
@y
  for (t=0;t<r;t++) {
    register int u;
    @<Generate the transitions from time |t| to time |t+1|@>;
    for (u=0;u<=t;u++)
      @<Generate clauses to ensure that $X_u!=X_{t+1}$@>;
  }
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
printf("~ sat-mutex-distinct %d\n",r);
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
@z
