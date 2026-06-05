#include <stdio.h>
#include <string.h>
#define MAX 10
typedef struct
{
    char lhs;
    char rhs[MAX][50];
    int count;
} Prod;

void trim(char *s)
{
    int i, start = 0, end = strlen(s) - 1;
    while (s[start] == ' ')
        start++;
    while (end >= start && (s[end] == ' ' || s[end] == '\n' || s[end] == '\r'))
        end--;
    for (i = 0; i <= end - start; i++)
        s[i] = s[start + i];
    s[i] = '\0';
}

void printProd(Prod *p, int prime)
{
    if (prime)
        printf("%c' -> ", p->lhs);
    else
        printf("%c -> ", p->lhs);
    for (int i = 0; i < p->count; i++)
    {
        if (i > 0)
            printf(" | ");
        printf("%s", p->rhs[i]);
    }
    printf("\n");
}

int main()
{
    int n, i, j;
    Prod prods[MAX], t[MAX], pr[MAX];
    char line[256], rhs_copy[256], *arrow, *tok;
    printf("Enter number of non-terminals: ");
    scanf("%d", &n);
    getchar();

    for (i = 0; i < n; i++)
    {
        printf("Enter production %d : ", i + 1);
        fgets(line, sizeof(line), stdin);
        trim(line);
        prods[i].lhs = line[0];
        prods[i].count = 0;
        arrow = strstr(line, "->");
        strcpy(rhs_copy, arrow + 2);
        tok = strtok(rhs_copy, "|");
        while (tok)
        {
            trim(tok);
            if (strlen(tok) > 0)
                strcpy(prods[i].rhs[prods[i].count++], tok);
            tok = strtok(NULL, "|");
        }
    }

    printf("\nOriginal Grammar:\n");
    for (i = 0; i < n; i++)
        printProd(&prods[i], 0);
    for (i = 0; i < n; i++)
    {
        char lhs = prods[i].lhs;
        char alpha[MAX][50], beta[MAX][50];
        int ac = 0, bc = 0;
        char prime[3] = {lhs, '\'', '\0'};

        for (j = 0; j < prods[i].count; j++)
        {
            if (prods[i].rhs[j][0] == lhs)
            {
                strcpy(alpha[ac], prods[i].rhs[j] + 1);
                trim(alpha[ac++]);
            }
            else
            {
                strcpy(beta[bc++], prods[i].rhs[j]);
            }
        }

        t[i].lhs = lhs;
        t[i].count = 0;
        pr[i].lhs = lhs;
        pr[i].count = 0;
        if (ac == 0)
        {
            for (j = 0; j < prods[i].count; j++)
                strcpy(t[i].rhs[t[i].count++], prods[i].rhs[j]);
        }
        else
        {
            for (j = 0; j < bc; j++)
                sprintf(t[i].rhs[t[i].count++], "%s%s", beta[j], prime);
            if (bc == 0)
                sprintf(t[i].rhs[t[i].count++], "e%s", prime);
            for (j = 0; j < ac; j++)
                sprintf(pr[i].rhs[pr[i].count++], "%s%s", alpha[j], prime);
            strcpy(pr[i].rhs[pr[i].count++], "e");
        }
    }
    printf("\nGrammar After Removing Left Recursion:\n");
    for (i = 0; i < n; i++)
    {
        printProd(&t[i], 0);
        if (pr[i].count > 0)
            printProd(&pr[i], 1);
    }
    return 0;
}