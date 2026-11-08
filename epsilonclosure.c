#include <stdio.h>

int edge[20][20];
int n, m;

void closure(int start)
{
    int stack[20], c[20] = {0};
    int top = -1, i, state;

    c[start] = 1;
    stack[++top] = start;

    while(top != -1)
    {
        state = stack[top--];

        for(i = 0; i < n; i++)
        {
            if(edge[state][i] == 1 && c[i] == 0)
            {
                c[i] = 1;
                stack[++top] = i;
            }
        }
    }

    printf("E-closure(%d) = { ", start);

    for(i = 0; i < n; i++)
    {
        if(c[i] == 1)
            printf("%d ", i);
    }

    printf("}\n");
}

int main()
{
    int i, from, to;

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of epsilon transitions: ");
    scanf("%d", &m);

    printf("Enter epsilon transitions (from to):\n");

    for(i = 0; i < m; i++)
    {
        scanf("%d %d", &from, &to);
        edge[from][to] = 1;
    }

    printf("\nEpsilon closures:\n");

    for(i = 0; i < n; i++)
        closure(i);

    return 0;
}
