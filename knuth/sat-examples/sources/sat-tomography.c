#define mmax 200
#define nmax 100 \

#define x(k) printf("%s%s",swap?"~":"",name[(k) -n+2]) 
#define xbar(k) printf("%s%s",swap?"":"~",name[(k) -n+2])  \

/*1:*/
#line 17 "./sat-tomography.w"

#include <stdio.h> 
#include <stdlib.h> 
int r[mmax+1],c[mmax+1],a[mmax+nmax],b[mmax+nmax];
int count[mmax+mmax+nmax+nmax];
char buf[80];
char name[mmax+nmax][9];
/*10:*/
#line 191 "./sat-tomography.w"

void gen_clauses(int n,int r){
register int i,j,k,jl,jr,t,tl,tr,swap= 0;
if(r> n-r)swap= 1,r= n-r;
if(r<0){
fprintf(stderr,"Negative parameter for case %s!\n",buf);
exit(-99);
}
if(r==0)/*16:*/
#line 316 "./sat-tomography.w"

{
for(i= 1;i<=n;i++){
xbar(n-2+i);
printf("\n");
}
}

/*:16*/
#line 199 "./sat-tomography.w"

else{
/*11:*/
#line 215 "./sat-tomography.w"

for(k= n+n-2;k>=n-1;k--)count[k]= 1;
for(;k>=0;k--)
count[k]= count[k+k+1]+count[k+k+2];
if(count[0]!=n){
fprintf(stderr,"I'm totally confused.\n");
exit(-666);
}

/*:11*/
#line 201 "./sat-tomography.w"
;
for(i= n-2;i;i--){
/*12:*/
#line 234 "./sat-tomography.w"

{
t= count[i],tl= count[i+i+1],tr= count[i+i+2];
if(t> r+1)t= r+1;
if(tl> r)tl= r;
if(tr> r)tr= r;
for(jl= 0;jl<=tl;jl++)for(jr= 0;jr<=tr;jr++)
if((jl+jr<=t)&&(jl+jr)> 0){
if(jl){
if(i+i+1>=n-1)xbar(i+i+1);
else printf("~%s%02x%02x",buf,i+i+2,jl);
}
if(jr){
printf(" ");
if(i+i+2>=n-1)xbar(i+i+2);
else printf("~%s%02x%02x",buf,i+i+3,jr);
}
if(jl+jr<=r)printf(" %s%02x%02x\n",buf,i+1,jl+jr);
else printf("\n");
}
}

/*:12*/
#line 203 "./sat-tomography.w"
;
/*13:*/
#line 262 "./sat-tomography.w"

if(t> r)t= r;
for(jl= 1;jl<=tl+1;jl++)for(jr= 1;jr<=tr+1;jr++)if(jl+jr<=t+1){
if(jl<=tl){
if(i+i+1>=n-1)x(i+i+1);
else printf("%s%02x%02x",buf,i+i+2,jl);
printf(" ");
}
if(jr<=tr){
if(i+i+2>=n-1)x(i+i+2);
else printf("%s%02x%02x",buf,i+i+3,jr);
printf(" ");
}
printf("~%s%02x%02x\n",buf,i+1,jl+jr-1);
}

/*:13*/
#line 204 "./sat-tomography.w"
;
}
/*14:*/
#line 282 "./sat-tomography.w"

tl= count[1],tr= count[2];
for(jl= 1;jl<=tl;jl++){
jr= r+1-jl;
if(jr> 0&&jr<=tr){
if(1>=n-1)xbar(1);
else printf("~%s02%02x",buf,jl);
printf(" ");
if(2>=n-1)xbar(2);
else printf("~%s03%02x",buf,jr);
printf("\n");
}
}

/*:14*/
#line 206 "./sat-tomography.w"
;
/*15:*/
#line 299 "./sat-tomography.w"

for(jl= 1;jl<=r;jl++){
jr= r+1-jl;
if(jr> 0){
if(jl<=tl){
if(1>=n-1)x(1);
else printf("%s02%02x",buf,jl);
printf(" ");
}
if(jr<=tr){
if(2>=n-1)x(2);
else printf("%s03%02x",buf,jr);
}
printf("\n");
}
}

/*:15*/
#line 207 "./sat-tomography.w"
;
}
}

