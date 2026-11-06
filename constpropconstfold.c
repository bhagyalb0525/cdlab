
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 50

char op[MAX][10], a1[MAX][20], a2[MAX][20], res[MAX][20];
char name[MAX][20], value[MAX][20];

int count, n;

int isNumber(char s[]) {
    int i;

    if (s[0] == '\0')
        return 0;

    for (i = 0; s[i]; i++)
        if (!isdigit((unsigned char)s[i]))
            return 0;

    return 1;
}

int lookup(char s[]) {
    int i;

    for (i = 0; i < n; i++)
        if (strcmp(name[i], s) == 0)
            return i;

    return -1;
}

void update(char r[], char v[]) {
    int i = lookup(r);

    if (i == -1)
        i = n++;

    strcpy(name[i], r);
    strcpy(value[i], v);
}

void optimize(int folding) {
    int i, p, x, y, z;
    char a[20], b[20], oper[10];

    n = 0;

    printf("\n%s\n", folding ?
           "WITH CONSTANT FOLDING" :
           "WITHOUT CONSTANT FOLDING");

    for (i = 0; i < count; i++) {
        strcpy(a, a1[i]);
        strcpy(b, a2[i]);
        strcpy(oper, op[i]);

        // Constant propagation
        p = lookup(a);
        if (p != -1 && strcmp(value[p], "#") != 0)
            strcpy(a, value[p]);

        p = lookup(b);
        if (p != -1 && strcmp(value[p], "#") != 0)
            strcpy(b, value[p]);

        // Constant folding
        if (folding && strcmp(oper, "=") != 0 &&
            isNumber(a) && isNumber(b)) {

            x = atoi(a);
            y = atoi(b);

            if (strcmp(oper, "+") == 0)
                z = x + y;
            else if (strcmp(oper, "-") == 0)
                z = x - y;
            else if (strcmp(oper, "*") == 0)
                z = x * y;
            else if (strcmp(oper, "/") == 0 && y != 0)
                z = x / y;
            else
                goto print;

            sprintf(a, "%d", z);
            strcpy(oper, "=");
        }

        print:

        if (strcmp(oper, "=") == 0)
            printf("%s = %s\n", res[i], a);
        else
            printf("%s = %s %s %s\n",
                   res[i], a, oper, b);

        // Update symbol table
        if (strcmp(oper, "=") == 0 && isNumber(a))
            update(res[i], a);
        else
            update(res[i], "#");
    }
}

int main() {
    int i;

    printf("Enter number of statements: ");
    scanf("%d", &count);

    printf("Enter quadruples (OP ARG1 ARG2 RESULT):\n");

    for (i = 0; i < count; i++)
        scanf("%s %s %s %s",
              op[i], a1[i], a2[i], res[i]);

    optimize(0);
    optimize(1);

    return 0;
}
