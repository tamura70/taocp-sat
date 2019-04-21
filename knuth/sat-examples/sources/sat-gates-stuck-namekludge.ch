@x to shorten the names of "prod" gates
  for (k=0;v->name[k];k++)
@y
  @<Shorten the name if necessary@>;
  for (k=0;v->name[k];k++)
@z
@x
printf("~ sat-gates-stuck %s %s\n",argv[1],argv[2]);
@y
printf("~ sat-gates-stuck-namekludge %s %s\n",argv[1],argv[2]);
@z
@x
@*Index.
@y
@ Here a name like \.{C34:13\char`\#19} becomes \.{C341319}.
In general I change all numbers to two digits, and delete the
colons and sharp signs.

@<Shorten the name if necessary@>=
if (v->name[0]<'A' || v->name[0]>'Z') {
  fprintf(stderr,"Vertex name %s didn't start with a code letter!\n",v->name);
  j=1;
}
{
  int i1,i2,i3;
  register i,d;
  for (i=1,d=0;v->name[i]>='0' && v->name[i]<='9';i++) d=10*d+v->name[i]-'0';
  if (d>99) {
    fprintf(stderr,"Vertex name %s has a number > 99!\n",v->name);
    j=1;
  }
  i1=d;
  if (v->name[i]!=':') goto okay;
  for (i++,d=0;v->name[i]>='0' && v->name[i]<='9';i++) d=10*d+v->name[i]-'0';
  if (d>99) {
    fprintf(stderr,"Vertex name %s has a number > 99!\n",v->name);
    j=1;
  }
  i2=d;
  if (v->name[i]!='#') goto okay;
  for (i++,d=0;v->name[i]>='0' && v->name[i]<='9';i++) d=10*d+v->name[i]-'0';
  if (d>99) {
    fprintf(stderr,"Vertex name %s has a number > 99!\n",v->name);
    j=1;
  }
  i3=d;
  if (v->name[i]) {
    fprintf(stderr,"Vertex name %s has unexpected structure!\n",v->name);
    j=1;
  }@+else if (i<8) goto okay;
  else sprintf(v->name+1,"%02d%02d%02d",i1,i2,i3);
okay:;
}

@*Index.
@z

