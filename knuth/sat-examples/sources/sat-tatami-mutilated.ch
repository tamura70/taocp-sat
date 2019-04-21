@x
The variables are \.{$i$H$j$} and \.{$i$V$j$},
@y
Well, no: This variant simply asks for an exact covering by dominoes.
And instead of reading a \.{dots} file, it works with an $m\times n$
chessboard, minus two cells on opposite corners.

The variables are \.{$i$H$j$} and \.{$i$V$j$},
@z
@x
main() {
  register int i,j,k,x,y;
  @<Input the pattern@>;
  printf("~ sat-tatami (%dx%d)\n",
                     xmax,ymax);
  @<Generate the clauses for domino covering@>;
  @<Generate the clauses to assert the tatami condition@>;
}
@y
main(int argc, char*argv[]) {
  register int i,j,k,x,y;
  @<Process the command line@>;
  printf("~ sat-tatami-mutilated %d %d\n",
                     xmax,ymax);
  @<Generate the clauses for domino covering@>;
}
@z
@x
@*Index.
@y
@ @<Process the command line@>=
if (argc!=3 || sscanf(argv[1],"%d",&xmax)!=1
            || sscanf(argv[2],"%d",&ymax)!=1) {
  fprintf(stderr,"Usage: %s m n\n",argv[0]);
  exit(-1);
}
if (xmax>maxx) {
  fprintf(stderr,"Sorry, the pattern should have at most %d rows!\n",maxx);
  exit(-3);
}
if (ymax>maxy) {
  fprintf(stderr,"Sorry, the pattern should have at most %d columns!\n",
         maxy);
  exit(-4);
}
xmin=ymin=1;
for (x=1;x<=xmax;x++) for (y=1;y<=ymax;y++)
  if ((x!=1 || y!=ymax) && (x!=xmax || y!=1)) p[x][y]=1;

@*Index.
@z
