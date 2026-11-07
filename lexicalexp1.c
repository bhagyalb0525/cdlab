
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *keywords[] = {
    "int", "char", "float", "double", "void",
    "if", "else", "while", "for", "return", "main"
};

char symbols[100][20];
int count = 0;

int isKeyword(char s[])
{
    int i;

    for(i = 0; i < 11; i++)
        if(strcmp(s, keywords[i]) == 0)
            return 1;

    return 0;
}

int lookup(char s[])
{
    int i;

    for(i = 0; i < count; i++)
        if(strcmp(symbols[i], s) == 0)
            return i;

    strcpy(symbols[count], s);
    return count++;
}

int main()
{
    FILE *fp;
    char ch, word[20];
    int i, line = 1;

    fp = fopen("input.txt", "r");

    if(fp == NULL)
    {
        printf("File not found");
        return 0;
    }

    printf("Line\tToken\t\tLexeme\t\tEntry\n");

    while((ch = fgetc(fp)) != EOF)
    {
        if(ch == '\n')
        {
            line++;
        }

        else if(isalpha(ch) || ch == '_')
        {
            i = 0;
            word[i++] = ch;

            while(isalnum(ch = fgetc(fp)) || ch == '_')
                word[i++] = ch;

            word[i] = '\0';
            ungetc(ch, fp);

            if(isKeyword(word))
                printf("%d\tKeyword\t\t%s\n", line, word);

            else
                printf("%d\tIdentifier\t%s\t%d\n",
                       line, word, lookup(word));
        }

        else if(isdigit(ch))
        {
            printf("%d\tDigit\t\t%c\n", line, ch);
        }

        else if(ch == '+' || ch == '-' ||
                ch == '*' || ch == '/' || ch == '%')
        {
            printf("%d\tArithmetic Op\t%c\n", line, ch);
        }

        else if(ch == '<' || ch == '>' ||
                ch == '=' || ch == '!')
        {
            printf("%d\tRelational Op\t%c\n", line, ch);
        }

        else if(ch == '(' || ch == ')' ||
                ch == '{' || ch == '}' ||
                ch == ';' || ch == ',')
        {
            printf("%d\tSpecial Symbol\t%c\n", line, ch);
        }
    }

    fclose(fp);

    printf("\nSymbol Table\n");
    printf("Entry\tIdentifier\n");

    for(i = 0; i < count; i++)
        printf("%d\t%s\n", i, symbols[i]);

    return 0;
}
