#include <stdio.h>
#include <string.h>

int judgement(char *str, int len)
{
    int  i;
    int  sp = -1;
    char stack[100];

    for (i = 0; i < len; i++)
    {
        switch(str[i])
        {
            case '(':
            case '{':
            case '[':
                stack[++sp] = str[i];
                break;
            case ')':
                if (-1 == sp || '(' != stack[sp])
                {
                    printf("index = %d\n", i);
                    return -1;
                }
                sp--;
                break;
            case '}':
                if (-1 == sp || '{' != stack[sp])
                {
                    printf("index = %d\n", i);
                    return -1;
                }
                sp--;
                break;
            case ']':
                if (-1 == sp || '[' != stack[sp])
                {
                    printf("index = %d\n", i);
                    return -1;
                }
                sp--;
                break;
            default:
                break;
        }      
    }
    
    if (-1 != sp)
    {
        return -1;
    }

    return 0;
}

int main(int argc, char **argv)
{
    int  ret;
    int  len;
    char *str = argv[1];
        

    if (1 == argc || NULL == str || 0 == (len = strlen(str)))
    {
        printf("true: para\n");
        return 0;   
    }

    (-1 == (ret = judgement(str, len))) ? printf("false\n") : printf("true\n");

    return 0;
}