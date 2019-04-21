#define maxx 50
#define maxy 200 \

/*1:*/
#line 15 "./sat-tatami.w"

#include <stdio.h> 
#include <stdlib.h> 
char p[maxx+2][maxy+2];
int xmax,ymax;
int xmin= maxx,ymin= maxy;
char buf[maxy+2];
char a[4][8];
#line 20 "./sat-tatami-mutilated.ch"
main(int argc,char*argv[]){
register int i,j,k,x,y;
/*5:*/
#line 31 "./sat-tatami-mutilated.ch"

if(argc!=3||sscanf(argv[1],"%d",&xmax)!=1
||sscanf(argv[2],"%d",&ymax)!=1){
fprintf(stderr,"Usage: %s m n\n",argv[0]);
exit(-1);
}
if(xmax> maxx){
fprintf(stderr,"Sorry, the pattern should have at most %d rows!\n",maxx);
exit(-3);
}
if(ymax> maxy){
fprintf(stderr,"Sorry, the pattern should have at most %d columns!\n",
maxy);
exit(-4);
}
xmin= ymin= 1;
for(x= 1;x<=xmax;x++)for(y= 1;y<=ymax;y++)
if((x!=1||y!=ymax)&&(x!=xmax||y!=1))p[x][y]= 1;

/*:5*/
#line 22 "./sat-tatami-mutilated.ch"
;
printf("~ sat-tatami-mutilated %d %d\n",
xmax,ymax);
/*3:*/
#line 62 "./sat-tatami.w"

for(x= xmin;x<=xmax;x++)for(y= ymin;y<=ymax;y++)if(p[x][y]){
k= 0;
if(p[x][y+1])sprintf(a[k],"%dH%d",
x,y),k++;
if(p[x][y-1])sprintf(a[k],"%dH%d",
x,y-1),k++;
if(p[x+1][y])sprintf(a[k],"%dV%d",
x,y),k++;
if(p[x-1][y])sprintf(a[k],"%dV%d",
x-1,y),k++;
if(k==0){
fprintf(stderr,"Cell (%d,",
x);
fprintf(stderr,"%d) cannot be covered with a domino!\n",
y);
exit(-1);
}
for(i= 0;i<k;i++)for(j= i+1;j<k;j++)
printf("~%s ~%s\n",
a[i],a[j]);
for(i= 0;i<k;i++)printf(" %s",
a[i]);
printf("\n");
}

/*:3*/
#line 25 "./sat-tatami-mutilated.ch"
;
}
#line 31 "./sat-tatami.w"

/*:1*/
