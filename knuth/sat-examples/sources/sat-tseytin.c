/*1:*/
#line 7 "./sat-tseytin.w"

#include "gb_graph.h" 
#include "gb_save.h" 
char bit[1000];
int main(int argc,char*argv[]){
register d,k,j;
register Graph*g;
register Vertex*u,*v;
register Arc*a;
/*2:*/
#line 20 "./sat-tseytin.w"

if(argc!=2){
fprintf(stderr,"Usage: %s foo.gb\n",argv[0]);
exit(-1);
}
g= restore_graph(argv[1]);
if(!g){
fprintf(stderr,"I couldn't reconstruct graph %s!\n",argv[1]);
exit(-2);
}
printf("~ sat-tseytin %s\n",argv[1]);

/*:2*/
#line 16 "./sat-tseytin.w"
;
/*3:*/
#line 40 "./sat-tseytin.w"

for(v= g->vertices;v<g->vertices+g->n;v++){
for(d= -1,a= v->arcs;a;a= a->next)d++;
while(1){
/*4:*/
#line 51 "./sat-tseytin.w"

for(j= (v> g->vertices),k= 0,a= v->arcs;a;a= a->next,j^= bit[k],k++){
printf(" ");
if(k==d)/*5:*/
#line 62 "./sat-tseytin.w"

{
if(j)printf("~");
}

/*:5*/
#line 54 "./sat-tseytin.w"

else if(bit[k])printf("~");
u= a->tip;
if(u<v)printf("%s.%s",u->name,v->name);
else printf("%s.%s",v->name,u->name);
}
printf("\n");

/*:4*/
#line 44 "./sat-tseytin.w"
;
for(k= 0;bit[k];k++)bit[k]= 0;
if(k==d)break;
bit[k]= 1;
}
}

/*:3*/
#line 17 "./sat-tseytin.w"
;
}

/*:1*/
