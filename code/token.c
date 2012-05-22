/* relop -> < | <= | == | != | > | >= $B$KBP$9$k(BC$B8@8l%3!<%INc(B */

int state = 0;
typedef int token;
int token_beginning = 0; /* $B;z6g@hF,0LCV(B */
int forward = 0; /* $BA0?J0LCV(B */

/* $B%H!<%/%s$NDj5A(B */
#define RELOP_LE 1
#define RELOP_LT 2
...

token nexttoken()
{
	while (1) {
		switch (state) {
			case 0:	c = nextchar(); /* $B<!$NJ8;z$rFI$_!"A0?J0LCV$r#1?J$a$k(B */
	  				if (c == '<') state = 1;
	  				else if (c == '=') state = 4;
					else if (c == '>') state = 7;
					else if (c == '!') state = 10;
					else state = fail();
					/* state $B$r<!$NA+0\?^$N=i4|>uBVHV9f$K%;%C%H(B */
					/* $B$5$i$K!"(Bfail()$B$NCf$GA0?J0LCV$r;z6g@hF,0LCV$KLa$9(B */
					break;
			case 1: c = nextchar();
					if (c == '=') state = 2;
					else state = 3;
					break;
			case 2:	token_beginning = forward;
					return(RELOP_LE);
			case 3:	retract(1); /* $BF~NO$r(B1$BJ8;zLa$9(B */
					token_beginning = forward;
					return(RELOP_LT);
			...
		}
	}
}

/* $B2~NIHG(B nexttoken()$B!#6uGr$NFI$_Ht$P$7!"<1JL;R!&M=Ls8l$N=hM}$r2C$($?(B */
token nexttoken()
{
	while (1) {
		switch (state) {
			case 0:	c = nextchar(); /* $B<!$NJ8;z$rFI$_!"A0?J0LCV$r#1?J$a$k(B */
					if (c == ' ' || c == '\t' || c == '\n') {
						state = 0;
						token_beginning ++; /* $B;z6g@hF,0LCV$r#1?J$a$k(B */
					}
	  				else if (c == '<') state = 1;
	  				else if (c == '=') state = 4;
					else if (c == '>') state = 7;
					else if (c == '!') state = 10;
					else state = fail();
					/* state $B$r<!$NA+0\?^$N=i4|>uBVHV9f$K%;%C%H(B */
					/* $B$5$i$K!"(Bfail()$B$NCf$GA0?J0LCV$r;z6g@hF,0LCV$KLa$9(B */
					break;
			case 1: c = nextchar();
					if (c == '=') state = 2;
					else state = 3;
					break;
			case 2:	token_beginning = forward;
					return(RELOP_LE);
			case 3:	retract(); /* $BF~NO$r(B1$BJ8;zLa$9(B */
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

int start = 0; /* $B8=:_$N=i4|>uBVHV9f(B */

int fail()
{
	forward = token_beginning; /* $BA0?J0LCV$r;z6g@hF,0LCV$K9g$o$;$k(B */
	switch (start) {
	case 0:	start = 13;
			break;
	...
	case 28:	recover(); /* $B%H!<%/%s$H$7$FG'<1$G$-$J$/$J$C$?$N$G!"%(%i!<=hM}(B */
				break;
	}
	return start;
}

/* nextchar(), retract() */
int buffer[2048]; /* $BA0H>J,$H8e$mH>J,$KJ,$1$F;H$&!#=i4|2=$O$7$F$"$k$H2>Dj(B */

int nextchar()
{
	int i;
	if (forward == 1023) { /* $BA0H>J,$N=*$o$j$@$C$?$i(B */
		for (i = 1024; i < 2048; i++) {
			buffer[i] = getchar();
		}
		forward ++;
	else if (forward == 2047) { /* $B8e$mH>J,$N=*$o$j$@$C$?$i(B */
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
