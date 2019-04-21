#define deg u.I \

/*1:*/
#line 50 "./gates-to-wires.w"

#include "gb_graph.h"
#include "gb_gates.h"
#include "gb_save.h"
FILE*in_file,*out_file;
char buf[1000];
main(int argc,char*argv[]){
register int i,j,k,n,r,s;
register Vertex*u,*v,*w;
register Arc*a,*b,*aa;
register Graph*g,*gg;
/*2:*/
#line 70 "./gates-to-wires.w"

if(argc!=3){
fprintf(stderr,"Usage: %s gates-in.gb wires-out.gb\n",argv[0]);
exit(-1);
}
g= restore_graph(argv[1]);
if(!g){
fprintf(stderr,"I can't restore the graph `%s'!\n",
argv[1]);
exit(-2);
}

/*:2*/
#line 61 "./gates-to-wires.w"
;
/*3:*/
#line 84 "./gates-to-wires.w"

for(k= 0,v= g->vertices;v<g->vertices+g->n;v++){
v->deg= 0;
if(v->typ=='L'){
v->typ= 'I';
a= gb_virgin_arc();
a->next= g->outs;
a->tip= v->alt;
g->outs= a;
}
else if(v->typ!='I'){
for(a= v->arcs;a;a= a->next)
k++,a->tip->deg++;
}
}
for(a= g->outs;a;a= a->next)
k++,a->tip->deg++;

/*:3*/
#line 62 "./gates-to-wires.w"
;
/*4:*/
#line 102 "./gates-to-wires.w"

gg= gb_new_graph(2*k-g->n);
if(!gg){
fprintf(stderr,"I couldn't create a new graph!\n");
exit(-99);
}
make_compound_id(gg,"",g,"|wires");
for(u= g->vertices,v= gg->vertices;u<g->vertices+g->n;u++){
v->name= gb_save_string(u->name);
v->typ= u->typ;
u->alt= v;
for(a= u->arcs;a;a= a->next){
w= a->tip->alt;
a->tip->alt++;
gb_new_arc(v,w,a->len);
}
k= (u->deg)-1,v++;
for(j= 0;j<k;j++){
sprintf(buf,"%s#%d",u->name,2*j+1);
v->name= gb_save_string(buf);
v->typ= 'F';
gb_new_arc(v,u->alt,0);
v++;
sprintf(buf,"%s#%d",u->name,2*j+2);
v->name= gb_save_string(buf);
v->typ= 'F';
gb_new_arc(v,u->alt,0);
v++;
u->alt++;
}
}
/*5:*/
#line 138 "./gates-to-wires.w"

for(b= NULL,a= g->outs;a;a= aa){
aa= a->next;
a->next= b;
b= a;
}
for(;b;b= b->next){
a= gb_virgin_arc();
w= b->tip;
a->tip= w->alt;
w->alt++;
a->next= gg->outs;
gg->outs= a;
}



/*:5*/
#line 133 "./gates-to-wires.w"
;

/*:4*/
#line 63 "./gates-to-wires.w"
;
strcpy(gg->util_types,g->util_types);
s= save_graph(gg,argv[2]);
if(s)fprintf(stderr,"Output written to %s (anomalies %x!)\n",argv[2],s);
else fprintf(stderr,"Output written to %s\n",argv[2]);
}

/*:1*/
