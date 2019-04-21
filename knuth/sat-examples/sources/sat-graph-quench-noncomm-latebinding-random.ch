@x
@d nmax 256
@y
Additional clauses that enforce left-to-right order for commutative moves
are included.

This version of the program implements ``late binding solitaire,'' a game
that I made up long ago (and used as a warmup problem when I taught
Stanford's CS problem seminar in 1989). We're given a sequence of playing
cards, chosen at random. The cards have two-letter names; for example,
\.{Ah} is the ace of hearts,
\.{6s} is the six of spades,
\.{Td} is the ten of diamonds.
Two cards are adjacent in the graph if and only
if they agree in suit or rank.

@d nmax 256
@z
@x
main(int argc, char*argv[]) {
@y
#include <string.h>
#include "gb_flip.h"
char* cardname[52]={
"Ac","2c","3c","4c","5c","6c","7c","8c","9c","Tc","Jc","Qc","Kc",
"Ad","2d","3d","4d","5d","6d","7d","8d","9d","Td","Jd","Qd","Kd",
"Ah","2h","3h","4h","5h","6h","7h","8h","9h","Th","Jh","Qh","Kh",
"As","2s","3s","4s","5s","6s","7s","8s","9s","Ts","Js","Qs","Ks"};
int seed;
main(int argc, char*argv[]) {
  register char* tt;
@z
@x
  @<Generate the enabling clauses@>;
@y
  @<Generate the enabling clauses@>;
  @<Generate the noncommutativity clauses@>;
@z
@x
@ @<Process the command line@>=
if (argc!=2) {
  fprintf(stderr,"Usage: %s foo.gb\n",argv[0]);
  exit(-1);
}
g=restore_graph(argv[1]);
if (!g) {
  fprintf(stderr,"I couldn't reconstruct graph %s!\n",argv[1]);
  exit(-2);
}
n=g->n;
if (n>nmax) {
  fprintf(stderr,"Sorry, that graph has too many vertices (%d>%d)!\n",
                                             n,nmax);
  exit(-3);
}
printf("~ sat-graph-quench %s\n",argv[1]);
@y
@ @<Process the command line@>=
if (argc!=2 || sscanf(argv[1],"%d",&seed)!=1) {
  fprintf(stderr,"Usage: %s seed\n",argv[0]);
  exit(-1);
}
gb_init_rand(seed);
n=18;
for (j=0;j<n;j++) {
  i=j+gb_unif_rand(52-j);
  tt=cardname[i],cardname[i]=cardname[j],cardname[j]=tt;
}
printf("~ sat-graph-quench-noncomm-latebinding-random %d\n",seed);
printf("~");
for (j=0;j<n;j++) printf(" %s",cardname[j]);
printf("\n");
@z
@x
@<Specify the initial nonadjacencies@>=
for (v=g->vertices;v<g->vertices+n;v++) v->stamp=0;
for (v=g->vertices,j=1;v<g->vertices+n;v++,j++) {
  for (a=v->arcs;a;a=a->next) if (a->tip>v)
    a->tip->stamp=j;
  for (w=v+1;w<g->vertices+n;w++) if (w->stamp!=j)
    printf("~00%02x%02x\n",
                (unsigned int)(v-g->vertices),(unsigned int)(w-g->vertices));
}
@y
@<Specify the initial nonadjacencies@>=
for (i=0;i<n;i++) for (j=i+1;j<n;j++) {
  if (cardname[i][0]==cardname[j][0]) continue;
  if (cardname[i][1]==cardname[j][1]) continue;
  printf("~00%02x%02x\n",
                i,j);
}
@z
@x
@*Index.
@y
@ The commutativity relations, when $t'=t+1$ and $j'=j+1$, are:
$\.{$t$Q$i$}\land\.{$t'$Q$j$}=\.{$t$Q$j'$}\land\.{$t'$Q$i$}$, if $i<j$;
$\.{$t$S$i$}\land\.{$t'$S$j$}=\.{$t$S$j'$}\land\.{$t'$S$i$}$, if $i+2<j$;
$\.{$t$Q$i$}\land\.{$t'$S$j$}=\.{$t$S$j'$}\land\.{$t'$Q$i$}$, if $i<j$;
$\.{$t$S$i$}\land\.{$t'$Q$j$}=\.{$t$Q$j'$}\land\.{$t'$S$i$}$, if $i+2<j$;
and (surprise!)
$\.{$t$S$i$}\land\.{$t'$S$i$}=\.{$t$Q$(i+3)$}\land\.{$t'$S$i$}$.
Furthermore, there also is commutativity in the cases
$\.{$t$Q$i$}\land\.{$t'$Q$i$}=\.{$t$Q$(i+1)$}\land\.{$t'$Q$i$}$,
$\.{$t$S$i$}\land\.{$t'$Q$(i-1)$}=\.{$t$Q$i$}\land\.{$t'$S$(i-1)}$,
but {\it only\/} when both sides are applicable. If only one of the
two sides can be applied because of current adjacencies, we will
allow it; otherwise we will allow only the alternative on the left
of each of these identities.

@<Generate the noncommutativity clauses@>=
for (t=0;t<=n-3;t++) {
  for (i=0;i<=n-t-2;i++) for (j=i+2;j<=n-t-2;j++)
    printf("~%02xQ%02x ~%02xQ%02x\n",
                 t,j,t+1,i);
  for (i=0;i<=n-t-2;i++) for (j=i+2;j<=n-t-4;j++)
    printf("~%02xS%02x ~%02xQ%02x\n",
                 t,j,t+1,i);
  for (i=0;i<=n-t-4;i++) for (j=i+4;j<=n-t-4;j++)
    printf("~%02xS%02x ~%02xS%02x\n",
                 t,j,t+1,i);
  for (i=0;i<=n-t-4;i++) for (j=i+3;j<=n-t-2;j++)
    printf("~%02xQ%02x ~%02xS%02x\n",
                 t,j,t+1,i);
  for (j=1;j<=n-t-2;j++)
    printf("~%02xQ%02x ~%02xQ%02x ~%02x%02x%02x\n",
                 t,j,t+1,j-1,t,j-1,j);
  for (j=1;j<=n-t-4;j++)
    printf("~%02xQ%02x ~%02xS%02x ~%02x%02x%02x\n",
                 t,j,t+1,j-1,t,j,j+3);
}   

@*Index.
@z
