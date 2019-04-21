@x
int m,n,t; /* command-line parameters */
@y
int m,n,t; /* command-line parameters */
int scale; /* we'll divide each input weight by this much */
@z
@x
  register int i,j,ii,jj,k,l;
@y
  register int i,j,ii,jj,k,l,reflectionsymmetryused=0;
@z
@x
if (argc!=4 ||
      sscanf(argv[1],"%d",&m)!=1 ||
      sscanf(argv[2],"%d",&n)!=1 ||
      sscanf(argv[3],"%d",&t)!=1) {
  fprintf(stderr,"Usage: %s m n t < w[m][n]\n", argv[0]);
@y
if (argc!=5 ||
      sscanf(argv[1],"%d",&m)!=1 ||
      sscanf(argv[2],"%d",&n)!=1 ||
      sscanf(argv[3],"%d",&t)!=1 ||
      sscanf(argv[4],"%d",&scale)!=1) {
  fprintf(stderr,"Usage: %s m n t scale < w[m][n]\n", argv[0]);
@z
@x
    if (w[i][j]<0 || w[i][j]>t) {
@y
    w[i][j]/=scale;
    if (w[i][j]<0 || w[i][j]>t) {
@z
@x
printf("~ sat-oss %d %d %d\n",m,n,t);
@y
printf("~ sat-oss-sym-scaled %d %d %d %d\n",m,n,t,scale);
@z
@x
      for (l=0;l+w[i][j]<=t+1-w[ii][jj];l++) {
@y
      if (!reflectionsymmetryused) 
        reflectionsymmetryused=1,printf("!%c%c%c%c\n",
                                    '0'+i,'0'+j,'0'+ii,'0'+jj);
      for (l=0;l+w[i][j]<=t+1-w[ii][jj];l++) {
@z
