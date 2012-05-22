%option main
%option noyywrap

%{
#define LT 0
#define LE 1
#define WHILE 2
#define ID 3
%}

%%
[ \t\n]+	{}
"<"		{printf("LT\n");}
"<="	{printf("LE\n");}
while	{printf("WHILE\n");}
[A-Za-z][0-9A-Za-z_]+	{printf("ID\n");}
%%
