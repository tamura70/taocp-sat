/*1:*/
#line 6 "./sat-poset-nomax-a.ch"

#line 9 "./sat-poset-nomax.w"
#include <stdio.h> 
#include <stdlib.h> 
int m;
main(int argc,char*argv[]){
register i,j,k;
/*2:*/
#line 20 "./sat-poset-nomax.w"

if(argc!=2||sscanf(argv[1],"%d",&m)!=1){
fprintf(stderr,"Usage: %s m\n",argv[0]);
exit(-1);
}
#line 11 "./sat-poset-nomax-a.ch"
printf("~ sat-poset-nomax-a %d\n",m);
#line 26 "./sat-poset-nomax.w"

/*:2*/
#line 14 "./sat-poset-nomax.w"
;
/*3:*/
#line 27 "./sat-poset-nomax.w"

for(j= 1;j<=m;j++)
printf("~%d.%d\n",j,j);

/*:3*/
#line 15 "./sat-poset-nomax.w"
;
/*4:*/
#line 31 "./sat-poset-nomax.w"

#line 17 "./sat-poset-nomax-a.ch"
for(i= 1;i<=m;i++)for(j= 1;j<=m;j++)if(i<j){
for(k= 1;k<=m;k++)if(k<j){
#line 34 "./sat-poset-nomax.w"
printf("~%d.%d ~%d.%d %d.%d\n",
i,j,j,k,i,k);
}
}

/*:4*/
#line 16 "./sat-poset-nomax.w"
;
/*5:*/
#line 39 "./sat-poset-nomax.w"

for(j= 1;j<=m;j++){
for(k= 1;k<=m;k++)printf(" %d.%d",j,k);
printf("\n");
}

/*:5*/
#line 17 "./sat-poset-nomax.w"
;
}

/*:1*/
