/*1:*/
#line 7 "./make_prod.w"

#include "gb_graph.h" 
#include "gb_gates.h" 
#include "gb_save.h" 
long m,n;
char buf[100];

int main(int argc,char*argv[])
{Graph*g,*gg,*ggg;
if(argc!=3||sscanf(argv[1],"%ld",&m)!=1||
sscanf(argv[2],"%ld",&n)!=1){
fprintf(stderr,"Usage: %s m n\n",argv[0]);
exit(-1);
}
g= prod(m,n);
sprintf(buf,"/tmp/prod,%ld,%ld.gb",m,n);
save_graph(g,buf);
return 0;
}

/*:1*/
