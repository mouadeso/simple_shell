#include "shell.h"

/**
 * string_to_integer_with_error - converts a string to an integer with error handling
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int string_to_integer_with_error(char *s)
{
    int i = 0;
    unsigned long int result = 0;

    if (*s == '+')
        s++;
    for (i = 0; s[i] != '\0'; i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            result *= 10;
            result += (s[i] - '0');
            if (result > INT_MAX)
                return (-1);
        }
        else
            return (-1);
    }
    return (result);
}

/**
 * print_custom_error - prints a custom error message
 * @info: the parameter & return info struct
 * @custom_error_str: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_custom_error(info_t *info, char *custom_error_str)
{
    write_error_string(info->fname);
    write_error_string(": ");
    print_integer(info->line_count, STDERR_FILENO);
    write_error_string(": ");
    write_error_string(info->argv[0]);
    write_error_string(": ");
    write_error_string(custom_error_str);
}

/**
 * print_integer - function prints an integer
 * @input: the input
 * @fd: the file descriptor to write to
 * Return: number of characters printed
 */
int print_integer(int input, int fd)
{
    int (*write_char)(char) = write_char_to_fd;
    int i, count = 0;
    unsigned int absolute, current;

    if (fd == STDERR_FILENO)
        write_char = write_error_char;
    if (input < 0)
    {
        absolute = -input;
        write_char('-');
        count++;
    }
    else
        absolute = input;
    current = absolute;
    for (i = 1000000000; i > 1; i /= 10)
    {
        if (absolute / i)
        {
            write_char('0' + current / i);
            count++;
        }
        current %= i;
    }
    write_char('0' + current);
    count++;

    return count;
}

/**
 * convert_integer_to_string - converter function for integers
 * @num: number
 * @base: base
 * @flags: argument flags
 * Return: string
 */
char *convert_integer_to_string(long int num, int base, int flags)
{
    static char *array;
    static char buffer[50];
    char sign = 0;
    char *ptr;
    unsigned long n = num;

    if (!(flags & CONVERT_UNSIGNED) && num < 0)
    {
        n = -num;
        sign = '-';
    }
    array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
    ptr = &buffer[49];
    *ptr = '\0';

    do {
        *--ptr = array[n % base];
        n /= base;
    } while (n != 0);

    if (sign)
        *--ptr = sign;
    return ptr;
}

/**
 * remove_comments_in_place - replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 * Return: Always 0;
 */
void remove_comments_in_place(char *buf)
{
    int i;

    for (i = 0; buf[i] != '\0'; i++)
        if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
        {
            buf[i] = '\0';
            break;
        }
}

