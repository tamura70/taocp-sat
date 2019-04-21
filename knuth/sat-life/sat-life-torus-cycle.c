#define maxx 50
#define maxy 50 \

#define pp(xx,yy) ((xx) >=0&&(yy) >=0?p[xx][yy]:0)  \

#define taut (2<<25) 
#define sign (1U<<31)  \

#define newlit(x,y,c,k) clause[clauseptr++]= ((c) <<28) +((k) <<25) +((x) <<12) +(y) 
#define newcomplit(x,y,c,k)  \
clause[clauseptr++]= sign+((c) <<28) +((k) <<25) +((x) <<12) +(y)  \

/*2:*/
#line 94 "./sat-life.w"

#include <stdio.h> 
#include <stdlib.h> 
char p[maxx+2][maxy+2];
char have_b[maxx+2][maxy+2];
char have_d[maxx+2][maxy+2];
char have_e[maxx+2][maxy+4];
char have_f[maxx+4][maxy+2];
#line 19 "./sat-life-torus-cycle.ch"
int tt;
int mm,nn,r;
#line 103 "./sat-life.w"
int xmax,ymax;
int xmin= maxx,ymin= maxy;
char timecode[]= "abcdefghijklmnopqrstuvwxyz"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

char buf[maxy+2];
unsigned int clause[4];
int clauseptr;
/*6:*/
#line 191 "./sat-life.w"

void outclause(void){
register int c,k,x,y,p;
for(p= 0;p<clauseptr;p++)
if(clause[p]==taut)goto done;
for(p= 0;p<clauseptr;p++)if(clause[p]!=taut+sign){
if(clause[p]>>31)printf(" ~");else printf(" ");
c= (clause[p]>>28)&0x7;
k= (clause[p]>>25)&0x7;
x= (clause[p]>>12)&0xfff;
y= clause[p]&0xfff;
#line 68 "./sat-life-torus-cycle.ch"
if(c)printf("%d%c%d%c%d",
1+((x+mm-1)%mm),timecode[tt],1+((y+nn-1)%nn),c+'@',k);
else if(k==7)printf("%d%c%dx",
1+((x+mm-1)%mm),timecode[tt],1+((y+nn-1)%nn));
else printf("%d%c%d",
1+((x+mm-1)%mm),timecode[(tt+k)%r],1+((y+nn-1)%nn));
#line 208 "./sat-life.w"
}
printf("\n");
done:clauseptr= 0;
}

/*:6*//*7:*/
#line 215 "./sat-life.w"

void applit(int x,int y,int bar,int k){
#line 80 "./sat-life-torus-cycle.ch"
clause[clauseptr++]= (bar?sign:0)+(k<<25)+(x<<12)+y;
#line 220 "./sat-life.w"
}

/*:7*//*8:*/
#line 235 "./sat-life.w"

void d(int x,int y){
register x1= x-1,x2= x,yy= y+1;
#line 85 "./sat-life-torus-cycle.ch"
if(have_d[x%mm][y%nn]!=tt+1){
#line 239 "./sat-life.w"
applit(x1,yy,1,0),newlit(x,y,4,1),outclause();
applit(x2,yy,1,0),newlit(x,y,4,1),outclause();
applit(x1,yy,1,0),applit(x2,yy,1,0),newlit(x,y,4,2),outclause();
applit(x1,yy,0,0),applit(x2,yy,0,0),newcomplit(x,y,4,1),outclause();
applit(x1,yy,0,0),newcomplit(x,y,4,2),outclause();
#line 245 "./sat-life.w"
applit(x2,yy,0,0),newcomplit(x,y,4,2),outclause();
#line 94 "./sat-life-torus-cycle.ch"
have_d[x%mm][y%nn]= tt+1;
#line 247 "./sat-life.w"
}
}

void e(int x,int y){
register x1= x-1,x2= x,yy= y-1;
#line 99 "./sat-life-torus-cycle.ch"
if(have_e[x%mm][y%nn]!=tt+1){
#line 253 "./sat-life.w"
applit(x1,yy,1,0),newlit(x,y,5,1),outclause();
applit(x2,yy,1,0),newlit(x,y,5,1),outclause();
applit(x1,yy,1,0),applit(x2,yy,1,0),newlit(x,y,5,2),outclause();
applit(x1,yy,0,0),applit(x2,yy,0,0),newcomplit(x,y,5,1),outclause();
applit(x1,yy,0,0),newcomplit(x,y,5,2),outclause();
#line 259 "./sat-life.w"
applit(x2,yy,0,0),newcomplit(x,y,5,2),outclause();
#line 108 "./sat-life-torus-cycle.ch"
have_e[x%mm][y%nn]= tt+1;
#line 261 "./sat-life.w"
}
}

