#define max_level 150
#define max_degree 1000
#define max_cols 10000
#define max_nodes 1000000 \

#define root col_array[0] \

#define buf_size 4*max_cols+3 \

#define panic(m) {fprintf(stderr,"%s!\n%s",m,buf) ;exit(-1) ;} \

/*1:*/
#line 26 "./sat-dance.w"

#include <stdio.h> 
#include <stdlib.h> 
#include <ctype.h> 
#include <string.h> 
/*2:*/
#line 61 "./sat-dance.w"

typedef struct node_struct{
struct node_struct*left,*right;
struct node_struct*up,*down;
struct col_struct*col;
int num;
}node;

/*:2*//*3:*/
#line 76 "./sat-dance.w"

typedef struct col_struct{
node head;
int len;
char name[8];
struct col_struct*prev,*next;
}column;

/*:3*/
#line 31 "./sat-dance.w"

/*6:*/
#line 99 "./sat-dance.w"

column col_array[max_cols+2];
node node_array[max_nodes];
char buf[buf_size];
node*row[max_nodes];
#line 4 "./sat-dance-prestwich.ch"
int rowptr;
int cases[7];
#line 105 "./sat-dance.w"

/*:6*/
#line 32 "./sat-dance.w"


main(argc,argv)
int argc;
char*argv[];
{
/*8:*/
#line 137 "./sat-dance.w"

#line 10 "./sat-dance-prestwich.ch"
register column*cur_col,*last_col;
#line 139 "./sat-dance.w"
register char*p,*q;
register node*cur_node;
int primary;
int j,k;

/*:8*/
#line 38 "./sat-dance.w"
;
/*5:*/
#line 93 "./sat-dance.w"

/*7:*/
#line 108 "./sat-dance.w"

cur_col= col_array+1;
fgets(buf,buf_size,stdin);
if(buf[strlen(buf)-1]!='\n')panic("Input line too long");
for(p= buf,primary= 1;*p;p++){
while(isspace(*p))p++;
if(!*p)break;
if(*p=='|'){
primary= 0;
if(cur_col==col_array+1)panic("No primary columns");
(cur_col-1)->next= &root,root.prev= cur_col-1;
continue;
}
for(q= p+1;!isspace(*q);q++);
if(q> p+7)panic("Column name too long");
if(cur_col>=&col_array[max_cols])panic("Too many columns");
for(q= cur_col->name;!isspace(*p);q++,p++)*q= *p;
cur_col->head.up= cur_col->head.down= &cur_col->head;
cur_col->head.num= -1;
cur_col->len= 0;
if(primary)cur_col->prev= cur_col-1,(cur_col-1)->next= cur_col;
else cur_col->prev= cur_col->next= cur_col;
cur_col++;
}
if(primary){
if(cur_col==col_array+1)panic("No primary columns");
(cur_col-1)->next= &root,root.prev= cur_col-1;
}

/*:7*/
#line 94 "./sat-dance.w"
;
/*9:*/
#line 144 "./sat-dance.w"

cur_node= node_array;
while(fgets(buf,buf_size,stdin)){
register column*ccol;
register node*row_start;
if(buf[strlen(buf)-1]!='\n')panic("Input line too long");
row_start= NULL;
for(p= buf;*p;p++){
while(isspace(*p))p++;
if(!*p)break;
for(q= p+1;!isspace(*q);q++);
if(q> p+7)panic("Column name too long");
for(q= cur_col->name;!isspace(*p);q++,p++)*q= *p;
*q= '\0';
for(ccol= col_array;strcmp(ccol->name,cur_col->name);ccol++);
if(ccol==cur_col)panic("Unknown column name");
if(cur_node==&node_array[max_nodes])panic("Too many nodes");
if(!row_start)row_start= cur_node;
else cur_node->left= cur_node-1,(cur_node-1)->right= cur_node;
cur_node->col= ccol;
cur_node->up= ccol->head.up,ccol->head.up->down= cur_node;
ccol->head.up= cur_node,cur_node->down= &ccol->head;
ccol->len++;
cur_node->num= rowptr;
cur_node++;
}
if(!row_start)panic("Empty row");
row[rowptr++]= row_start;
row_start->left= cur_node-1,(cur_node-1)->right= row_start;
}

/*:9*/
#line 95 "./sat-dance.w"
;

/*:5*/
#line 39 "./sat-dance.w"
;
/*10:*/
#line 15 "./sat-dance-prestwich.ch"

last_col= cur_col;
#line 182 "./sat-dance.w"
/*11:*/
#line 185 "./sat-dance.w"

for(cur_col= root.next;cur_col!=&root;cur_col= cur_col->next){
for(cur_node= cur_col->head.down;cur_node!=&cur_col->head;
cur_node= cur_node->down)
printf(" %d",cur_node->num+1);
printf("\n");
}

#line 33 "./sat-dance-prestwich.ch"
/*:11*/
#line 182 "./sat-dance.w"
;
/*12:*/
#line 33 "./sat-dance-prestwich.ch"

for(cur_col= root.next;cur_col<last_col;cur_col++){
for(k= 0,cur_node= cur_col->head.down;
cur_node!=&cur_col->head;cur_node= cur_node->down)k++;
if(k==1)continue;
j= 0,cur_node= cur_col->head.down;
if(k<7)/*13:*/
#line 43 "./sat-dance-prestwich.ch"

{
while(j<k)cases[j++]= cur_node->num+1,cur_node= cur_node->down;
while(k> 1){
k--;
for(j= 0;j<k;j++)printf("~%d ~%d\n",cases[j],cases[k]);
}
}

/*:13*/
#line 39 "./sat-dance-prestwich.ch"

else/*14:*/
#line 57 "./sat-dance-prestwich.ch"

{
register i,b,t;
for(;j<k;j++,cur_node= cur_node->down){
b= k+j;
for(t= 1;t<=b;t<<= 1);
for(i= '@',t>>= 2;t;t>>= 1,i++)
printf("~%d %s%ld%c\n",
cur_node->num+1,(b&t?"":"~"),cur_col-root.next,i);
}
}
#line 206 "./sat-dance.w"

/*:14*/
#line 40 "./sat-dance-prestwich.ch"
;
}

/*:12*/
#line 183 "./sat-dance.w"
;

/*:10*/
#line 40 "./sat-dance.w"
;
}

/*:1*/
