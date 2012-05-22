%{
#define LT 0
#define LE 1
#define WHILE 2
#define ID 3
%}

%%
[ \t\n]+	{}
"<"		{return LT;}
"<="	{return LE;}
while	{return WHILE;}
[A-Za-z][0-9A-Za-z_]+	{return ID;}
%%