/*:8*//*9:*/
#line 267 "./sat-life.w"

void f(int x,int y){
register xx= x-1,y1= y,y2= y+1;
#line 113 "./sat-life-torus-cycle.ch"
if(have_f[x%mm][y%nn]!=tt+1){
#line 271 "./sat-life.w"
applit(xx,y1,1,0),newlit(x,y,6,1),outclause();
applit(xx,y2,1,0),newlit(x,y,6,1),outclause();
applit(xx,y1,1,0),applit(xx,y2,1,0),newlit(x,y,6,2),outclause();
applit(xx,y1,0,0),applit(xx,y2,0,0),newcomplit(x,y,6,1),outclause();
applit(xx,y1,0,0),newcomplit(x,y,6,2),outclause();
#line 277 "./sat-life.w"
applit(xx,y2,0,0),newcomplit(x,y,6,2),outclause();
#line 122 "./sat-life-torus-cycle.ch"
have_f[x%mm][y%nn]= tt+1;
#line 279 "./sat-life.w"
}
}

/*:9*//*10:*/
#line 286 "./sat-life.w"

void g(int x,int y){
register x1,x2,y1,y2;
if(x&1)x1= x-1,y1= y,x2= x+1,y2= y^1;
else x1= x+1,y1= y,x2= x-1,y2= y-1+((y&1)<<1);
applit(x1,y1,1,0),newlit(x,y,7,1),outclause();
applit(x2,y2,1,0),newlit(x,y,7,1),outclause();
applit(x1,y1,1,0),applit(x2,y2,1,0),newlit(x,y,7,2),outclause();
applit(x1,y1,0,0),applit(x2,y2,0,0),newcomplit(x,y,7,1),outclause();
applit(x1,y1,0,0),newcomplit(x,y,7,2),outclause();
applit(x2,y2,0,0),newcomplit(x,y,7,2),outclause();
}

/*:10*//*11:*/
#line 302 "./sat-life.w"

void b(int x,int y){
register j,k,xx= x,y1= y-(y&2),y2= y+(y&2);
#line 127 "./sat-life-torus-cycle.ch"
if(have_b[x%mm][y%nn]!=tt+1){
#line 306 "./sat-life.w"
d(xx,y1);
e(xx,y2);
for(j= 0;j<3;j++)for(k= 0;k<3;k++)if(j+k){
if(j)newcomplit(xx,y1,4,j);
if(k)newcomplit(xx,y2,5,k);
newlit(x,y,2,j+k);
outclause();
if(j)newlit(xx,y1,4,3-j);
if(k)newlit(xx,y2,5,3-k);
newcomplit(x,y,2,5-j-k);
outclause();
}
#line 132 "./sat-life-torus-cycle.ch"
have_b[x%mm][y%nn]= tt+1;
#line 319 "./sat-life.w"
}
}

/*:11*//*12:*/
#line 329 "./sat-life.w"

void c(int x,int y){
register j,k,x1,y1;
if(x&1)x1= x+2,y1= (y-1)|1;
else x1= x,y1= y&-2;
g(x,y);
#line 137 "./sat-life-torus-cycle.ch"
if(0)
#line 336 "./sat-life.w"
/*13:*/
#line 352 "./sat-life.w"

{
for(k= 1;k<3;k++){
newcomplit(x,y,7,k),newlit(x,y,3,k),outclause();
newlit(x,y,7,k),newcomplit(x,y,3,k),outclause();
}
newcomplit(x,y,3,3),outclause();
newcomplit(x,y,3,4),outclause();
}

/*:13*/
#line 336 "./sat-life.w"

else{
f(x1,y1);
for(j= 0;j<3;j++)for(k= 0;k<3;k++)if(j+k){
if(j)newcomplit(x1,y1,6,j);
if(k)newcomplit(x,y,7,k);
newlit(x,y,3,j+k);
outclause();
if(j)newlit(x1,y1,6,3-j);
if(k)newlit(x,y,7,3-k);
newcomplit(x,y,3,5-j-k);
outclause();
}
}
}

/*:12*//*14:*/
#line 365 "./sat-life.w"

