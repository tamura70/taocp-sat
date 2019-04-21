#define prime_char '\''
#define sharp_char '#' \

#define tarnished x.I
#define ename u.S \

/*1:*/
#line 13 "./sat-gates-stuck.w"

#include <stdlib.h> 
#include <string.h> 
#include "gb_graph.h"
#include "gb_gates.h"
#include "gb_save.h"
main(int argc,char*argv[]){
register int j,k;
register Graph*g;
register Vertex*u,*v,*w,*fault;
register Arc*a;
/*2:*/
#line 31 "./sat-gates-stuck.w"

if(argc!=3){
fprintf(stderr,"Usage: %s foo-wires.gb fault\n",argv[0]);
exit(-1);
}
g= restore_graph(argv[1]);
if(!g){
fprintf(stderr,"I couldn't reconstruct graph %s!\n",argv[1]);
exit(-2);
}
if(argv[2][0]!='0'&&argv[2][0]!='1'){
fprintf(stderr,"The fault name should begin with 0 or 1!\n");
exit(-3);
}

/*:2*/
#line 24 "./sat-gates-stuck.w"
;
/*3:*/
#line 52 "./sat-gates-stuck.w"

for(j= 0,v= g->vertices;v<g->vertices+g->n;v++){
for(k= 0;v->name[k];k++)
if(v->name[k]<'!'||v->name[k]> '~')break;
if(v->name[0]=='~'||k==0||v->name[k]){
fprintf(stderr,"Sorry, the wire name `%s' is illegal!\n",v->name);
j= 1;
}else if(k> 8){
fprintf(stderr,"Sorry, the wire name `%s' is too long!\n",v->name);
j= 1;
}else if(v->name[k-1]==prime_char||v->name[k-1]==sharp_char){
fprintf(stderr,
"Sorry, I don't like the last character of the wire name `%s'!\n",
v->name);
j= 1;
}else if(v->name[0]=='_'&&v->name[1]=='_'){
fprintf(stderr,"Sorry, I'm reserving wire names that begin with `__'!\n");
j= 1;
}
}
if(j)exit(-3);

/*:3*/
#line 25 "./sat-gates-stuck.w"
;
/*4:*/
#line 74 "./sat-gates-stuck.w"

for(v= g->vertices,fault= NULL;v<g->vertices+g->n;v++){
if(strcmp(v->name,argv[2]+1)==0){
fault= v;break;
}
}
if(!fault){
fprintf(stderr,"Sorry, I can't find a wire named `%s'!\n",
argv[2]+1);
exit(-4);
}

/*:4*/
#line 26 "./sat-gates-stuck.w"
;
/*5:*/
#line 107 "./sat-gates-stuck.w"

printf("~ sat-gates-stuck %s %s\n",argv[1],argv[2]);
for(v= g->vertices;v<g->vertices+g->n;v++){
v->tarnished= 0;
switch(v->typ){
case'I':break;
case'~':/*6:*/
#line 132 "./sat-gates-stuck.w"

if(v->arcs==NULL||v->arcs->next!=NULL){
fprintf(stderr,"The NOT gate %s should have only one argument!\n",v->name);
exit(-10);
}
u= v->arcs->tip;
printf("%s %s\n",v->name,u->ename);
printf("~%s ~%s\n",v->name,u->ename);
if(u->tarnished){
v->tarnished= 1;
printf("%s%c %s%c\n",v->name,prime_char,u->ename,prime_char);
printf("~%s%c ~%s%c\n",v->name,prime_char,u->ename,prime_char);
printf("~%s%c %s%c\n",u->name,sharp_char,v->name,sharp_char);
}

/*:6*/
#line 113 "./sat-gates-stuck.w"
;break;
case'&':/*7:*/
#line 147 "./sat-gates-stuck.w"

for(a= v->arcs;a;a= a->next){
u= a->tip;
printf("~%s %s\n",v->name,u->ename);
if(u->tarnished){
v->tarnished= 1;
printf("~%s%c %s%c\n",u->name,sharp_char,v->name,sharp_char);
}
}
printf("%s",v->name);
for(a= v->arcs;a;a= a->next)
printf(" ~%s",a->tip->ename);
printf("\n");
if(v->tarnished){
for(a= v->arcs;a;a= a->next){
u= a->tip;
if(u->tarnished)
printf("~%s%c %s%c\n",v->name,prime_char,u->ename,prime_char);
else printf("~%s%c %s\n",v->name,prime_char,u->ename);
}
printf("%s%c",v->name,prime_char);
for(a= v->arcs;a;a= a->next){
u= a->tip;
if(u->tarnished)printf(" ~%s%c",u->ename,prime_char);
else printf(" ~%s",u->ename);
}
printf("\n");
}

/*:7*/
#line 114 "./sat-gates-stuck.w"
;break;
case'|':/*8:*/
#line 176 "./sat-gates-stuck.w"

for(a= v->arcs;a;a= a->next){
u= a->tip;
printf("%s ~%s\n",v->name,u->ename);
if(u->tarnished){
v->tarnished= 1;
printf("~%s%c %s%c\n",u->name,sharp_char,v->name,sharp_char);
}
}
printf("~%s",v->name);
for(a= v->arcs;a;a= a->next)
printf(" %s",a->tip->ename);
printf("\n");
if(v->tarnished){
for(a= v->arcs;a;a= a->next){
u= a->tip;
if(u->tarnished)
printf("%s%c ~%s%c\n",v->name,prime_char,u->ename,prime_char);
else printf("%s%c ~%s\n",v->name,prime_char,u->ename);
}
printf("~%s%c",v->name,prime_char);
for(a= v->arcs;a;a= a->next){
u= a->tip;
if(u->tarnished)printf(" %s%c",u->ename,prime_char);
else printf(" %s",u->ename);
}
printf("\n");
}

/*:8*/
#line 115 "./sat-gates-stuck.w"
;break;
case'^':/*9:*/
#line 209 "./sat-gates-stuck.w"

for(k= 0,a= v->arcs;a;a= a->next)k++;
if(k!=2){
fprintf(stderr,"Sorry, I do XOR only of two operands, not %d (gate %s)!\n",
k,v->name);
exit(-5);
}
u= v->arcs->tip,w= v->arcs->next->tip;
printf("~%s %s %s\n",v->name,u->ename,w->ename);
printf("~%s ~%s ~%s\n",v->name,u->ename,w->ename);
printf("%s ~%s %s\n",v->name,u->ename,w->ename);
printf("%s %s ~%s\n",v->name,u->ename,w->ename);
if(u->tarnished){
v->tarnished= 1;
printf("~%s%c %s%c\n",u->name,sharp_char,v->name,sharp_char);
if(w->tarnished){
printf("~%s%c %s%c\n",w->name,sharp_char,v->name,sharp_char);
printf("~%s%c ~%s%c\n",u->name,sharp_char,w->name,sharp_char);
printf("~%s%c %s%c %s%c\n",v->name,prime_char,u->ename,prime_char,w->ename,prime_char);
printf("~%s%c ~%s%c ~%s%c\n",v->name,prime_char,u->ename,prime_char,w->ename,prime_char);
printf("%s%c ~%s%c %s%c\n",v->name,prime_char,u->ename,prime_char,w->ename,prime_char);
printf("%s%c %s%c ~%s%c\n",v->name,prime_char,u->ename,prime_char,w->ename,prime_char);
}else{
printf("~%s%c %s%c %s\n",v->name,prime_char,u->ename,prime_char,w->ename);
printf("~%s%c ~%s%c ~%s\n",v->name,prime_char,u->ename,prime_char,w->ename);
printf("%s%c ~%s%c %s\n",v->name,prime_char,u->ename,prime_char,w->ename);
printf("%s%c %s%c ~%s\n",v->name,prime_char,u->ename,prime_char,w->ename);
}
}else if(w->tarnished){
v->tarnished= 1;
printf("~%s%c %s%c\n",w->name,sharp_char,v->name,sharp_char);
printf("~%s%c %s%c %s\n",v->name,prime_char,w->ename,prime_char,u->ename);
printf("~%s%c ~%s%c ~%s\n",v->name,prime_char,w->ename,prime_char,u->ename);
printf("%s%c ~%s%c %s\n",v->name,prime_char,w->ename,prime_char,u->ename);
printf("%s%c %s%c ~%s\n",v->name,prime_char,w->ename,prime_char,u->ename);
}

/*:9*/
#line 116 "./sat-gates-stuck.w"
;break;
case'F':/*10:*/
#line 246 "./sat-gates-stuck.w"

if(!v->arcs||v->arcs->next){
fprintf(stderr,"Eh? A fanout gate should have a unique parent!\n");
exit(-6);
}
u= v->arcs->tip;
v->ename= u->ename;
v->tarnished= u->tarnished;
if((v-1)->typ=='F'&&(v-1)->arcs->tip==u){
if(v->tarnished)
printf("~%s%c %s%c %s%c\n",
u->name,sharp_char,(v-1)->name,sharp_char,v->name,sharp_char);
}else if((v+1)->typ!='F'||(v+1)->arcs->tip!=u){
fprintf(stderr,"Eh? Fanout gates should occur in pairs!\n");
exit(-7);
}

/*:10*/
#line 117 "./sat-gates-stuck.w"
;break;
default:fprintf(stderr,"Sorry, I don't know to handle type `%c' (wire %s)!\n",
(int)v->typ,v->name);
exit(-666);
}
if(v->typ!='F'){
v->ename= v->name;
if(v->tarnished){
printf("~%s%c ~%s ~%s%c\n",v->name,sharp_char,v->name,v->name,prime_char);
printf("~%s%c %s %s%c\n",v->name,sharp_char,v->name,v->name,prime_char);
}
}
if(v==fault)/*11:*/
#line 263 "./sat-gates-stuck.w"

{
v->tarnished= 1;
printf("%s%s%c\n",
argv[2][0]=='0'?"~":"",v->ename,prime_char);
printf("%s%s\n",
argv[2][0]=='0'?"":"~",v->ename);
printf("%s%c\n",
v->name,sharp_char);
}

/*:11*/
#line 129 "./sat-gates-stuck.w"
;
}

/*:5*/
#line 27 "./sat-gates-stuck.w"
;
/*12:*/
#line 281 "./sat-gates-stuck.w"

printf("__0\n");
for(k= 0,a= g->outs;a;a= a->next){
u= a->tip;
if(u->tarnished){
printf("%s%c ~__%d __%d\n",
u->name,sharp_char,k,k+1);
k++;
}
}
printf("~__%d\n",k);

/*:12*/
#line 28 "./sat-gates-stuck.w"
;
}

/*:1*/
