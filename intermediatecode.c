
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char stack[100];
int top = -1;

char postfix[100];
int p = 0;

char op[100], arg1[100][20], arg2[100][20], res[100][20];
char values[100][20];

int count = 0, vtop = -1;

int precedence(char c)
{
    if (c == '*' || c == '/')
        return 2;

    if (c == '+' || c == '-')
        return 1;

    return 0;
}

void push(char c)
{
    stack[++top] = c;
}

char pop()
{
    return stack[top--];
}

int main()
{
    char infix[100];
    int i;

    printf("Enter arithmetic expression: ");
    scanf("%99s", infix);

    /* Infix to Postfix */

    for (i = 0; infix[i] != '\0'; i++)
    {
        char c = infix[i];

        if (isalnum((unsigned char)c))
        {
            postfix[p++] = c;
        }
        else if (c == '(')
        {
            push(c);
        }
        else if (c == ')')
        {
            while (top != -1 && stack[top] != '(')
                postfix[p++] = pop();

            if (top != -1)
                pop();
        }
        else
        {
            while (top != -1 && stack[top] != '(' &&
                   precedence(stack[top]) >= precedence(c))
            {
                postfix[p++] = pop();
            }

            push(c);
        }
    }

    while (top != -1)
        postfix[p++] = pop();

    postfix[p] = '\0';

    printf("\nPostfix: %s\n", postfix);

    /* Intermediate Code Generation */

    for (i = 0; postfix[i] != '\0'; i++)
    {
        char c = postfix[i];

        if (isalnum((unsigned char)c))
        {
            vtop++;
            values[vtop][0] = c;
            values[vtop][1] = '\0';
        }
        else
        {
            char a[20], b[20], temp[20];

            strcpy(b, values[vtop--]);
            strcpy(a, values[vtop--]);

            sprintf(temp, "t%d", count + 1);

            op[count] = c;
            strcpy(arg1[count], a);
            strcpy(arg2[count], b);
            strcpy(res[count], temp);

            strcpy(values[++vtop], temp);

            count++;
        }
    }

    /* Quadruple Representation */

    printf("\nQUADRUPLE FORM\n");
    printf("OP\tARG1\tARG2\tRESULT\n");

    for (i = 0; i < count; i++)
    {
        printf("%c\t%s\t%s\t%s\n",
               op[i], arg1[i], arg2[i], res[i]);
    }

    /* Triple Representation */

    printf("\nTRIPLE FORM\n");
    printf("OP\tARG1\tARG2\n");

    for (i = 0; i < count; i++)
    {
        printf("%c\t%s\t%s\n",
               op[i], arg1[i], arg2[i]);
    }

    return 0;
}
