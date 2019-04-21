@x
register column *cur_col;
@y
register column *cur_col,*last_col;
int newvars=1;
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
  if (k==2) {
    printf("~%d ~%d\n",cur_node->num+1,cur_node->down->num+1);
    continue;
  }
  while (k>4) {
    printf("%s%d ~%d\n",j?"t":"~",j?newvars-1:cur_node->num+1,
                 cur_node->down->num+1);
    printf("%s%d ~%d\n",j?"t":"~",j?newvars-1:cur_node->num+1,
                 cur_node->down->down->num+1);
    printf("%s%d ~t%d\n",j?"t":"~",j?newvars-1:cur_node->num+1,newvars);
    printf("~%d ~%d\n",cur_node->down->num+1,cur_node->down->down->num+1);
    printf("~%d ~t%d\n",cur_node->down->num+1,newvars);
    printf("~%d ~t%d\n",cur_node->down->down->num+1,newvars);
    j=1,newvars++,cur_node=cur_node->down->down,k-=2;
  }
  printf("%s%d ~%d\n",j?"t":"~",j?newvars-1:cur_node->num+1,cur_node->down->num+1);
  printf("%s%d ~%d\n",j?"t":"~",j?newvars-1:cur_node->num+1,
                 cur_node->down->down->num+1);
  printf("~%d ~%d\n",cur_node->down->num+1,cur_node->down->down->num+1);
  if (k==3) continue;
  printf("%s%d ~%d\n",j?"t":"~",j?newvars-1:cur_node->num+1,
                 cur_node->down->down->down->num+1);
  printf("~%d ~%d\n",cur_node->down->num+1,cur_node->down->down->down->num+1);
  printf("~%d ~%d\n",cur_node->down->down->num+1,cur_node->down->down->down->num+1);
}
@z
