@x
@d nmax 1000
@y
This variant of the program actually omits $z$. It forms two copies of
the multiplier circuitry, and states that they produce different results.
(These clauses are clearly unsatisfiable, but the solver will have to
figure that out.)

@d nmax 1000
@z
@x
  printf("~ sat-dadda %d %d %s\n",m,n,argv[3]);
  @<Generate the unit clauses for $z$@>;
@y
  printf("~ sat-dadda-miter %d %d\n",m,n);
  @<Generate the difference clauses for $z$@>;
@z
@x
if (argc!=4 || sscanf(argv[1],"%d",&m)!=1 || sscanf(argv[2],"%d",&n)!=1) {
  fprintf(stderr,"Usage: %s m n z\n",argv[0]);
@y
if (argc!=3 || sscanf(argv[1],"%d",&m)!=1 || sscanf(argv[2],"%d",&n)!=1) {
  fprintf(stderr,"Usage: %s m n\n",argv[0]);
@z
@x
if (argv[3][0]<'0' || argv[3][0]>'9') {
  fprintf(stderr,"z must begin with a decimal digit, not '%c'!\n",argv[3][0]);
  exit(-4);
}
@y
@z
@x
@ @<Generate the unit clauses for $z$@>=
for (j=0;j<m+n;j++) {
  for (i=k=0;argv[3][i]>='0' && argv[3][i]<='9';i++) {
    l=argv[3][i]-'0'+k;
    k=(l&1? 10: 0);
    argv[3][i]='0'+(l>>1);
  }
  if (k) printf("Z%d\n",j+1);
  else printf("~Z%d\n",j+1);
}
if (argv[3][i]) {
  fprintf(stderr,"Warning: Junk found after the value of z: %s\n",argv[3]+i);
  argv[3][i]=0;
}
for (i=0;argv[3][i];i++) if (argv[3][i]!='0')
  fprintf(stderr,"Warning: z was truncated to %d bits\n",m+n);
@y
@ Variable \.{@@$k$} will be true only if there's a solution
with $\.{z$k$}=0$ and $\.{Z$k$}=1$.

@<Generate the difference clauses for $z$@>=
for (j=0;j<m+n;j++) {
  printf("~@@%d ~z%d\n",j+1,j+1);
  printf("~@@%d Z%d\n",j+1,j+1);
}
for (j=0;j<m+n;j++) printf(" @@%d",j+1);
printf("\n");
@z
@x
  if (k==2) make_and('Z',0,1,'X',0,i,'Y',0,j)@;
  else {
    l=count[k]=++size[k];
    bin[k][l-1]=l;
    make_and('A',k,l,'X',0,i,'Y',0,j);
@y
  if (k==2) {
    make_and('z',0,1,'X',0,i,'Y',0,j);
    make_and('Z',0,1,'X',0,i,'Y',0,j);
  }@+else {
    l=count[k]=++size[k];
    bin[k][l-1]=l;
    make_and('a',k,l,'X',0,i,'Y',0,j);
    make_and('A',k,l,'X',0,i,'Y',0,j);
@z
@x
  make_xor('Z',0,k-1,'A',k,bin[k][0],'A',k,bin[k][1]);
  if (k==m+n)
    make_and('Z',0,k,'A',k,bin[k][0],'A',k,bin[k][1])@;
  else {
    l=count[k+1]=++size[k+1], bin[k+1][l-1]=l;
    make_and('A',k+1,l,'A',k,bin[k][0],'A',k,bin[k][1]);
@y
  make_xor('z',0,k-1,'a',k,bin[k][0],'a',k,bin[k][1]);
  make_xor('Z',0,k-1,'A',k,bin[k][0],'A',k,bin[k][1]);
  if (k==m+n) {
    make_and('z',0,k,'a',k,bin[k][0],'a',k,bin[k][1]);
    make_and('Z',0,k,'A',k,bin[k][0],'A',k,bin[k][1]);
  }@+else {
    l=count[k+1]=++size[k+1], bin[k+1][l-1]=l;
    make_and('a',k+1,l,'a',k,bin[k][0],'a',k,bin[k][1]);
    make_and('A',k+1,l,'A',k,bin[k][0],'A',k,bin[k][1]);
@z
@x
  make_xor('S',k,i,'A',k,addend[0],'A',k,addend[1]);
  make_and('P',k,i,'A',k,addend[0],'A',k,addend[1]);
  l=++count[k], bin[k][size[k]++]=l;
  if (size[k]==1)
    make_xor('Z',0,k-1,'S',k,i,'A',k,addend[2])@;
  else make_xor('A',k,l,'S',k,i,'A',k,addend[2]);
  make_and('Q',k,i,'S',k,i,'A',k,addend[2]);
  if (k==m+n)
    make_or('Z',0,k,'P',k,i,'Q',k,i)@;
  else {
    l=count[k+1]=++size[k+1], bin[k+1][l-1]=l;
    make_or('A',k+1,l,'P',k,i,'Q',k,i);
@y
  make_xor('s',k,i,'a',k,addend[0],'a',k,addend[1]);
  make_xor('S',k,i,'A',k,addend[0],'A',k,addend[1]);
  make_and('p',k,i,'a',k,addend[0],'a',k,addend[1]);
  make_and('P',k,i,'A',k,addend[0],'A',k,addend[1]);
  l=++count[k], bin[k][size[k]++]=l;
  if (size[k]==1) {
    make_xor('z',0,k-1,'s',k,i,'a',k,addend[2])@;
    make_xor('Z',0,k-1,'S',k,i,'A',k,addend[2])@;
  }@+else {
    make_xor('a',k,l,'s',k,i,'a',k,addend[2]);
    make_xor('A',k,l,'S',k,i,'A',k,addend[2]);
  }
  make_and('q',k,i,'s',k,i,'a',k,addend[2]);
  make_and('Q',k,i,'S',k,i,'A',k,addend[2]);
  if (k==m+n) {
    make_or('z',0,k,'p',k,i,'q',k,i);
    make_or('Z',0,k,'P',k,i,'Q',k,i);
  }@+else {
    l=count[k+1]=++size[k+1], bin[k+1][l-1]=l;
    make_or('a',k+1,l,'p',k,i,'q',k,i);
    make_or('A',k+1,l,'P',k,i,'Q',k,i);
@z


