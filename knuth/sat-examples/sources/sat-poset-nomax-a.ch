@x
@c
@y
This variant uses only the special cases of transitivity where
$i<j$ and $k<j$.
@c
@z
@x
printf("~ sat-poset-nomax %d\n",m);
@y
printf("~ sat-poset-nomax-a %d\n",m);
@z
@x
for (i=1;i<=m;i++) for (j=1;j<=m;j++) if (i!=j) {
  for (k=1;k<=m;k++) if (j!=k) {
@y
for (i=1;i<=m;i++) for (j=1;j<=m;j++) if (i<j) {
  for (k=1;k<=m;k++) if (k<j) {
@z
