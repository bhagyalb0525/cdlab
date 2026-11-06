%{
    #include<stdio.h>
%}

%option noyywrap

%%
abc {printf("ABC");}
.|\n  {ECHO;}
%%

int main()
{
    printf("enter a string");
    yylex();
    return 0;
}
