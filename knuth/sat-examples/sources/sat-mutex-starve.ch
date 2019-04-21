@x
simpler scheme.
@y
simpler scheme.

This version of the program does not try to find a violation of
the mutual exclusion property. Instead, it tries to find a
``starvation cycle,'' namely a cycle in which the state at time~$r$
equals the state at a previous time~$p$, and for which the following
conditions hold: (1)~Both players have been bumped at least once
in the cycle. (2)~At least one of the players has executed neither a
\.{maybe} command nor a \.{critical} command within the cycle.

The ``starved'' player is A, if $p<0$; otherwise it's B.
@z
@x
int r; /* command-line parameter, the number of time steps to emulate */
@y
int r; /* command-line parameter, the number of time steps to emulate */
int p; /* command-line parameter, plus-or-minus the time when cycle begins */
int pp; /* absolute value of |p| */
@z
@x
  @<Generate clauses to force concurrent critical sections at time |r|@>;
@y
  @<Generate clauses to make the cycle legitimate@>;
@z
@x
if (argc!=2 || sscanf(argv[1],"%d",&r)!=1) {
  fprintf(stderr,"Usage: %s r < foo.dat\n",argv[0]);
  exit(-1);
}
@y
if (argc!=3 || sscanf(argv[1],"%d",&r)!=1 || sscanf(argv[2],"%d",&p)!=1) {
  fprintf(stderr,"Usage: %s r {+|-}p < foo.dat\n",argv[0]);
  exit(-1);
}
pp=p>0? p: -p;
@z
@x
printf("~ sat-mutex %d\n",r);
@y
printf("~ sat-mutex-starve %d %d\n",r,p);
@z
@x
  @<Generate clauses to forbid nonunique states for A at time |t+1|@>;
  @<Generate clauses to forbid nonunique states for B at time |t+1|@>;
@y
  if (t+1!=r) {
    @<Generate clauses to forbid nonunique states for A at time |t+1|@>;
    @<Generate clauses to forbid nonunique states for B at time |t+1|@>;
  }
@z
@x
@ @d tprime (t+1)
@y
@ @d tprime (t+1==r? pp: t+1)
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
@ @<Generate clauses to make the cycle legitimate@>=
for (j=pp;j<r;j++) printf(" ~%03d@@",j); /* at least one A turn */
printf("\n");
for (j=pp;j<r;j++) printf(" %03d@@",j); /* at least one B turn */
printf("\n");
for (j=0;j<m;j++) if (state[j].var[0]==0) { /* \.{maybe} or \.{critical} */
  if ((p<0 && state[j].name[0]=='A') || (p>0 && state[j].name[0]=='B'))
    for (k=pp;k<r;k++)
      printf("~%03d%.4s\n",k,state[j].name);
}

@z
