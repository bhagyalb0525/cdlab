
#include <stdio.h>
#include <string.h>

char input[100];
int pos = 0;

int E();
int Ep();
int T();
int Tp();
int F();

int E()
{
    if (T())
        return Ep();

    return 0;
}

int Ep()
{
    if (input[pos] == '+' || input[pos] == '-')
    {
        pos++;

        if (T())
            return Ep();

        return 0;
    }

    if (input[pos] == ')' || input[pos] == '\0')
        return 1;

    return 0;
}

int T()
{
    if (F())
        return Tp();

    return 0;
}

int Tp()
{
    if (input[pos] == '*' || input[pos] == '/')
    {
        pos++;

        if (F())
            return Tp();

        return 0;
    }

    if (input[pos] == '+' || input[pos] == '-' ||
        input[pos] == ')' || input[pos] == '\0')
        return 1;

    return 0;
}

int F()
{
    if (isalpha(input[pos]))
    {
        pos++;
        return 1;
    }

    if (input[pos] == '(')
    {
        pos++;

        if (E())
        {
            if (input[pos] == ')')
            {
                pos++;
                return 1;
            }
        }

        return 0;
    }

    return 0;
}

int main()
{
    printf("Enter a string: ");
    scanf("%99s", input);

    pos = 0;

    if (E() && input[pos] == '\0')
        printf("String accepted\n");
    else
        printf("String rejected\n");

    return 0;
}
