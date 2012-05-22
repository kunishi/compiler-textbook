#include <ctype.h>

int fail(char *s, int i)
{
  int j;
  for (j = 0; j < i; j ++) {
    backchar(s[j], file);
  }
  switch (start) {
  case 0:
    start = 4;
    break;
  case 4:
    start = 10;
    break;
  case 10:
    /* $B$I$N%H!<%/%s$bG'<1<:GT(B */
    break;
  }
  return start;
}

int nexttoken()
{
  int c; /* $B8=:_=hM}Cf$NJ8;z(B */
  char s[80]; /* $B=i4|>uBV$+$i8=:_$^$G$K=hM}$7$?J8;zNs(B */
  int i = 0;

  /* $BBg0hJQ?t$N=i4|2=(B */
  state = 0;
  start = 0;
  yytext[0] = '\0';

  while (1) {
    switch (state) {
    case 0:
      c = nextchar(file);
      if (c == ' ' || c == '\t' || c == '\n')
        state = 0; /* $B6uGr$NFI$_Ht$P$7(B */
      else if (c == '<') {
        state = 1;
        s[i++] = c;
      } else /* 1 $B$DL\$N%*!<%H%^%H%s$O<:GT(B */
        state = fail(s, i);
      break;
    case 1:
      c = nextchar(file);
      if (c == '=') {
        state = 2;
        s[i++] = c;
      } else
        state = 3;
      break;
    case 2:
      return LE;
    case 3:
      backchar(c, file); /* 1 $BJ8;zGK4~(B */
      return LT;
    case 4:
      c = nextchar(file);
      s[i++] = c;
      if (c == 'w')
        state = 5;
      else
        state = fail(s, i);
      break;
    case 5:
      c = nextchar(file);
      s[i++] = c;
      if (c == 'h')
        state = 6;
      else
        state = fail(s, i);
      break;
    case 6:
      c = nextchar(file);
      s[i++] = c;
      if (c == 'i')
        state = 7;
      else
        state = fail(s, i);
      break;
    case 7:
      c = nextchar(file);
      s[i++] = c;
      if (c == 'l')
        state = 8;
      else
        state = fail(s, i);
      break;
    case 8:
      c = nextchar(file);
      s[i++] = c;
      if (c == 'e')
        state = 9;
      else
        state = fail(s, i);
      break;
    case 9:
      return WHILE;
    case 10:
      c = nextchar(file);
      s[i++] = c;
      if (isalpha(c) || c == '_')
        state = 11;
      else
        state = fail(s, i);
      break;
    case 11:
      c = nextchar(file);
      s[i++] = c;
      if (isalpha(c) || isdigit(c) || c == '_')
        state = 11;
      else
        state = 12;
      break;
    case 12:
      backchar(c, file);
      s[i] = '\0'; /* $BFI$_9~$_$9$.$?(B c $B$r(B \0 $B$G>e=q$-(B */
      strcpy(s, yytext);
      return ID;
    }
  }
}
