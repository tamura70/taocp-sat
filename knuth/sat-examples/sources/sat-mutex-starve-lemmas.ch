@x
simpler scheme.
@y
simpler scheme.

This version of the program does not try to find a violation of
the mutual exclusion property. Instead, it tries to find a
``starvation cycle,'' namely a cycle in which state~$X_k$
equals state~$X_0$, for some $k\le r$,
and for which the following
conditions hold: (1)~Both processes have been bumped at least once
in the cycle. (2)~At least one of the processes has executed neither a
\.{maybe} command nor a \.{critical} command within the cycle.

Furthermore we assume that a set of lemmas is given on an auxiliary input file.
These lemmas need not be invariant in the normal sense; but they must
be true in every state that we allow. In particular, these lemmas
will typically exclude states that are forbidden in a starvation cycle.
(They might, for example, include the unit clause `\.{\char`\~A0}' if
we are trying to starve process~A.) Condition~(2) is not actually
enforced by this program; it's only enforced by the lemmas.

We don't assume that $X_0$ is an initial state. We only assume that
it satisfies the given lemmas.
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
  @<Generate clauses to force concurrent critical sections at time |r|@>;
@y
  @<Generate clauses that deal with the lemmas@>;
  @<Generate clauses to force a starvation cycle@>;
@z
@x
if (argc!=2 || sscanf(argv[1],"%d",&r)!=1) {
  fprintf(stderr,"Usage: %s r < foo.dat\n",argv[0]);
  exit(-1);
}
@y
if (argc!=3 || sscanf(argv[1],"%d",&r)!=1) {
  fprintf(stderr,"Usage: %s r p foo.lemmas < foo.dat\n",argv[0]);
  exit(-1);
}
@z
@x
printf("~ sat-mutex %d\n",r);
@y
lemma_file=fopen(argv[2],"r");
if (!lemma_file) {
  fprintf(stderr,"I can't open file `%s' for reading!\n",argv[2]);
  exit(-3);
}                                       
printf("~ sat-mutex-starve-lemmas %d %s\n",r,argv[2]);
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
@ If the $i$th lemma is $l_1\lor\cdots\lor l_k$, we essentially output
the clauses $l_{t1}\lor\cdots\lor l_{tk}$ for $0\le t<r$, plus the 
clauses $\lnot\.{\char`\#$i$}\lor\lnot l_{rj}$. The effect is to
assert that this lemma is true until time~$r$, but if \.{\char`\#$i$}
holds then it fails at time~$r$. Finally we assert that at least one
lemma does fail at time~$r$.

@<Generate clauses that deal with the lemmas@>=
for (i=1;;i++) {
  register char *p,*q;
  char hold;
  if (!fgets(buf,bufsize,lemma_file)) break;
  for (t=0;t<=r;t++)
    @<Generate the clauses for $\Phi(t)$@>;
}

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

@ Here we introduce auxiliary variables \.{$t$U}, \.{$t$V}, and
$\.{$t$W}, meaning respectively
`$\hbox{\char`\@@}_0\lor\cdots\lor\hbox{\char`\@@}_{t-1}$',
`$\overline{\hbox{\char`\@@}_0}\lor\cdots\lor
   \overline{\hbox{\char`\@@}_{t-1}}$',
and `the first $t$ steps are a starvation cycle'.

@<Generate clauses to force a starvation cycle@>=
printf("~000U\n");
for (t=1;t<=r;t++) printf("~%03dU %03dU %03d@@\n",t,t-1,t-1);
printf("~000V\n");
for (t=1;t<=r;t++) printf("~%03dV %03dV ~%03d@@\n",t,t-1,t-1);
for (t=2;t<=r;t++) {
  printf("~%03dW %03dU\n",t,t);
  printf("~%03dW %03dV\n",t,t);
  for (j=0;j<m;j++) {
    printf("~%03dW 000%.4s ~%03d%.4s\n",t,state[j].name,t,state[j].name);
    printf("~%03dW ~000%.4s %03d%.4s\n",t,state[j].name,t,state[j].name);
  }
  for (j=0;j<n;j++) {
    printf("~%03dW 000%.2s ~%03d%.2s\n",t,vars[j],t,vars[j]);
    printf("~%03dW ~000%.2s %03d%.2s\n",t,vars[j],t,vars[j]);
  }
}
for (t=2;t<=r; t++) printf(" %03dW",t);
printf("\n");
@z
