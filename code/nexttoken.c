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
    /* どのトークンも認識失敗 */
    break;
  }
  return start;
}

int nexttoken()
{
  int c; /* 現在処理中の文字 */
  char s[80]; /* 初期状態から現在までに処理した文字列 */
  int i = 0;

  /* 大域変数の初期化 */
  state = 0;
  start = 0;
  yytext[0] = '\0';

  while (1) {
    switch (state) {
    case 0:
      c = nextchar(file);
      if (c == ' ' || c == '\t' || c == '\n')
        state = 0; /* 空白の読み飛ばし */
      else if (c == '<') {
        state = 1;
        s[i++] = c;
      } else /* 1 つ目のオートマトンは失敗 */
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
      backchar(c, file); /* 1 文字破棄 */
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
      s[i] = '\0'; /* 読み込みすぎた c を \0 で上書き */
      strcpy(s, yytext);
      return ID;
    }
  }
}
