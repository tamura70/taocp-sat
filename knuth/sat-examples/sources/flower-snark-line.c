#define avert(j) (g->vertices+(6*(j) -6) ) 
#define bvert(j) (g->vertices+(6*(j) -5) ) 
#define cvert(j) (g->vertices+(6*(j) -4) ) 
#define dvert(j) (g->vertices+(6*(j) -3) ) 
#define evert(j) (g->vertices+(6*(j) -2) ) 
#define fvert(j) (g->vertices+(6*(j) -1) )  \

#define incr(j) ((j) ==n?1:(j) +1)  \

/*1:*/
#line 14 "./flower-snark-line.w"

#include "gb_graph.h" 
#include "gb_save.h" 
int n;
char buf[16];
int main(int argc,char*argv[]){
register int i,j,k;
register Graph*g;
/*2:*/
#line 31 "./flower-snark-line.w"

if(argc!=2||sscanf(argv[1],"%d",&n)!=1){
fprintf(stderr,"Usage: %s n\n",argv[0]);
exit(-1);
}

/*:2*/
#line 22 "./flower-snark-line.w"
;
/*3:*/
#line 44 "./flower-snark-line.w"

g= gb_new_graph(6*n);
if(!g){
fprintf(stderr,"Can't create an empty graph of %d vertices!\n",6*n);
exit(-2);
}
for(j= 1;j<=n;j++){
sprintf(buf,"a%d",j);
avert(j)->name= gb_save_string(buf);
sprintf(buf,"b%d",j);
bvert(j)->name= gb_save_string(buf);
sprintf(buf,"c%d",j);
cvert(j)->name= gb_save_string(buf);
sprintf(buf,"d%d",j);
dvert(j)->name= gb_save_string(buf);
sprintf(buf,"e%d",j);
evert(j)->name= gb_save_string(buf);
sprintf(buf,"f%d",j);
fvert(j)->name= gb_save_string(buf);
}

/*:3*/
#line 23 "./flower-snark-line.w"
;
for(j= 1;j<=n;j++)
/*4:*/
#line 67 "./flower-snark-line.w"

{
gb_new_edge(avert(j),avert(incr(j)),1);
gb_new_edge(avert(j),bvert(j),1);
gb_new_edge(avert(j),bvert(incr(j)),1);
gb_new_edge(bvert(j),cvert(j),1);
gb_new_edge(bvert(j),dvert(j),1);
gb_new_edge(cvert(j),dvert(j),1);
gb_new_edge(cvert(j),evert(j),1);
gb_new_edge(dvert(j),fvert(j),1);
gb_new_edge(evert(j),dvert(incr(j)),1);
gb_new_edge(evert(j),fvert(incr(j)),1);
gb_new_edge(fvert(j),cvert(incr(j)),1);
gb_new_edge(fvert(j),evert(incr(j)),1);
}

/*:4*/
#line 25 "./flower-snark-line.w"
;
sprintf(g->id,"flowersnarkline(%d)",n);
sprintf(buf,"fsnarkline%d.gb",n);
save_graph(g,buf);
}

/*:1*/
