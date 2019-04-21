#define maxn 10000
#define bufsize 10020 \

#define xbar(k) if(buf[(k) -n+1]=='0')  \
printf("~x%d", \
(k) -n+2) ; \
else printf("x%d", \
(k) -n+2)  \

/*1:*/
#line 12 "./sat-closest-string.w"

#include <stdio.h> 
#include <stdlib.h> 
int r;
char buf[bufsize];
int count[maxn+maxn];
main(){
register int i,j,jl,jr,k,m,n,t,tl,tr;
n= -1;
printf("~ sat-closest-string\n");
for(j= 1;;j++){
getbuf:if(fgets(buf,bufsize,stdin)==NULL)break;
if(buf[0]=='!')goto getbuf;
/*2:*/
#line 29 "./sat-closest-string.w"

/*3:*/
#line 33 "./sat-closest-string.w"

for(i= 0;i<bufsize;i++)
if(buf[i]!='0'&&buf[i]!='1')break;
if(i==bufsize){
fprintf(stderr,"Input string %s didn't fit in the buffer!\n",
buf);
exit(-1);
}
if(i==0){
fprintf(stderr,"Null input string!\n");
exit(-2);
}
if(buf[i]!=' '){
buf[i]= '\0';
fprintf(stderr,"Input string %s not followed by blank space!\n",
buf);
exit(-3);
}
buf[i]= '\0';
if(n<0){
n= i;
/*4:*/
#line 80 "./sat-closest-string.w"

for(k= n+n-2;k>=n-1;k--)count[k]= 1;
for(;k>=0;k--)
count[k]= count[k+k+1]+count[k+k+2];
if(count[0]!=n){
fprintf(stderr,"I'm totally confused.\n");
exit(-666);
}

/*:4*/
#line 54 "./sat-closest-string.w"
;
}else if(n!=i){
fprintf(stderr,"Input string %s has length %d, not %d!\n",
buf,i,n);
exit(-4);
}
if(sscanf(buf+i+1,"%d",
&r)!=1){
fprintf(stderr,"Input string %s not followed by a distance threshold!\n",
buf);
exit(-5);
}
if(r<=0||r>=n){
fprintf(stderr,"The distance threshold for %s should be between 1 and %d!\n",
buf,n-1);
exit(-6);
}
printf("~ s%d=%s, r%d=%d\n",
j,buf,j,r);

/*:3*/
#line 30 "./sat-closest-string.w"
;
/*5:*/
#line 89 "./sat-closest-string.w"

for(i= n-2;i;i--)
/*6:*/
#line 105 "./sat-closest-string.w"

{
t= count[i],tl= count[i+i+1],tr= count[i+i+2];
if(t> r+1)t= r+1;
if(tl> r)tl= r;
if(tr> r)tr= r;
for(jl= 0;jl<=tl;jl++)for(jr= 0;jr<=tr;jr++)
if((jl+jr<=t)&&(jl+jr)> 0){
if(jl){
if(i+i+1>=n-1)xbar(i+i+1);
else printf("~%dB%d.%d",
j,i+i+2,jl);
}
if(jr){
printf(" ");
if(i+i+2>=n-1)xbar(i+i+2);
else printf("~%dB%d.%d",
j,i+i+3,jr);
}
if(jl+jr<=r)printf(" %dB%d.%d\n",
j,i+1,jl+jr);
else printf("\n");
}
}

/*:6*/
#line 91 "./sat-closest-string.w"
;
/*7:*/
#line 133 "./sat-closest-string.w"

tl= count[1],tr= count[2];
if(tl> r)tl= r;
for(jl= 1;jl<=tl;jl++){
jr= r+1-jl;
if(jr<=tr){
if(1>=n-1)xbar(1);
else printf("~%dB2.%d",
j,jl);
printf(" ");
if(2>=n-1)xbar(2);
else printf("~%dB3.%d",
j,jr);
printf("\n");
}
}

/*:7*/
#line 92 "./sat-closest-string.w"
;

/*:5*/
#line 31 "./sat-closest-string.w"
;

/*:2*/
#line 25 "./sat-closest-string.w"
;
}
}

/*:1*/
