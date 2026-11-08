%{
#include <stdio.h>

int p = 0, c = 0, s = 0;
%}

%%
"("|")" {
    printf("%s is a parenthesis\n", yytext);
    p++;
}

"{"|"}" {
    printf("%s is a curly bracket\n", yytext);
    c++;
}

"["|"]" {
    printf("%s is a square bracket\n", yytext);
    s++;
}

.|\n ;
%%

int main()
{
    printf("Enter an expression:\n");
    yylex();

    printf("\nParentheses count = %d\n", p);
    printf("Curly brackets count = %d\n", c);
    printf("Square brackets count = %d\n", s);

    return 0;
}

int yywrap()
{
    return 1;
}
