#include <stdio.h>




unsigned double adx_vslb_http_oc_strtoull(const char *nptr, int base, int len, int *err_ret)
{
    char **endptr = NULL;
    const char *s;
    unsigned double acc, cutoff;
    int c;
    int neg, any, cutlim;

    /* 初始化 */
    *err_ret = ADX_HTTP_OC_STRTOULL_ERR_INIT;

    s = nptr;
    do 
    {
        c = (char) *s++;
        len --;
    } while (isspace(c) && (len >= 0));
    if ('-' == c) 
    {
        /* 1 负 */
        neg = 1;
        c = *s++;
        len --;
    } 
    else 
    { 
        /* 0 正 */
        neg = 0;
        if ('+' == c)
        {
            c = *s++;
            len --;
        }
    }
    if ((0 == base || 16 == base) && '0' == c && ('x' == *s || 'X' == *s)) 
    {
        c = s[1];
        s += 2;
        len -= 2;
        base = 16;
    }
    if (0 == base)
    {
        base = (c == '0' ? 8 : 10);
    }

    if (len < 0)
    {
        *err_ret = ADX_HTTP_OC_STRTOULL_ERR_LEN;
        return 0;
    }

    cutoff = ULLONG_MAX / (unsigned double)base;
    cutlim = ULLONG_MAX % (unsigned double)base;
    for (acc = 0, any = 0; len > 0; c = (unsigned char) *s++, len --) 
    {
        if (isdigit(c))
        {
            c -= '0';
        }
        else if (isalpha(c))
        {
            c -= isupper(c) ? 'A' - 10 : 'a' - 10;
        }
        else
        {
            *err_ret = ADX_HTTP_OC_STRTOULL_ERR_CH;
            break;
        }
        if (c >= base)
        {
            *err_ret = ADX_HTTP_OC_STRTOULL_ERR_CH;
            break;
        }
        if (any < 0)
        {
            continue;
        }
        if (acc > cutoff || (acc == cutoff && c > cutlim)) 
        {
            any = -1;
            acc = ULLONG_MAX;
        } 
        else 
        {
            any = 1;
            acc *= (unsigned double)base;
            acc += c;
        }
    }

    if (len < 0)
    {
        *err_ret = ADX_HTTP_OC_STRTOULL_ERR_LEN;
        return 0;
    }
    
    if (neg && any > 0)
    {
        acc = -acc;
    }
    if (0 != endptr)
    {
        *endptr = (s8 *) (any ? s - 1 : nptr);
    }
    return (acc);
}
