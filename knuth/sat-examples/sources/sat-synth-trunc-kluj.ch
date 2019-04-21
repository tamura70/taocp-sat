@x
int K,N; /* command-line parameters */
@y
int K,N,cutoff; /* command-line parameters */
int perm_swap[]={0,1,2,0,2,1,0,2,0,1,2,0,2,1,0,2,0,1,2,0,2,1,0};
int perm[]={1,2,3,4};
int dat[4][21];
@z
@x
  register int i,j,k,t;
@y
  register int i,j,k,t,count;
@z
@x
  printf("~ sat-synth %d %d\n",N,K);
@y
  printf("~ sat-synth-trunc-kluj %d %d %d\n",N,K,cutoff);
  @<Print 24 solution-excluding lines@>;
@z
@x
  while (1) {
@y
  for (count=0;count<cutoff;count++) {
@z
@x
if (argc!=3 || sscanf(argv[1],""O"d",&N)!=1 ||
               sscanf(argv[2],""O"d",&K)!=1) {
  fprintf(stderr,"Usage: "O"s N K\n",argv[0]);
@y
if (argc!=4 || sscanf(argv[1],""O"d",&N)!=1 ||
               sscanf(argv[2],""O"d",&K)!=1 ||
               sscanf(argv[3],""O"d",&cutoff)!=1) {
  fprintf(stderr,"Usage: "O"s N K cutoff\n",argv[0]);
@z
@x
@*Index.
@y
@ @<Print 24 solution-excluding lines@>=
dat[0][2]=dat[0][3]=dat[0][10]=-1; /* $\bar x_2\bar x_3\bar x_{10}$ */
dat[1][6]=dat[1][10]=dat[1][12]=-1; /* $\bar x_6\bar x_{10}\bar x_{12}$ */
dat[2][8]=1,dat[2][13]=dat[2][15]=-1; /* $x_8\bar x_{13}\bar x_{15}$ */
dat[3][10]=1,dat[3][8]=dat[3][12]=-1; /* $\bar x_8 x_{10}\bar x_{12}$ */
for (i=0;;i++) {
  for (j=0;j<4;j++) for (k=1;k<=20;k++) {
    if (dat[j][k]>0)
      printf(" ~"O"d+"O"d "O"d-"O"d",perm[j],k,perm[j],k);
    else if (dat[j][k]<0)
      printf(" "O"d+"O"d ~"O"d-"O"d",perm[j],k,perm[j],k);        
    else printf(" "O"d+"O"d "O"d-"O"d",perm[j],k,perm[j],k);
  }
  printf("\n");
  if (i==23) break;
  j=perm_swap[i];
  k=perm[j], perm[j]=perm[j+1], perm[j+1]=k;
}

@*Index.
@z
