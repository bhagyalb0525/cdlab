#include<stdio.h>
#include<string.h>
#include<ctype.h>

#define MAXP 100
#define MAXR 100

char lhs[MAXP];
char rhs[MAXP][MAXR];
int n;

int first[26][128];
int follow[26][128];

int isNT(char c)
{
    return (c>='A' && c<='Z');
}

int add(int set[26][128],char nt,char symbol)
{
    int index=nt-'A';
    unsigned char c=(unsigned char)symbol;
    if (!set[index][c]){
        set[index][c]=1;
        return 1;
    }
    return 0;
}

int main()
{
    int i,j,k,changed;
    char p[100],start;

    printf("enter no.of productions\n");
    scanf("%d",&n);

    printf("enterprod\n");
    for (i=0;i<n;i++)
    {
        scanf("%199s",p);

        lhs[i]=p[0];
        for (j=2;p[j]!='\0';j++)
        {
            rhs[i][j-2]=p[j];
        }
        rhs[i][j-2]='\0';

    }
}
