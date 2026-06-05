#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_CODE 1000
#define MAX_TOKEN 100

char *keywords[] = {
    "int", "float", "if", "else",
    "while", "for", "return"};

int isKeyword(char *word)
{
    for (int i = 0; i < 7; i++)
    {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int isOperator(char ch)
{
    return strchr("+-*/=<>", ch) != NULL;
}

int isSymbol(char ch)
{
    return strchr(";()", ch) != NULL;
}

void classify(char *token)
{
    int number = 1;

    for (int i = 0; token[i]; i++)
    {
        if (!isdigit(token[i]))
        {
            number = 0;
            break;
        }
    }

    if (isKeyword(token))
        printf("%-15s %-15s\n", token, "KEYWORD");
    else if (number)
        printf("%-15s %-15s\n", token, "NUMBER");
    else
        printf("%-15s %-15s\n", token, "IDENTIFIER");
}

void tokenize(char *code)
{
    char token[MAX_TOKEN];
    int j = 0;
    for (int i = 0;; i++)
    {
        char ch = code[i];
        if (isalnum(ch) || ch == '_')
        {
            token[j++] = ch;
        }
        else
        {
            if (j > 0)
            {
                token[j] = '\0';
                classify(token);
                j = 0;
            }
            if (isOperator(ch))
            {
                char op[2] = {ch, '\0'};
                printf("%-15s %-15s\n", op, "OPERATOR");
            }
            else if (isSymbol(ch))
            {
                char sym[2] = {ch, '\0'};
                printf("%-15s %-15s\n", sym, "SYMBOL");
            }
            if (ch == '\0')
                break;
        }
    }
}

int main()
{
    FILE *fp = fopen("File.txt", "r");
    char code[MAX_CODE];
    int i = 0;
    if (!fp)
    {
        printf("Cannot open File.txt\n");
        return 1;
    }
    while ((code[i] = fgetc(fp)) != EOF && i < MAX_CODE - 1)
        i++;

    code[i] = '\0';
    fclose(fp);
    printf("%-15s %-15s\n", "LEXEME", "TOKEN");
    printf("------------------------------\n");
    tokenize(code);
    return 0;
}