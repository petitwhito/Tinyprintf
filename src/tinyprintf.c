#include "tinyprintf.h"

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

char *throw(char *s, const char *base)
{
    s[0] = base[0];
    s[1] = '\0';
    return s;
}

int lenbase(const char *base)
{
    int count = 0;
    for (int i = 0; base[count]; i++)
    {
        count++;
    }
    return count;
}

char *my_itoa_base(int n, char *s, const char *base)
{
    if (n == 0)
    {
        return throw(s, base);
    }
    int i = 0;
    int sign = 0;
    if (n < 0)
    {
        s[0] = '-';
        i++;
        sign = 1;
        n = -n;
    }
    int lbase = lenbase(base);
    while (n != 0)
    {
        int r = n % lbase;
        s[i] = base[r];
        i++;
        n = n / lbase;
    }

    int j = i - 1;
    if (sign)
    {
        for (int k = 1; k <= i / 2; k++)
        {
            char temp = s[k];
            s[k] = s[j];
            s[j] = temp;
            j--;
        }
    }
    else
    {
        for (int k = 0; k < i / 2; k++)
        {
            char temp = s[k];
            s[k] = s[j];
            s[j] = temp;
            j--;
        }
    }
    s[i] = '\0';
    return s;
}

char *my_itoa_base_unsigned(unsigned n, char *s, const char *base)
{
    if (n == 0)
    {
        return throw(s, base);
    }
    int i = 0;
    int sign = 0;
    int lbase = lenbase(base);
    while (n != 0)
    {
        int r = n % lbase;
        s[i] = base[r];
        i++;
        n = n / lbase;
    }

    int j = i - 1;
    if (sign)
    {
        for (int k = 1; k <= i / 2; k++)
        {
            char temp = s[k];
            s[k] = s[j];
            s[j] = temp;
            j--;
        }
    }
    else
    {
        for (int k = 0; k < i / 2; k++)
        {
            char temp = s[k];
            s[k] = s[j];
            s[j] = temp;
            j--;
        }
    }
    s[i] = '\0';
    return s;
}

static int case_d(int res, int count)
{
    char *str = malloc(sizeof(char) * 100000);
    str = my_itoa_base(res, str, "0123456789");
    for (int i = 0; str[i]; i++)
    {
        putchar(str[i]);
        count++;
    }
    free(str);
    return count;
}

static int case_x(int res, int count)
{
    char *str = malloc(sizeof(char) * 100000);
    str = my_itoa_base_unsigned(res, str, "0123456789abcdef");
    for (int i = 0; str[i]; i++)
    {
        putchar(str[i]);
        count++;
    }
    free(str);
    return count;
}

static int case_o(int res, int count)
{
    char *str = malloc(sizeof(char) * 100000);
    str = my_itoa_base_unsigned(res, str, "01234567");
    for (int i = 0; str[i]; i++)
    {
        putchar(str[i]);
        count++;
    }
    free(str);
    return count;
}

static int case_u(int res, int count)
{
    char *str = malloc(sizeof(char) * 100000);
    str = my_itoa_base_unsigned(res, str, "0123456789");
    for (int i = 0; str[i]; i++)
    {
        putchar(str[i]);
        count++;
    }
    free(str);
    return count;
}

static int case_s(char *str, int count)
{
    if (!str)
    {
        putchar('(');
        putchar('n');
        putchar('u');
        putchar('l');
        putchar('l');
        putchar(')');
        count += 6;
        return count;
    }

    for (int i = 0; str[i]; i++)
    {
        putchar(str[i]);
        count++;
    }
    return count;
}

int tinyprintf(const char *format, ...)
{
    if (!format)
        return 0;
    va_list ap;

    int count = 0;
    va_start(ap, format);

    int next = 0;
    for (int i = 0; format[i]; i++)
    {
        if (format[i] == '%' && !next)
        {
            next = 1;
            continue;
        }
        if (!next)
        {
            putchar(format[i]);
            count++;
        }
        else
        {
            next = 0;
            int res;
            char c;
            char *str;
            switch (format[i])
            {
            case 'd':
                res = va_arg(ap, int);
                count = case_d(res, count);
                break;
            case 'x':
                res = va_arg(ap, unsigned);
                count = case_x(res, count);
                break;
            case 'o':
                res = va_arg(ap, unsigned);
                count = case_o(res, count);
                break;
            case 'u':
                res = va_arg(ap, unsigned);
                count = case_u(res, count);
                break;
            case 's':
                str = va_arg(ap, char *);
                count = case_s(str, count);
                break;
            case 'c':
                c = va_arg(ap, int);
                putchar(c);
                count++;
                break;
            default:
                if (format[i - 1] == '%' && format[i] != '%')
                {
                    putchar(format[i - 1]);
                    count++;
                }
                count++;
                putchar(format[i]);
            }
        }
    }

    va_end(ap);
    return count;
}
