
%{
#include <stdio.h>

int lines = 0, words = 0, chars = 0;
%}

%%
\n                  { lines++; }
[ \t]               { }
[A-Za-z]+           { words++; chars += yyleng; }
%%

int yywrap()
{
    return 1;
}

int main()
{
    printf("Enter the text:\n");
    yylex();

    printf("\nRESULTS\n");
    printf("Lines: %d\n", lines);
    printf("Words: %d\n", words);
    printf("Characters: %d\n", chars);

    return 0;
}
