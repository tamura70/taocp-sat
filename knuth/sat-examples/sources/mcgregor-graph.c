#define vert(j,k) (g->vertices+(n*(j) +(k) ) ) 
#define edge(j,k,jj,kk) gb_new_edge(vert(j,k) ,vert(jj,kk) ,1)  \

/*1:*/
#line 27 "./mcgregor-graph.w"

#include "gb_graph.h" 
#include "gb_save.h" 
int n;
char buf[16];
int main(int argc,char*argv[]){
register int i,j,k;
register Graph*g;
/*2:*/
#line 44 "./mcgregor-graph.w"

if(argc!=2||sscanf(argv[1],"%d",&n)!=1){
fprintf(stderr,"Usage: %s n\n",argv[0]);
exit(-1);
}

/*:2*/
#line 35 "./mcgregor-graph.w"
;
/*3:*/
#line 53 "./mcgregor-graph.w"

g= gb_new_graph(n*(n+1));
if(!g){
fprintf(stderr,"Can't create an empty graph of %d vertices!\n",n*(n+1));
exit(-2);
}
for(j= 0;j<=n;j++)for(k= 0;k<n;k++){
sprintf(buf,"%d.%d",j,k);
vert(j,k)->name= gb_save_string(buf);
}

/*:3*/
#line 36 "./mcgregor-graph.w"
;
for(j= 0;j<=n;j++)for(k= 0;k<n;k++)
/*4:*/
#line 72 "./mcgregor-graph.w"

{
if(j==0&&k==0){
edge(j,k,1,0);
for(i= 1;i<=n>>1;i++)edge(j,k,n,i);
}
if(j==1&&k==0){
for(i= n>>1;i<n;i++)edge(j,k,n,i);
continue;
}
if(j<n&&k<n-1)edge(j,k,j+1,k+1);
if(j==0)edge(j,k,n,n-1);
if(j!=k&&j<n)edge(j,k,j+1,k);
if(j!=k+1&&k<n-1)edge(j,k,j,k+1);
if(j==k&&k<n-1)edge(j,k,n-j,0);
if(j==k&&j> 0)edge(j,k,n+1-j,0);
if(k==n-1&&j> 0&&j<k)edge(j,k,n-j,n-j-1);
if(k==n-1&&j> 0&&j<n)edge(j,k,n+1-j,n-j);
}

/*:4*/
#line 38 "./mcgregor-graph.w"
;
sprintf(g->id,"mcgregor(%d)",n);
sprintf(buf,"mcgregor%d.gb",n);
save_graph(g,buf);
}

/*:1*/
