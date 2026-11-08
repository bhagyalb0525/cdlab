%{
    #include<stdio.h>
    int v=0,c=0;
%}

%option noyywrap

%%
[aeiouAEIOU] {v++;}
[a-zA-Z]  {c++;}
.|\n  {}
%%

int main()
{
    printf("enter a string");
    yylex();

    printf("no.of vowels:%d\n",v);
    printf("no.of cons:%d",c);
}
