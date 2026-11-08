
%{
#include <stdio.h>
%}

%option noyywrap

%%

"int"|"float"|"char"|"double"|"void"|"if"|"else"|"while"|"for"|"return" {
    printf("%s\t KEYWORD\n", yytext);
}

[a-zA-Z_][a-zA-Z0-9_]* {
    printf("%s\t IDENTIFIER\n", yytext);
}

[0-9]+ {
    printf("%-15s INTEGER CONSTANT\n", yytext);
}

"<="|">="|"=="|"!="|"<"|">" {
    printf("%-15s RELATIONAL OPERATOR\n", yytext);
}

"=" {
    printf("%-15s ASSIGNMENT OPERATOR\n", yytext);
}

"+"|"-"|"*"|"/"|"%" {
    printf("%-15s ARITHMETIC OPERATOR\n", yytext);
}

";"|","|"("|")"|"{"|"}"|"["|"]" {
    printf("%-15s SPECIAL SYMBOL\n", yytext);
}

[ \t\n]+   ;

. {
    printf("%-15s UNKNOWN\n", yytext);
}

%%

int main()
{
    FILE *fp;

    fp = fopen("input.txt", "r");

    if(fp == NULL)
    {
        printf("File not found\n");
        return 1;
    }

    yyin = fp;

    printf("LEXEME\tTOKEN\n");

    yylex();

    fclose(fp);

    return 0;
}
