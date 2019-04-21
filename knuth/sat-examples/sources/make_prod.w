@i gb_types.w

@* Making a graph.
I'm just creating a file \.{/tmp/prod,m,n.gb}, where $m$ and $n$
appear on the command line.

@p
#include "gb_graph.h" /* we use the {\sc GB\_\,GRAPH} data structures */
#include "gb_gates.h" /* and the product graph generator */
#include "gb_save.h" /* and we save our results in ASCII format */
long m,n;
char buf[100];
@#
int main(int argc, char* argv[])
{@+Graph *g,*gg,*ggg;
  if (argc!=3 || sscanf(argv[1],"%ld",&m)!=1 ||
                 sscanf(argv[2],"%ld",&n)!=1) {
    fprintf(stderr,"Usage: %s m n\n",argv[0]);
    exit(-1);
  }
  g=prod(m,n);
  sprintf(buf,"/tmp/prod,%ld,%ld.gb",m,n);
  save_graph(g,buf); /* generate an ASCII file for it */
  return 0; /* normal exit */
}

@* Index.
