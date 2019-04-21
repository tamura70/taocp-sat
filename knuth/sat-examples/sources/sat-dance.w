\datethis
@*Intro. Given an exact cover problem, presented on |stdin| in the
format used by {\mc DANCE}, we generate clauses for an equivalent
satisfiability problem in the format used by my {\mc SAT} routines.

I hacked this program by starting with {\mc DANCE}; then I replaced
the dancing links algorithm with a new back end. (A lot of the operations
performed are therefore pointless leftovers from the earlier routine.
Much of the commentary is also superfluous; I did this in a big hurry.)

Given a matrix whose elements are 0 or 1, the problem is to
find all subsets of its rows whose sum is at most~1 in all columns and
{\it exactly\/}~1 in all ``primary'' columns. The matrix is specified
in the standard input file as follows: Each column has a symbolic name,
either one or two or three characters long. The first line of input contains
the names of all primary columns, followed by `\.{\char"7C}', followed by
the names of all other columns.
(If all columns are primary, the~`\.{\char"7C}' may be omitted.)
The remaining lines represent the rows, by listing the columns where 1 appears.

@d max_level 150 /* at most this many rows in a solution */
@d max_degree 1000 /* at most this many branches per search tree node */
@d max_cols 10000 /* at most this many columns */
@d max_nodes 1000000 /* at most this many nonzero elements in the matrix */

@c
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
@<Type definitions@>@;
@<Global variables@>@;
@#
main(argc,argv)
  int argc;
  char *argv[];
{
  @<Local variables@>;
  @<Initialize the data structures@>;
  @<Output the clauses@>;
}

@*Data structures.
Each column of the input matrix is represented by a \&{column} struct,
and each row is represented as a linked list of \&{node} structs. There's one
node for each nonzero entry in the matrix.

More precisely, the nodes are linked circularly within each row, in
both directions. The nodes are also linked circularly within each column;
the column lists each include a header node, but the row lists do not.
Column header nodes are part of a \&{column} struct, which
contains further info about the column.

Each node contains five fields. Four are the pointers of doubly linked lists,
already mentioned; the fifth points to the column containing the node.

Well, actually I've now included a sixth field. It specifies the row number.

@s col_struct int

@<Type...@>=
typedef struct node_struct {
  struct node_struct *left,*right; /* predecessor and successor in row */
  struct node_struct *up,*down; /* predecessor and successor in column */
  struct col_struct *col; /* the column containing this node */
  int num; /* the row in which this node appears */
} node;

@ Each \&{column} struct contains five fields:
The |head| is a node that stands at the head of its list of nodes;
the |len| tells the length of that list of nodes, not counting the header;
the |name| is a one-, two-, or three-letter identifier;
|next| and |prev| point to adjacent columns, when this
column is part of a doubly linked list.

@<Type...@>=
typedef struct col_struct {
  node head; /* the list header */
  int len; /* the number of non-header items currently in this column's list */
  char name[8]; /* symbolic identification of the column, for printing */
  struct col_struct *prev,*next; /* neighbors of this column */
} column;

@ One |column| struct is called the root. It serves as the head of the
list of columns that need to be covered, and is identifiable by the fact
that its |name| is empty.

@d root col_array[0] /* gateway to the unsettled columns */

@*Inputting the matrix.
Brute force is the rule in this part of the program.

@<Initialize the data structures@>=
@<Read the column names@>;
@<Read the rows@>;

@ @d buf_size 4*max_cols+3 /* upper bound on input line length */

@<Glob...@>=
column col_array[max_cols+2]; /* place for column records */
node node_array[max_nodes]; /* place for nodes */
char buf[buf_size];
node *row[max_nodes]; /* the first node in each row */
int rowptr; /* this many rows have been seen */

@ @d panic(m) {@+fprintf(stderr,"%s!\n%s",m,buf);@+exit(-1);@+}

@<Read the column names@>=
cur_col=col_array+1;
fgets(buf,buf_size,stdin);
if (buf[strlen(buf)-1]!='\n') panic("Input line too long");
for (p=buf,primary=1;*p;p++) {
  while (isspace(*p)) p++;
  if (!*p) break;
  if (*p=='|') {
    primary=0;
    if (cur_col==col_array+1) panic("No primary columns");
    (cur_col-1)->next=&root, root.prev=cur_col-1;
    continue;
  }
  for (q=p+1;!isspace(*q);q++);
  if (q>p+7) panic("Column name too long");
  if (cur_col>=&col_array[max_cols]) panic("Too many columns");
  for (q=cur_col->name;!isspace(*p);q++,p++) *q=*p;
  cur_col->head.up=cur_col->head.down=&cur_col->head;
  cur_col->head.num=-1;
  cur_col->len=0;
  if (primary) cur_col->prev=cur_col-1, (cur_col-1)->next=cur_col;
  else cur_col->prev=cur_col->next=cur_col;
  cur_col++;
}
if (primary) {
  if (cur_col==col_array+1) panic("No primary columns");
  (cur_col-1)->next=&root, root.prev=cur_col-1;
}

@ @<Local variables@>=
register column *cur_col;
register char *p,*q;
register node *cur_node;
int primary;
int j,k;

@ @<Read the rows@>=
cur_node=node_array;
while (fgets(buf,buf_size,stdin)) {
  register column *ccol;
  register node *row_start;
  if (buf[strlen(buf)-1]!='\n') panic("Input line too long");
  row_start=NULL;
  for (p=buf;*p;p++) {
    while (isspace(*p)) p++;
    if (!*p) break;
    for (q=p+1;!isspace(*q);q++);
    if (q>p+7) panic("Column name too long");
    for (q=cur_col->name;!isspace(*p);q++,p++) *q=*p;
    *q='\0';
    for (ccol=col_array;strcmp(ccol->name,cur_col->name);ccol++);
    if (ccol==cur_col) panic("Unknown column name");
    if (cur_node==&node_array[max_nodes]) panic("Too many nodes");
    if (!row_start) row_start=cur_node;
    else cur_node->left=cur_node-1, (cur_node-1)->right=cur_node;
    cur_node->col=ccol;
    cur_node->up=ccol->head.up, ccol->head.up->down=cur_node;
    ccol->head.up=cur_node, cur_node->down=&ccol->head;
    ccol->len++;
    cur_node->num=rowptr;
    cur_node++;
  }
  if (!row_start) panic("Empty row");
  row[rowptr++]=row_start;
  row_start->left=cur_node-1, (cur_node-1)->right=row_start;
}

@*Clausing.
There's one variable for each row; its meaning is ``this row is in the cover.''
There are two kinds of clauses: For each primary column, we must select
one of its rows. For each pair of intersecting rows, we must not select
them both.

@<Output the clauses@>=
@<Output the column clauses@>;
@<Output the intersection clauses@>;

@ @<Output the column clauses@>=
for (cur_col=root.next; cur_col!=&root; cur_col=cur_col->next) {
  for (cur_node=cur_col->head.down; cur_node!=&cur_col->head; 
           cur_node=cur_node->down)
   printf(" %d",cur_node->num+1);
  printf("\n");
}

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

@*Index.
