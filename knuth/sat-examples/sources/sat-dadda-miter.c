#define nmax 1000 \

#define make_and(a,ka,la,b,kb,lb,c,kc,lc) { \
if(ka) printf("~%c%d.%d ",a,ka,la) ; \
else printf("~%c%d ",a,la) ; \
if(kb) printf("%c%d.%d\n",b,kb,lb) ; \
else printf("%c%d\n",b,lb) ; \
if(ka) printf("~%c%d.%d ",a,ka,la) ; \
else printf("~%c%d ",a,la) ; \
if(kc) printf("%c%d.%d\n",c,kc,lc) ; \
else printf("%c%d\n",c,lc) ; \
if(ka) printf("%c%d.%d ",a,ka,la) ; \
else printf("%c%d ",a,la) ; \
if(kb) printf("~%c%d.%d ",b,kb,lb) ; \
else printf("~%c%d ",b,lb) ; \
if(kc) printf("~%c%d.%d\n",c,kc,lc) ; \
else printf("~%c%d\n",c,lc) ; \
} \

#define make_xor(a,ka,la,b,kb,lb,c,kc,lc) { \
if(ka) printf("%c%d.%d ",a,ka,la) ; \
else printf("%c%d ",a,la) ; \
if(kb) printf("~%c%d.%d ",b,kb,lb) ; \
else printf("~%c%d ",b,lb) ; \
if(kc) printf("%c%d.%d\n",c,kc,lc) ; \
else printf("%c%d\n",c,lc) ; \
if(ka) printf("%c%d.%d ",a,ka,la) ; \
else printf("%c%d ",a,la) ; \
if(kb) printf("%c%d.%d ",b,kb,lb) ; \
else printf("%c%d ",b,lb) ; \
if(kc) printf("~%c%d.%d\n",c,kc,lc) ; \
else printf("~%c%d\n",c,lc) ; \
if(ka) printf("~%c%d.%d ",a,ka,la) ; \
else printf("~%c%d ",a,la) ; \
if(kb) printf("%c%d.%d ",b,kb,lb) ; \
else printf("%c%d ",b,lb) ; \
if(kc) printf("%c%d.%d\n",c,kc,lc) ; \
else printf("%c%d\n",c,lc) ; \
if(ka) printf("~%c%d.%d ",a,ka,la) ; \
else printf("~%c%d ",a,la) ; \
if(kb) printf("~%c%d.%d ",b,kb,lb) ; \
else printf("~%c%d ",b,lb) ; \
if(kc) printf("~%c%d.%d\n",c,kc,lc) ; \
else printf("~%c%d\n",c,lc) ; \
} \

#define make_or(a,ka,la,b,kb,lb,c,kc,lc) { \
if(ka) printf("%c%d.%d ",a,ka,la) ; \
else printf("%c%d ",a,la) ; \
if(kb) printf("~%c%d.%d\n",b,kb,lb) ; \
else printf("~%c%d\n",b,lb) ; \
if(ka) printf("%c%d.%d ",a,ka,la) ; \
else printf("%c%d ",a,la) ; \
if(kc) printf("~%c%d.%d\n",c,kc,lc) ; \
else printf("~%c%d\n",c,lc) ; \
if(ka) printf("~%c%d.%d ",a,ka,la) ; \
else printf("~%c%d ",a,la) ; \
if(kb) printf("%c%d.%d ",b,kb,lb) ; \
else printf("%c%d ",b,lb) ; \
if(kc) printf("%c%d.%d\n",c,kc,lc) ; \
else printf("%c%d\n",c,lc) ; \
} \

/*1:*/
#line 27 "./sat-dadda.w"

