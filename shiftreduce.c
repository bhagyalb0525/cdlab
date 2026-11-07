#include <stdio.h>
#include <string.h>

char L[20], R[20][20];
int n;

int findHandle(char stack[], int top)
{
    int i, j, len, start;

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
    int i, j, top = 0, ip = 0, prod;

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

        if(input[ip] != '$')
        {
            stack[++top] = input[ip++];
            stack[top+1] = '\0';

            printf("Shift %c\n", stack[top]);
        }
        else
        {
            prod = findHandle(stack, top);

            if(prod != -1)
            {
                printf("Reduce %c->%s\n", L[prod], R[prod]);

                top = top - strlen(R[prod]);

                stack[++top] = L[prod];
                stack[top+1] = '\0';
            }
            else
            {
                if(strcmp(stack, "$E") == 0)
                    printf("Accepted\n");
                else
                    printf("Rejected\n");

                break;
            }
        }
    }

    return 0;
}
