@x
  register int i,j,ii,jj,k,l;
@y
  register int i,j,ii,jj,k,l,reflectionsymmetryused=0;
@z
@x
printf("~ sat-oss %d %d %d\n",m,n,t);
@y
printf("~ sat-oss-sym %d %d %d\n",m,n,t);
@z
@x
      for (l=0;l+w[i][j]<=t+1-w[ii][jj];l++) {
@y
      if (!reflectionsymmetryused) 
        reflectionsymmetryused=1,printf("!%c%c%c%c\n",
                                    '0'+i,'0'+j,'0'+ii,'0'+jj);
      for (l=0;l+w[i][j]<=t+1-w[ii][jj];l++) {
@z
