@x
@c
@y
This variant uses only the special cases of transitivity where
$i\le k$ and $j<k$.
@c
@z
@x
printf("~ sat-poset-nomax %d\n",m);
@y
printf("~ sat-poset-nomax-b %d\n",m);
@z
@x
  for (k=1;k<=m;k++) if (j!=k) {
@y
  for (k=i;k<=m;k++) if (k>j) {
@z
