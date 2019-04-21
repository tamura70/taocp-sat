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

if(argc!=4||sscanf(argv[1],"%d",&m)!=1||sscanf(argv[2],"%d",&n)!=1){
fprintf(stderr,"Usage: %s m n z\n",argv[0]);
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
if(argv[3][0]<'0'||argv[3][0]> '9'){
fprintf(stderr,"z must begin with a decimal digit, not '%c'!\n",argv[3][0]);
exit(-4);
}

/*:2*/
#line 38 "./sat-dadda.w"
;
printf("~ sat-dadda %d %d %s\n",m,n,argv[3]);
/*3:*/
#line 63 "./sat-dadda.w"

for(j= 0;j<m+n;j++){
for(i= k= 0;argv[3][i]>='0'&&argv[3][i]<='9';i++){
l= argv[3][i]-'0'+k;
k= (l&1?10:0);
argv[3][i]= '0'+(l>>1);
}
if(k)printf("Z%d\n",j+1);
else printf("~Z%d\n",j+1);
}
if(argv[3][i]){
fprintf(stderr,"Warning: Junk found after the value of z: %s\n",argv[3]+i);
argv[3][i]= 0;
}
for(i= 0;argv[3][i];i++)if(argv[3][i]!='0')
fprintf(stderr,"Warning: z was truncated to %d bits\n",m+n);

/*:3*/
#line 40 "./sat-dadda.w"
;
/*4:*/
#line 80 "./sat-dadda.w"

/*6:*/
#line 108 "./sat-dadda.w"

for(i= 1;i<=m;i++)for(j= 1;j<=n;j++){
k= i+j;
if(k==2)make_and('Z',0,1,'X',0,i,'Y',0,j)
else{
l= count[k]= ++size[k];
bin[k][l-1]= l;
make_and('A',k,l,'X',0,i,'Y',0,j);
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
make_xor('S',k,i,'A',k,addend[0],'A',k,addend[1]);
make_and('P',k,i,'A',k,addend[0],'A',k,addend[1]);
l= ++count[k],bin[k][size[k]++]= l;
if(size[k]==1)
make_xor('Z',0,k-1,'S',k,i,'A',k,addend[2])
else make_xor('A',k,l,'S',k,i,'A',k,addend[2]);
make_and('Q',k,i,'S',k,i,'A',k,addend[2]);
if(k==m+n)
make_or('Z',0,k,'P',k,i,'Q',k,i)
else{
l= count[k+1]= ++size[k+1],bin[k+1][l-1]= l;
make_or('A',k+1,l,'P',k,i,'Q',k,i);
}
}

/*:8*/
#line 87 "./sat-dadda.w"
;
if(size[k]> 1)/*7:*/
#line 146 "./sat-dadda.w"

{
make_xor('Z',0,k-1,'A',k,bin[k][0],'A',k,bin[k][1]);
if(k==m+n)
make_and('Z',0,k,'A',k,bin[k][0],'A',k,bin[k][1])
else{
l= count[k+1]= ++size[k+1],bin[k+1][l-1]= l;
make_and('A',k+1,l,'A',k,bin[k][0],'A',k,bin[k][1]);
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
