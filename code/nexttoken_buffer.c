#include <ctype.h>

int fail()
{
  forward = beginning;
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

  /* $BBg0hJQ?t$N=i4|2=(B */
  state = 0;
  start = 0;
  yytext[0] = '\0';

  while (1) {
    switch (state) {
    case 0:
      c = nextchar();
      if (c == ' ' || c == '\t' || c == '\n') {
        state = 0; /* $B6uGr$NFI$_Ht$P$7(B */
        beginning ++;
      }
      else if (c == '<')
        state = 1;
      else /* 1 $B$DL\$N%*!<%H%^%H%s$O<:GT(B */
        state = fail();
      break;
    case 1:
      c = nextchar();
      if (c == '=')
        state = 2;
      else
        state = 3;
      break;
    case 2:
      return LE;
    case 3:
      backchar(); /* 1 $BJ8;zGK4~(B */
      return LT;
    case 4:
      c = nextchar();
      if (c == 'w')
        state = 5;
      else
        state = fail();
      break;
    case 5:
      c = nextchar();
      if (c == 'h')
        state = 6;
      else
        state = fail();
      break;
    case 6:
      c = nextchar();
      if (c == 'i')
        state = 7;
      else
        state = fail();
      break;
    case 7:
      c = nextchar();
      if (c == 'l')
        state = 8;
      else
        state = fail();
      break;
    case 8:
      c = nextchar();
      if (c == 'e')
        state = 9;
      else
        state = fail();
      break;
    case 9:
      return WHILE;
    case 10:
      c = nextchar();
      if (isalpha(c) || c == '_')
        state = 11;
      else
        state = fail();
      break;
    case 11:
      c = nextchar();
      if (isalpha(c) || isdigit(c) || c == '_')
        state = 11;
      else
        state = 12;
      break;
    case 12:
      backchar();
      strncpy(&buffer[beginning],
              forward - beginning + 1,
              yytext);
      return ID;
    }
  }
}