void a(int x,int y){
register j,k,xx= x|1;
b(xx,y);
c(x,y);
for(j= 0;j<5;j++)for(k= 0;k<5;k++)if(j+k> 1&&j+k<5){
if(j)newcomplit(xx,y,2,j);
if(k)newcomplit(x,y,3,k);
newlit(x,y,1,j+k);
outclause();
}
for(j= 0;j<5;j++)for(k= 0;k<5;k++)if(j+k> 2&&j+k<6&&j*k){
if(j)newlit(xx,y,2,j);
if(k)newlit(x,y,3,k);
newcomplit(x,y,1,j+k-1);
outclause();
}
}

/*:14*//*15:*/
#line 390 "./sat-life.w"

void zprime(int x,int y){
newcomplit(x,y,1,4),applit(x,y,1,1),outclause();
newlit(x,y,1,2),applit(x,y,1,1),outclause();
newlit(x,y,1,3),applit(x,y,0,0),applit(x,y,1,1),outclause();

newcomplit(x,y,1,3),newlit(x,y,1,4),applit(x,y,0,1),outclause();

applit(x,y,0,7),newcomplit(x,y,1,2),newlit(x,y,1,4),outclause();

applit(x,y,1,7),applit(x,y,1,0),applit(x,y,0,1),outclause();

}

#line 142 "./sat-life-torus-cycle.ch"
/*:15*/
#line 112 "./sat-life.w"

main(int argc,char*argv[]){
register int j,k,x,y;
/*3:*/
#line 124 "./sat-life.w"

#line 52 "./sat-life-torus-cycle.ch"
if(argc!=4||sscanf(argv[1],"%d",&mm)!=1||
sscanf(argv[2],"%d",&nn)!=1||
sscanf(argv[3],"%d",&r)!=1){
fprintf(stderr,"Usage: %s m n r\n",argv[0]);
exit(-1);
}
printf("~ sat-life-torus-cycle %d %d %d\n",mm,nn,r);
#line 133 "./sat-life.w"

/*:3*/
#line 115 "./sat-life.w"
;
#line 30 "./sat-life-torus-cycle.ch"
/*16:*/
#line 142 "./sat-life-torus-cycle.ch"

for(y= 1;y<2;y++)printf(" 1a%d",y);
printf("\n");

/*:16*/
#line 30 "./sat-life-torus-cycle.ch"
;
for(tt= 0;tt<r;tt++){
ymax= nn,ymin= 1;
xmax= mm,xmin= 1;
for(x= xmin;x<=xmax;x++)for(y= ymin;y<=ymax;y++){
a(x,y);
zprime(x,y);
}
}
/*17:*/
#line 146 "./sat-life-torus-cycle.ch"

for(k= 1;k<r;k++)if(r%k==0){
for(x= 1;x<=mm;x++)for(y= 1;y<=nn;y++){
printf("%da%d %d%c%d ~%da%c%d\n",x,y,x,timecode[k],y,x,timecode[k],y);
printf("~%da%d ~%d%c%d ~%da%c%d\n",x,y,x,timecode[k],y,x,timecode[k],y);
}
for(x= 1;x<=mm;x++)for(y= 1;y<=nn;y++)
printf(" %da%c%d",x,timecode[k],y);
printf("\n");
}

/*:17*/
#line 39 "./sat-life-torus-cycle.ch"
;
/*18:*/
#line 157 "./sat-life-torus-cycle.ch"

for(k= 1;k<mm;k++)if(mm%k==0){
register int q;
for(q= 1;q<=mm-k;q++)for(y= 1;y<=nn;y++){
printf("%da%d %da%d ~%d,%d:%d\n",q,y,q+k,y,q,q+k,y);
printf("~%da%d ~%da%d ~%d,%d:%d\n",q,y,q+k,y,q,q+k,y);
}
for(q= 1;q<=mm-k;q++)for(y= 1;y<=nn;y++)printf(" %d,%d:%d",q,q+k,y);
printf("\n");
}
for(k= 1;k<nn;k++)if(nn%k==0){
register int q;
for(q= 1;q<=nn-k;q++)for(x= 1;x<=mm;x++){
printf("%da%d %da%d ~%d:%d,%d\n",x,q,x,q+k,x,q,q+k);
printf("~%da%d ~%da%d ~%d:%d,%d\n",x,q,x,q+k,x,q,q+k);
}
for(q= 1;q<=nn-k;q++)for(x= 1;x<=mm;x++)printf(" %d:%d,%d",x,q,q+k);
printf("\n");
}

/*:18*/
#line 40 "./sat-life-torus-cycle.ch"
;
#line 122 "./sat-life.w"
}

/*:2*/