/*:10*/
#line 24 "./sat-tomography.w"
;
main(){
register int d,i,j,k,l,m,n,nn,t;
register char*p;
/*2:*/
#line 33 "./sat-tomography.w"

m= n= 0;
while(1){
if(!fgets(buf,80,stdin))break;
for(d= 0,p= buf+1;*p>='0'&&*p<='9';p++)d= 10*d+*p-'0';
if(*p++!='='){
fprintf(stderr,"Missing `=' sign!\nBad line: %s",
buf);
exit(-1);
}
for(l= 0;*p>='0'&&*p<='9';p++)l= 10*l+*p-'0';
if(*p!='\n'){
fprintf(stderr,"Missing \\n character!\nBad line %s",
buf);
exit(-2);
}
switch(buf[0]){
/*3:*/
#line 57 "./sat-tomography.w"

case'r':if(d<1||d> mmax){
fprintf(stderr,"Row index out of range!\nBad line %s",
buf);
exit(-4);
}
if(l<0||l> nmax){
fprintf(stderr,"Row data out of range!\nBad line %s",
buf);
exit(-5);
}
if(d> m)m= d;
if(r[d]){
fprintf(stderr,"The value of r%d has already been given!\nBad line %s",
d,buf);
exit(-6);
}
r[d]= l;
break;

/*:3*//*4:*/
#line 77 "./sat-tomography.w"

case'c':if(d<1||d> nmax){
fprintf(stderr,"Column index out of range!\nBad line %s",
buf);
exit(-14);
}
if(l<0||l> mmax){
fprintf(stderr,"Column data out of range!\nBad line %s",
buf);
exit(-15);
}
if(d> n)n= d;
if(c[d]){
fprintf(stderr,"The value of c%d has already been given!\nBad line %s",
d,buf);
exit(-16);
}
c[d]= l;
break;

/*:4*//*5:*/
#line 97 "./sat-tomography.w"

case'a':if(d<1||d>=mmax+nmax){
fprintf(stderr,"Diagonal index out of range!\nBad line %s",
buf);
exit(-24);
}
if(l<0||l> mmax||l> nmax){
fprintf(stderr,"Diagonal data out of range!\nBad line %s",
buf);
exit(-25);
}
if(a[d]){
fprintf(stderr,"The value of a%d has already been given!\nBad line %s",
d,buf);
exit(-26);
}
a[d]= l;
break;

/*:5*//*6:*/
#line 116 "./sat-tomography.w"

case'b':if(d<1||d>=mmax+nmax){
fprintf(stderr,"Diagonal index out of range!\nBad line %s",
buf);
exit(-34);
}
if(l<0||l> mmax||l> nmax){
fprintf(stderr,"Diagonal data out of range!\nBad line %s",
buf);
exit(-35);
}
if(b[d]){
fprintf(stderr,"The value of b%d has already been given!\nBad line %s",
d,buf);
exit(-36);
}
b[d]= l;
break;


/*:6*/
#line 50 "./sat-tomography.w"

default:fprintf(stderr,"Data must begin with r, c, a, or b!\nBad line %s",
buf);
exit(-3);
}
}

/*:2*/
#line 28 "./sat-tomography.w"
;
/*7:*/
#line 136 "./sat-tomography.w"

for(i= 1,l= 0;i<=m;i++)l+= r[i];
nn= l;
for(j= 1,l= 0;j<=n;j++)l+= c[j];
if(l!=nn){
fprintf(stderr,
"The total of the r's is %d, but the total of the c's is %d!\n",
nn,l);
exit(-40);
}
for(d= 1,l= 0;d<m+n;d++)l+= a[d];
if(l!=nn){
fprintf(stderr,
"The total of the r's is %d, but the total of the a's is %d!\n",
nn,l);
exit(-41);
}
for(d= 1,l= 0;d<m+n;d++)l+= b[d];
if(l!=nn){
fprintf(stderr,
"The total of the r's is %d, but the total of the b's is %d!\n",
nn,l);
exit(-41);
}
fprintf(stderr,"Input for %d rows and %d columns successfully read",
m,n);
fprintf(stderr," (total %d)\n",
nn);
printf("~ sat-tomography (%dx%d, %d)\n",
m,n,nn);

/*:7*/
#line 29 "./sat-tomography.w"
;
/*8:*/
#line 173 "./sat-tomography.w"

for(i= 1;i<=m;i++)/*9:*/
#line 184 "./sat-tomography.w"

{
sprintf(buf,"%dR",i);
for(j= 1;j<=n;j++)sprintf(name[j],"%dx%d",i,j);
gen_clauses(n,r[i]);
}

/*:9*/
#line 174 "./sat-tomography.w"
;
for(j= 1;j<=n;j++)/*17:*/
#line 324 "./sat-tomography.w"

{
sprintf(buf,"%dC",j);
for(i= 1;i<=m;i++)sprintf(name[i],"%dx%d",i,j);
gen_clauses(m,c[j]);
}

/*:17*/
#line 175 "./sat-tomography.w"
;
for(d= 1;d<m+n;d++)/*18:*/
#line 331 "./sat-tomography.w"

{
sprintf(buf,"%dA",d);
if(m<=n){
if(d<=m){
for(i= 1;i<=d;i++)sprintf(name[i],"%dx%d",i,d+1-i);
gen_clauses(d,a[d]);
}else if(d<=n){
for(i= 1;i<=m;i++)sprintf(name[i],"%dx%d",i,d+1-i);
gen_clauses(m,a[d]);
}else{
for(t= 1;t<=m+n-d;t++)sprintf(name[t],"%dx%d",d+t-n,n+1-t);
gen_clauses(m+n-d,a[d]);
}
}else{
if(d<=n){
for(i= 1;i<=d;i++)sprintf(name[i],"%dx%d",i,d+1-i);
gen_clauses(d,a[d]);
}else if(d<=m){
for(j= 1;j<=n;j++)sprintf(name[j],"%dx%d",d+1-j,j);
gen_clauses(n,a[d]);
}else{
for(t= 1;t<=m+n-d;t++)sprintf(name[t],"%dx%d",d+t-n,n+1-t);
gen_clauses(m+n-d,a[d]);
}
}
}

/*:18*/
#line 176 "./sat-tomography.w"
;
for(d= 1;d<m+n;d++)/*19:*/
#line 359 "./sat-tomography.w"

{
sprintf(buf,"%dB",d);
if(m<=n){
if(d<=m){
for(i= 1;i<=d;i++)sprintf(name[i],"%dx%d",i,n+i-d);
gen_clauses(d,b[d]);
}else if(d<=n){
for(i= 1;i<=m;i++)sprintf(name[i],"%dx%d",i,n+i-d);
gen_clauses(m,b[d]);
}else{
for(j= 1;j<=m+n-d;j++)sprintf(name[j],"%dx%d",j+d-n,j);
gen_clauses(m+n-d,b[d]);
}
}else{
if(d<=n){
for(i= 1;i<=d;i++)sprintf(name[i],"%dx%d",i,n+i-d);
gen_clauses(d,b[d]);
}else if(d<=m){
for(j= 1;j<=n;j++)sprintf(name[j],"%dx%d",j+d-n,j);
gen_clauses(n,b[d]);
}else{
for(j= 1;j<=m+n-d;j++)sprintf(name[j],"%dx%d",j+d-n,j);
gen_clauses(m+n-d,b[d]);
}
}
}

/*:19*/
#line 177 "./sat-tomography.w"
;

/*:8*/
#line 30 "./sat-tomography.w"
;
}

/*:1*/
