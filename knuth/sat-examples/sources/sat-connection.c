#define bufsize 80 \

#define seen z.I \

/*1:*/
#line 47 "./sat-connection.w"

#include <stdio.h> 
#include <stdlib.h> 
#include "gb_graph.h"
#include "gb_save.h"
char buf[bufsize];
char namew[bufsize],namez[bufsize];
char code[]= 
"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
main(int argc,char*argv[]){
register int j,t,m,mm;
register Graph*g;
register Vertex*v,*w,*z;
register Arc*a,*b,*c;
register char*p,*q;
/*2:*/
#line 71 "./sat-connection.w"

if(argc!=2){
fprintf(stderr,"Usage: %s foo.gb\n",
argv[0]);
exit(-1);
}
g= restore_graph(argv[1]);
if(!g){
fprintf(stderr,"I couldn't reconstruct graph %s!\n",argv[1]);
exit(-2);
}
hash_setup(g);
printf("~ sat-connection %s\n",
argv[1]);

/*:2*/
#line 62 "./sat-connection.w"
;
/*3:*/
#line 88 "./sat-connection.w"

for(v= g->vertices;v<g->vertices+g->n;v++)v->seen= 0;

/*:3*/
#line 63 "./sat-connection.w"
;
for(m= 0,t= 1;;t++){
if(!fgets(buf,bufsize,stdin))break;
/*4:*/
#line 91 "./sat-connection.w"

mm= m;
for(p= buf;*p==' ';p++);
if(*p=='\n')
fprintf(stderr,"Warning: An empty line of input is being ignored!\n");
else{
for(namew[0]= *p,q= p+1;*q!=' '&&*q!='\n';q++)namew[q-p]= *q;
namew[q-p]= '\0';
if(q-p> 7){
fprintf(stderr,"Sorry, the name of vertex %s is too long!\n",
namew);
exit(-3);
}
w= hash_out(namew);
if(!w){
fprintf(stderr,"Vertex %s isn't in that graph!\n",
namew);
exit(-33);
}
if(w->seen){
fprintf(stderr,"Vertex %s has already occurred!\n",
namew);
exit(-6);
}
w->seen= 1;
while(1){
for(p= q;*p==' ';p++);
if(*p=='\n')break;
for(namez[0]= *p,q= p+1;*q!=' '&&*q!='\n';q++)namez[q-p]= *q;
namez[q-p]= '\0';
if(q-p> 7){
fprintf(stderr,"Sorry, the name of vertex %s is too long!\n",
namez);
exit(-4);
}
z= hash_out(namez);
if(!z){
fprintf(stderr,"Vertex %s isn't in that graph!\n",
namez);
exit(-44);
}
if(z->seen){
fprintf(stderr,"Vertex %s has already occurred!\n",
namez);
exit(-66);
}
z->seen= 1;
if(!code[m]){
fprintf(stderr,"Sorry, I can't handle this many cases!\n");
fprintf(stderr,"Recompile me with a longer code string.\n");
exit(-5);
}
printf("~ step %c, connecting %s to %s\n",
code[m],namew,namez);
/*5:*/
#line 155 "./sat-connection.w"

for(v= g->vertices;v<g->vertices+g->n;v++)for(j= 0;j<mm;j++)
printf("~%s%c ~%s%c\n",
v->name,code[m],v->name,code[j]);
for(v= g->vertices;v<g->vertices+g->n;v++){
if(v==w||v==z)/*6:*/
#line 167 "./sat-connection.w"

{
printf("%s%c\n",
v->name,code[m]);
for(a= v->arcs;a;a= a->next)
printf(" %s%c",
a->tip->name,code[m]);
printf("\n");
for(a= v->arcs;a;a= a->next)for(b= a->next;b;b= b->next)
printf("~%s%c ~%s%c\n",
a->tip->name,code[m],b->tip->name,code[m]);

}

/*:6*/
#line 160 "./sat-connection.w"

else{
/*7:*/
#line 181 "./sat-connection.w"

for(a= v->arcs;a;a= a->next){
printf("~%s%c",
v->name,code[m]);
for(b= v->arcs;b;b= b->next)if(a!=b)
printf(" %s%c",
b->tip->name,code[m]);
printf("\n");
}

/*:7*/
#line 162 "./sat-connection.w"
;
/*8:*/
#line 191 "./sat-connection.w"

for(a= v->arcs;a;a= a->next)
for(b= a->next;b;b= b->next)
for(c= b->next;c;c= c->next)
printf("~%s%c ~%s%c ~%s%c ~%s%c\n",
v->name,code[m],
a->tip->name,code[m],b->tip->name,code[m],c->tip->name,code[m]);

/*:8*/
#line 163 "./sat-connection.w"
;
}
}

/*:5*/
#line 145 "./sat-connection.w"
;
m++;
}
if(mm==m){
w->seen= -1;
printf("~ singleton vertex %s\n",
namew);
}
}

/*:4*/
#line 66 "./sat-connection.w"
;
}
/*9:*/
#line 205 "./sat-connection.w"

for(v= g->vertices;v<g->vertices+g->n;v++)if(v->seen==-1)
for(j= 0;j<m;j++)printf("~%s%c\n",
v->name,code[j]);

/*:9*/
#line 68 "./sat-connection.w"
;
}

/*:1*/
