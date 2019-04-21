/*1:*/
#line 12 "./queen-graph.w"

#include "gb_graph.h" 
#include "gb_basic.h" 
#include "gb_save.h" 

long n;
char buf[100];
main(int argc,char*argv[])
{Graph*g,*gg,*ggg;
/*2:*/
#line 30 "./queen-graph.w"

if(argc!=2||sscanf(argv[1],"%ld",&n)!=1){
fprintf(stderr,"Usage: %s n\n",argv[0]);
exit(-1);
}

/*:2*/
#line 21 "./queen-graph.w"
;
g= board(n,n,0L,0L,-1L,0L,0L);
gg= board(n,n,0L,0L,-2L,0L,0L);
ggg= gunion(g,gg,0L,0L);
sprintf(buf,"queen%ldx%ld.gb",n,n);
save_graph(ggg,buf);
return 0;
}

/*:1*/
