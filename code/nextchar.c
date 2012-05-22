int buffer[2048];
/* 前半分と後ろ半分に分けて使う。初期化はしてあると仮定 */

int nextchar()
{
  int i;
  if (forward == 1023) { /* 前半分の終わりだったら */
    for (i = 1024; i < 2048; i++) {
      buffer[i] = getc(file);
    }
    forward ++;
  }
  else if (forward == 2047) {
    /* 後ろ半分の終わりだったら */
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
