@x
  printf("~ sat-erdos-disc %d\n",n);
@y
  printf("~ sat-erdos-disc-res %d\n",n);
@z
@x
small~$t$ by using the facts that $S_j^0=1$ and $S_0^k=0$.)
@y
small~$t$ by using the facts that $S_j^0=1$ and $S_0^k=0$.)

Furthermore, we simplify yet again by using resolution to
eliminate the \.A and \.C variables, as well as \.{%d%B1}.
@z
@x
@ @<Generate the first clauses@>=
{
  printf("~%dB%d %dA%d\n",
           d,t,d,t+1);
  printf("~%dC%d %dB%d\n",
           d,t,d,t+1);
  printf("%dB%d ~%dC%d\n",
           d,t,d,t);
  printf("%dA%d ~%dB%d\n",
           d,t+1,d,t+1);
}

@ @<Generate the second clauses@>=
{
  if (t>1) {
    printf("~X%d %dA%d\n",
           d*(t+t-2),d,t);
    printf("X%d ~%dC%d\n",
           d*(t+t-2),d,t-1);
    printf("~X%d ~%dA%d %dB%d\n",
           d*(t+t-1),d,t,d,t);
    printf("X%d %dC%d ~%dB%d\n",
           d*(t+t-1),d,t-1,d,t);
  } else {
    printf("~X%d %dB%d\n",
              d,d,1);
    printf("X%d ~%dB%d\n",
              d,d,1);
  }
  printf("~X%d ~%dB%d %dC%d\n",
            d*(t+t),d,t,d,t);
  printf("X%d %dB%d ~%dA%d\n",
            d*(t+t),d,t,d,t+1);
  printf("~X%d ~%dC%d\n",
            d*(t+t+1),d,t);
  printf("X%d %dA%d\n",
            d*(t+t+1),d,t+1);
}
@y
@ @<Generate the first clauses@>=
{
  if (t>1) {
    printf("~X%d ~%dB%d %dB%d\n",
            d*(t+t+1),d,t,d,t+1);
    printf("~X%d ~%dB%d %dB%d\n",
            d*(t+t),d,t,d,t+1);
    printf("X%d %dB%d ~%dB%d\n",
            d*(t+t+1),d,t,d,t+1);
    printf("X%d %dB%d ~%dB%d\n",
            d*(t+t),d,t,d,t+1);
  } else {
    printf("~X%d ~X%d %dB%d\n",
            d*3,d,d,t+1);
    printf("~X%d ~X%d %dB%d\n",
            d*2,d,d,t+1);
    printf("X%d X%d ~%dB%d\n",
            d*3,d,d,t+1);
    printf("X%d X%d ~%dB%d\n",
            d*2,d,d,t+1);
  }
}

@ @<Generate the second clauses@>=
{
  if (t>1) {
    printf("X%d X%d %dB%d\n",
             d*(t+t),d*(t+t+1),d,t);
    if (2*t+3<=n) printf("X%d X%d ~%dB%d\n",
             d*(t+t),d*(t+t+1),d,t+1);
    printf("~X%d ~X%d ~%dB%d\n",
             d*(t+t),d*(t+t+1),d,t);
    if (2*t+3<=n) printf("~X%d ~X%d %dB%d\n",
             d*(t+t),d*(t+t+1),d,t+1);
  } else {
    printf("X%d X%d X%d\n",
             d*(t+t),d*(t+t+1),d);
    if (5<=n) printf("X%d X%d ~%dB%d\n",
             d*(t+t),d*(t+t+1),d,2);
    printf("~X%d ~X%d ~X%d\n",
             d*(t+t),d*(t+t+1),d);
    if (5<=n) printf("~X%d ~X%d %dB%d\n",
             d*(t+t),d*(t+t+1),d,2);
  }
}
@z
