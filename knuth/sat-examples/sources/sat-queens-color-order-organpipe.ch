@x a change file for sat-queens-color-order-cliques2
it can be used twice: I generate also a random permutation and
@y
it can be used twice: I generate also the organpipe permutation and
@z
@x
if (argc!=4 || sscanf(argv[1],"%d",&n)!=1
            || sscanf(argv[2],"%d",&d)!=1
            || sscanf(argv[3],"%d",&seed)!=1) {
  fprintf(stderr,"Usage: %s n d seed\n",argv[0]);
@y
if (argc!=3 || sscanf(argv[1],"%d",&n)!=1
            || sscanf(argv[2],"%d",&d)!=1) {
  fprintf(stderr,"Usage: %s n d\n",argv[0]);
@z
@x
gb_init_rand(seed);
printf("~ sat-queens-color-order-cliques2 %d %d %d\n",n,d,seed);

@ @<Set up the new permutation@>=
for (i=1;i<d;i++) {
  j=gb_unif_rand(i+1);
  perm[i]=perm[j];
  perm[j]=i;
}
@y
printf("~ sat-queens-color-order-organpipe %d %d\n",n,d);

@ @<Set up the new permutation@>=
for (i=0,j=d-1;i<j;i++,j--)
  perm[i]=i+i, perm[j]=i+i+1;
if (i==j) perm[i]=i+i;
@z
