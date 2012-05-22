/* relop -> < | <= | == | != | > | >= に対するC言語コード例 */

int state = 0;
typedef int token;
int token_beginning = 0; /* 字句先頭位置 */
int forward = 0; /* 前進位置 */

/* トークンの定義 */
#define RELOP_LE 1
#define RELOP_LT 2
...

token nexttoken()
{
	while (1) {
		switch (state) {
			case 0:	c = nextchar(); /* 次の文字を読み、前進位置を１進める */
	  				if (c == '<') state = 1;
	  				else if (c == '=') state = 4;
					else if (c == '>') state = 7;
					else if (c == '!') state = 10;
					else state = fail();
					/* state を次の遷移図の初期状態番号にセット */
					/* さらに、fail()の中で前進位置を字句先頭位置に戻す */
					break;
			case 1: c = nextchar();
					if (c == '=') state = 2;
					else state = 3;
					break;
			case 2:	token_beginning = forward;
					return(RELOP_LE);
			case 3:	retract(1); /* 入力を1文字戻す */
					token_beginning = forward;
					return(RELOP_LT);
			...
		}
	}
}

/* 改良版 nexttoken()。空白の読み飛ばし、識別子・予約語の処理を加えた */
token nexttoken()
{
	while (1) {
		switch (state) {
			case 0:	c = nextchar(); /* 次の文字を読み、前進位置を１進める */
					if (c == ' ' || c == '\t' || c == '\n') {
						state = 0;
						token_beginning ++; /* 字句先頭位置を１進める */
					}
	  				else if (c == '<') state = 1;
	  				else if (c == '=') state = 4;
					else if (c == '>') state = 7;
					else if (c == '!') state = 10;
					else state = fail();
					/* state を次の遷移図の初期状態番号にセット */
					/* さらに、fail()の中で前進位置を字句先頭位置に戻す */
					break;
			case 1: c = nextchar();
					if (c == '=') state = 2;
					else state = 3;
					break;
			case 2:	token_beginning = forward;
					return(RELOP_LE);
			case 3:	retract(); /* 入力を1文字戻す */
					token_beginning = forward;
					return(RELOP_LT);
			...
			case 13:	c = nextchar();
						if (isletter(c)) state = 14;
						else state = fail();
						break;
			case 14:	c = nextchar();
						if (isletter(c)) state = 14;
						else state = 15;
						break;
			case 15:	retract();
						install_id();
						return (gettoken());
			...
		}
	}
}

int start = 0; /* 現在の初期状態番号 */

int fail()
{
	forward = token_beginning; /* 前進位置を字句先頭位置に合わせる */
	switch (start) {
	case 0:	start = 13;
			break;
	...
	case 28:	recover(); /* トークンとして認識できなくなったので、エラー処理 */
				break;
	}
	return start;
}

/* nextchar(), retract() */
int buffer[2048]; /* 前半分と後ろ半分に分けて使う。初期化はしてあると仮定 */

int nextchar()
{
	int i;
	if (forward == 1023) { /* 前半分の終わりだったら */
		for (i = 1024; i < 2048; i++) {
			buffer[i] = getchar();
		}
		forward ++;
	else if (forward == 2047) { /* 後ろ半分の終わりだったら */
		for (i = 0; i < 1024; i++) {
			buffer[i] = getchar();
		}
		forward = 0;
	}
	else forward ++;
	return buffer[forward];
}

void retract()
{
	if (forward == 0) {
		forward = 2047;
	} else {
		forward --;
	}
}
