@x
int rowptr; /* this many rows have been seen */
@y
int rowptr; /* this many rows have been seen */
int cases[7]; /* row numbers for at-most-one constraints */
@z
@x
register column *cur_col;
@y
register column *cur_col,*last_col;
@z
@x
@<Output the clauses@>=
@y
@<Output the clauses@>=
last_col=cur_col;
@z
@x
@ @<Output the intersection clauses@>=
for (j=0;j<rowptr;j++) {
  for (cur_node=row[j]->right;cur_node!=row[j];cur_node=cur_node->right)
    cur_node->col->head.num=j;
  cur_node->col->head.num=j;
  for (k=j+1;k<rowptr;k++) {
    for (cur_node=row[k]->right;cur_node!=row[k];cur_node=cur_node->right)
      if (cur_node->col->head.num==j) goto clash;
    if (cur_node->col->head.num==j) goto clash;
    continue;
clash: printf("~%d ~%d\n",j+1,k+1);
  }
}  
@y
@ @<Output the intersection clauses@>=
for (cur_col=root.next;cur_col<last_col;cur_col++) {
  for (k=0,cur_node=cur_col->head.down;
        cur_node!=&cur_col->head;cur_node=cur_node->down) k++;
  if (k==1) continue;
  j=0, cur_node=cur_col->head.down;
  if (k<7) @<Use direct exclusion@>@;
  else @<Use Prestwich's broadcast method@>;
}

@ @<Use direct exclusion@>=
{
  while (j<k) cases[j++]=cur_node->num+1,cur_node=cur_node->down;
  while (k>1) {
    k--;
    for (j=0;j<k;j++) printf("~%d ~%d\n",cases[j],cases[k]);
  }
}

@ The auxiliary variables for column $c$ are named by appending \.@@,
\.A, \.B, \dots\ to the number~$c$. We ``broadcast'' to the auxiliary
variables the route to node $k+j$ in the complete binary tree,
for $0\le j<k$.

@<Use Prestwich's broadcast method@>=
{
  register i,b,t;
  for (;j<k;j++,cur_node=cur_node->down) {
    b=k+j;
    for (t=1;t<=b;t<<=1);
    for (i='@@',t>>=2;t;t>>=1,i++)
      printf("~%d %s%ld%c\n",
         cur_node->num+1,(b&t?"":"~"),cur_col-root.next,i);
  }
}    
@z
