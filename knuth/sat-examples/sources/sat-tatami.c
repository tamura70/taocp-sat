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
main(){
register int i,j,k,x,y;
/*2:*/
#line 32 "./sat-tatami.w"

for(x= 1;;x++){
if(!fgets(buf,maxy+2,stdin))break;
if(x> maxx){
fprintf(stderr,"Sorry, the pattern should have at most %d rows!\n",maxx);
exit(-3);
}
for(y= 1;buf[y-1]!='\n';y++){
if(y> maxy){
fprintf(stderr,"Sorry, the pattern should have at most %d columns!\n",
maxy);
exit(-4);
}
if(buf[y-1]=='*'){
p[x][y]= 1;
if(y> ymax)ymax= y;
if(y<ymin)ymin= y;
if(x> xmax)xmax= x;
if(x<xmin)xmin= x;
}else if(buf[y-1]!='.'){
fprintf(stderr,"Unexpected character `%c' found in the pattern!\n",
buf[y-1]);
exit(-5);
}
}
}

/*:2*/
#line 25 "./sat-tatami.w"
;
printf("~ sat-tatami (%dx%d)\n",
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
#line 28 "./sat-tatami.w"
;
/*4:*/
#line 88 "./sat-tatami.w"

for(x= xmin;x<xmax;x++)for(y= ymin;y<ymax;y++){
k= p[x][y]+p[x][y+1]+p[x+1][y]+p[x+1][y+1];
if(k>=3){
if(p[x][y]&&p[x][y+1])printf(" %dH%d",
x,y);
if(p[x][y]&&p[x+1][y])printf(" %dV%d",
x,y);
if(p[x+1][y]&&p[x+1][y+1])printf(" %dH%d",
x+1,y);
if(p[x][y+1]&&p[x+1][y+1])printf(" %dV%d",
x,y+1);
printf("\n");
}
}

/*:4*/
#line 29 "./sat-tatami.w"
;
}

/*:1*/
