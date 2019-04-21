/*1:*/
#line 15 "./word_components.w"

#line 46 "./word_giant.ch"
#include "gb_graph.h" 
#include "gb_save.h" 
#include "gb_basic.h" 
#line 17 "./word_components.w"
#include "gb_words.h" 
#define link z.V
#define master y.V
#define size x.I \


#line 18 "./word_components.w"

main()
{Graph*g= words(0L,0L,0L,0L);
Vertex*v;
Arc*a;
long n= 0;
long isol= 0;
long comp= 0;
long m= 0;
#line 61 "./word_giant.ch"
for(v= g->vertices;v<g->vertices+g->n;v++){
n++;
/*2:*/
#line 42 "./word_components.w"

/*3:*/
#line 74 "./word_components.w"

v->link= v;
v->master= v;
v->size= 1;
isol++;
comp++;

/*:3*/
#line 43 "./word_components.w"
;
a= v->arcs;
while(a&&a->tip> v)a= a->next;
#line 81 "./word_giant.ch"
for(;a;a= a->next){register Vertex*u= a->tip;
register int k= a->loc;
register char*p= v->name+k,*q= u->name+k;
if(*p<*q)a->len= (a-1)->len= *q-*p;
else a->len= (a-1)->len= *p-*q;
m++;
/*4:*/
#line 85 "./word_components.w"

u= u->master;
if(u!=v->master){register Vertex*w= v->master,*t;
if(u->size<w->size){
#line 90 "./word_components.w"
w->size+= u->size;
if(u->size==1)isol--;
for(t= u->link;t!=u;t= t->link)t->master= w;
u->master= w;
}else{
#line 96 "./word_components.w"
if(u->size==1)isol--;
u->size+= w->size;
if(w->size==1)isol--;
for(t= w->link;t!=w;t= t->link)t->master= u;
w->master= u;
}
t= u->link;
u->link= w->link;
w->link= t;
comp--;
}

/*:4*/
#line 87 "./word_giant.ch"
;
}
#line 55 "./word_components.w"

/*:2*/
#line 64 "./word_giant.ch"
;
}
/*5:*/
#line 121 "./word_giant.ch"

for(v= g->vertices;v<g->vertices+g->n;v++)
if(v->master->size+v->master->size<g->n)v->ind= 0;
else v->ind= 1;
#line 125 "./word_components.w"

/*:5*/
#line 66 "./word_giant.ch"
;
save_graph(induced(g,"giant",0,0,0),"word_giant.gb");
#line 35 "./word_components.w"
return 0;
}

/*:1*/
