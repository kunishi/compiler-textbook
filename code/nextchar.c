int buffer[2048];
/* $BA0H>J,$H8e$mH>J,$KJ,$1$F;H$&!#=i4|2=$O$7$F$"$k$H2>Dj(B */

int nextchar()
{
  int i;
  if (forward == 1023) { /* $BA0H>J,$N=*$o$j$@$C$?$i(B */
    for (i = 1024; i < 2048; i++) {
      buffer[i] = getc(file);
    }
    forward ++;
  }
  else if (forward == 2047) {
    /* $B8e$mH>J,$N=*$o$j$@$C$?$i(B */
    for (i = 0; i < 1024; i++) {
      buffer[i] = getc(file);
    }
    forward = 0;
  }
  else forward ++;
  return buffer[forward];
}

void backchar()
{
  if (forward == 0) {
    forward = 2047;
  } else {
    forward --;
  }
}
