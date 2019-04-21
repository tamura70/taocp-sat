@x
choosing bits to add in a first-in-first-out manner. Change files will
readily adapt this algorithm to other queuing disciplines.
@y
choosing bits to add in a last-in-first-out manner.
@z
@x
  printf("~ sat-dadda %d %d %s\n",m,n,argv[3]);
@y
  printf("~ sat-dadda-lifo %d %d %s\n",m,n,argv[3]);
@z
@x
@ Finally, here's where I use the first-in-first-out queuing discipline.
(Clumsily.)

@<Choose |addend[i]|@>=
{
  addend[i]=bin[k][0];
  for (l=1;l<size[k];l++) bin[k][l-1]=bin[k][l];
  size[k]=l-1;
}
@y
@ Finally, here's where I use the last-in-first-out queuing discipline.

@<Choose |addend[i]|@>=
{
  l=size[k]-1;
  addend[i]=bin[k][l];
  size[k]=l;
}
@z