#include <stdio.h> 
#include <stdlib.h> 
int bin[nmax+nmax][nmax];
int count[nmax+nmax];
int size[nmax+nmax];
int adders[nmax+nmax];
int m,n;
int addend[3];
main(int argc,char*argv[]){
register int i,j,k,l;
/*2:*/
#line 44 "./sat-dadda.w"

#line 22 "./sat-dadda-miter.ch"
if(argc!=3||sscanf(argv[1],"%d",&m)!=1||sscanf(argv[2],"%d",&n)!=1){
fprintf(stderr,"Usage: %s m n\n",argv[0]);
#line 47 "./sat-dadda.w"
exit(-1);
}
if(n> nmax){
fprintf(stderr,"Sorry, n must be at most %d!\n",nmax);
exit(-2);
}
if(m<2||m> n){
fprintf(stderr,"Sorry, m can't be %d (it should lie between 2 and %d)!\n",
m,n);
exit(-3);
}
#line 62 "./sat-dadda.w"

#line 50 "./sat-dadda-miter.ch"
/*:2*/
#line 38 "./sat-dadda.w"
;
#line 15 "./sat-dadda-miter.ch"
printf("~ sat-dadda-miter %d %d\n",m,n);
/*3:*/
#line 53 "./sat-dadda-miter.ch"

for(j= 0;j<m+n;j++){
printf("~@%d ~z%d\n",j+1,j+1);
printf("~@%d Z%d\n",j+1,j+1);
}
for(j= 0;j<m+n;j++)printf(" @%d",j+1);
printf("\n");
#line 79 "./sat-dadda.w"

/*:3*/
#line 16 "./sat-dadda-miter.ch"
;
#line 41 "./sat-dadda.w"
/*4:*/
#line 80 "./sat-dadda.w"

/*6:*/
#line 108 "./sat-dadda.w"

for(i= 1;i<=m;i++)for(j= 1;j<=n;j++){
k= i+j;
#line 68 "./sat-dadda-miter.ch"
if(k==2){
make_and('z',0,1,'X',0,i,'Y',0,j);
make_and('Z',0,1,'X',0,i,'Y',0,j);
}else{
l= count[k]= ++size[k];
bin[k][l-1]= l;
make_and('a',k,l,'X',0,i,'Y',0,j);
make_and('A',k,l,'X',0,i,'Y',0,j);
#line 116 "./sat-dadda.w"
}
}

/*:6*/
#line 81 "./sat-dadda.w"
;
for(k= 3;k<=m+n;k++)
/*5:*/
#line 85 "./sat-dadda.w"

{
while(size[k]> 2)/*8:*/
#line 174 "./sat-dadda.w"

{
for(i= 0;i<3;i++)/*9:*/
#line 196 "./sat-dadda.w"

{
addend[i]= bin[k][0];
for(l= 1;l<size[k];l++)bin[k][l-1]= bin[k][l];
size[k]= l-1;
}

/*:9*/
#line 176 "./sat-dadda.w"
;
i= ++adders[k];
#line 109 "./sat-dadda-miter.ch"
make_xor('s',k,i,'a',k,addend[0],'a',k,addend[1]);
make_xor('S',k,i,'A',k,addend[0],'A',k,addend[1]);
make_and('p',k,i,'a',k,addend[0],'a',k,addend[1]);
make_and('P',k,i,'A',k,addend[0],'A',k,addend[1]);
l= ++count[k],bin[k][size[k]++]= l;
if(size[k]==1){
make_xor('z',0,k-1,'s',k,i,'a',k,addend[2])
make_xor('Z',0,k-1,'S',k,i,'A',k,addend[2])
}else{
make_xor('a',k,l,'s',k,i,'a',k,addend[2]);
make_xor('A',k,l,'S',k,i,'A',k,addend[2]);
}
make_and('q',k,i,'s',k,i,'a',k,addend[2]);
make_and('Q',k,i,'S',k,i,'A',k,addend[2]);
if(k==m+n){
make_or('z',0,k,'p',k,i,'q',k,i);
make_or('Z',0,k,'P',k,i,'Q',k,i);
}else{
l= count[k+1]= ++size[k+1],bin[k+1][l-1]= l;
make_or('a',k+1,l,'p',k,i,'q',k,i);
make_or('A',k+1,l,'P',k,i,'Q',k,i);
#line 190 "./sat-dadda.w"
}
}

/*:8*/
#line 87 "./sat-dadda.w"
;
if(size[k]> 1)/*7:*/
#line 146 "./sat-dadda.w"

{
#line 85 "./sat-dadda-miter.ch"
make_xor('z',0,k-1,'a',k,bin[k][0],'a',k,bin[k][1]);
make_xor('Z',0,k-1,'A',k,bin[k][0],'A',k,bin[k][1]);
if(k==m+n){
make_and('z',0,k,'a',k,bin[k][0],'a',k,bin[k][1]);
make_and('Z',0,k,'A',k,bin[k][0],'A',k,bin[k][1]);
}else{
l= count[k+1]= ++size[k+1],bin[k+1][l-1]= l;
make_and('a',k+1,l,'a',k,bin[k][0],'a',k,bin[k][1]);
make_and('A',k+1,l,'A',k,bin[k][0],'A',k,bin[k][1]);
#line 154 "./sat-dadda.w"
}
}

/*:7*/
#line 88 "./sat-dadda.w"
;
}

/*:5*/
#line 83 "./sat-dadda.w"
;

/*:4*/
#line 41 "./sat-dadda.w"
;
}

/*:1*/
