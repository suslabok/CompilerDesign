#include <stdio.h>
#include <string.h>

int match(char *text, char *pattern);
int matchChar(char s, char p)
{
    return p == '.' || s == p;
}

int findClosing(char *p, int start)
{
    int d = 0;
    for (int i = start; p[i]; i++)
    {
        if (p[i] == '(')
            d++;
        else if (p[i] == ')' && --d == 0)
            return i;
    }
    return -1;
}

int matchHere(char *text, char *pattern);

int matchStar(char *text, char ch, char *rest)
{
    if (matchHere(text, rest))
        return 1;
    for (int i = 0; text[i] && matchChar(text[i], ch); i++)
        if (matchHere(text + i + 1, rest))
            return 1;
    return 0;
}

int matchHere(char *text, char *pattern)
{
    if (*pattern == '\0')
        return *text == '\0';
    if (pattern[0] == '(')
    {
        int end = findClosing(pattern, 0);
        char group[100], part[100];
        strncpy(group, pattern + 1, end - 1);
        group[end - 1] = '\0';
        for (int i = 0; i <= strlen(text); i++)
        {
            strncpy(part, text, i);
            part[i] = '\0';
            if (match(part, group) &&
                matchHere(text + i, pattern + end + 1))
                return 1;
        }
        return 0;
    }
    if (pattern[1] == '*')
        return matchStar(text, pattern[0], pattern + 2);
    if (*text && matchChar(*text, *pattern))
        return matchHere(text + 1, pattern + 1);
    return 0;
}

int match(char *text, char *pattern)
{
    int depth = 0;
    for (int i = 0; pattern[i]; i++)
    {
        if (pattern[i] == '(')
            depth++;
        else if (pattern[i] == ')')
            depth--;
        else if (pattern[i] == '|' && depth == 0)
        {
            char left[100], right[100];
            strncpy(left, pattern, i);
            left[i] = '\0';
            strcpy(right, pattern + i + 1);
            return match(text, left) || match(text, right);
        }
    }
    return matchHere(text, pattern);
}

int main()
{
    char pattern[100], text[100];
    printf("Enter Pattern: ");
    scanf("%99s", pattern);
    printf("Enter String: ");
    scanf("%99s", text);
    if (match(text, pattern))
        printf("Valid String (Matched)\n");
    else
        printf("Invalid String (Not Matched)\n");
    return 0;
}