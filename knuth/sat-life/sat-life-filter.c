/*1:*/
#line 9 "./sat-life-filter.w"

#include <stdio.h> 
#include <stdlib.h> 
char pix[101][101];
/*2:*/
#line 22 "./sat-life-filter.w"

int nextchar(void){
register int c= fgetc(stdin);
if(c!=EOF)return c;
exit(-1);
}

/*:2*/
#line 13 "./sat-life-filter.w"
;
main(){
register int c,i,j,bit,maxi= 0,maxj= 0;
while(1){
if(feof(stdin))break;
/*3:*/
#line 29 "./sat-life-filter.w"

for(c= nextchar();c==' ';){
/*4:*/
#line 35 "./sat-life-filter.w"

c= nextchar();
if(c!='~')bit= 1;
else{
bit= 0;
c= nextchar();
}
for(i= 0;c>='0'&&c<='9';c= nextchar())i= 10*i+c-'0';
if(i>=100){
fprintf(stderr,"Eh? I found a number of more than two digits!\n");
exit(-2);
}
if(c!='a')goto litdone;
c= nextchar();
for(j= 0;c>='0'&&c<='9';c= nextchar())j= 10*j+c-'0';
if(j>=100){
fprintf(stderr,"Eh? I found a number of more than two digits!\n");
exit(-2);
}
if(c!=' '&&c!='\n')goto litdone;
/*5:*/
#line 58 "./sat-life-filter.w"

if(i> maxi)maxi= i;
if(j> maxj)maxj= j;
pix[i][j]= bit;

/*:5*/
#line 55 "./sat-life-filter.w"
;
litdone:while(c!=' '&&c!='\n')c= nextchar();

/*:4*/
#line 31 "./sat-life-filter.w"
;
}
/*6:*/
#line 63 "./sat-life-filter.w"

for(i= 0;i<=maxi+1;i++){
for(j= 0;j<=maxj+1;j++)putchar(pix[i][j]?'*':'.');
putchar('\n');
}
putchar('\n');

/*:6*/
#line 33 "./sat-life-filter.w"
;

/*:3*/
#line 18 "./sat-life-filter.w"
;
}
}

/*:1*/
