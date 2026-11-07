#include <stdio.h>
#include <string.h>

char L[20], R[20][20];
int n;

char table[7][7] = {
    {'>', '>', '<', '<', '<', '<', '>'},
    {'>', '>', '<', '<', '<', '<', '>'},
    {'>', '>', '>', '>', '<', '<', '>'},
    {'>', '>', '>', '>', '<', '<', '>'},
    {'>', '>', '>', '>', '<', '<', '>'},
    {'>', '>', '>', '>', '>', 'e', '>'},
    {'<', '<', '<', '<', '<', '<', 'a'}
};

int topTerminal(char stack[], int top)
{
    while(top >= 0)
    {
        if(strchr("+-*/^i$", stack[top]) != NULL)
            return top;

        top--;
    }

    return -1;
}

int findHandle(char stack[], int top)
{
    int i, j, start, len;

    for(i = 0; i < n; i++)
    {
        len = strlen(R[i]);
        start = top - len + 1;

        if(start < 0)
            continue;

        for(j = 0; j < len; j++)
        {
            if(stack[start+j] != R[i][j])
                break;
        }

        if(j == len)
            return i;
    }

    return -1;
}

int main()
{
    char p[30], input[100], stack[100];
    int i, j, top = 0, ip = 0;
    int t, r, k, prod;
    char rel;

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions:\n");

    for(i = 0; i < n; i++)
    {
        scanf("%s", p);

        L[i] = p[0];

        for(j = 2; p[j] != '\0'; j++)
            R[i][j-2] = p[j];

        R[i][j-2] = '\0';
    }

    printf("Enter input string: ");
    scanf("%s", input);

    if(input[strlen(input)-1] != '$')
        strcat(input, "$");

    stack[0] = '$';
    stack[1] = '\0';

    printf("\nSTACK\t\tINPUT\t\tACTION\n");

    while(1)
    {
        printf("%s\t\t%s\t\t", stack, input+ip);

        t = topTerminal(stack, top);

        if(t == -1)
        {
            printf("Rejected\n");
            break;
        }

        if(stack[t] == '+') r = 0;
        else if(stack[t] == '-') r = 1;
        else if(stack[t] == '*') r = 2;
        else if(stack[t] == '/') r = 3;
        else if(stack[t] == '^') r = 4;
        else if(stack[t] == 'i') r = 5;
        else if(stack[t] == '$') r = 6;
        else
        {
            printf("Rejected\n");
            break;
        }

        if(input[ip] == '+') k = 0;
        else if(input[ip] == '-') k = 1;
        else if(input[ip] == '*') k = 2;
        else if(input[ip] == '/') k = 3;
        else if(input[ip] == '^') k = 4;
        else if(input[ip] == 'i') k = 5;
        else if(input[ip] == '$') k = 6;
        else
        {
            printf("Rejected\n");
            break;
        }

        rel = table[r][k];

        if(rel == '<' || rel == '=')
        {
            stack[++top] = input[ip++];
            stack[top+1] = '\0';

            printf("Shift %c\n", stack[top]);
        }

        else if(rel == '>')
        {
            prod = findHandle(stack, top);

            if(prod == -1)
            {
                printf("Rejected: Invalid handle\n");
                break;
            }

            printf("Reduce %c->%s\n", L[prod], R[prod]);

            top = top - strlen(R[prod]);

            stack[++top] = L[prod];
            stack[top+1] = '\0';
        }

        else if(rel == 'a')
        {
            if(strcmp(stack, "$A") == 0)
                printf("Accepted\n");
            else
                printf("Rejected\n");

            break;
        }

        else
        {
            printf("Rejected\n");
            break;
        }
    }

    return 0;
}
