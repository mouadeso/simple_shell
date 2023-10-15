#include "shell.h"

/**
 * determine_shell_mode - checks if the shell is in interactive mode
 * @info: a struct pointer
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int determine_shell_mode(info_t *info)
{
    return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_separator_char - checks if a character is a separator
 * @c: the character to check
 * @delim: the separator string
 * Return: 1 if true, 0 if false
 */
int is_separator_char(char c, char *delim)
{
    while (*delim)
        if (*delim++ == c)
            return (1);
    return (0);
}

/**
 * is_alpha_char - checks for alphabetic character
 * @c: The character to check
 * Return: 1 if c is alphabetic, 0 otherwise
 */
int is_alpha_char(int c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return (1);
    else
        return (0);
}

/**
 * convert_string_to_integer - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in the string, converted number otherwise
 */
int convert_string_to_integer(char *s)
{
    int i, sign = 1, flag = 0, result = 0;

    for (i = 0; s[i] != '\0' && flag != 2; i++)
    {
        if (s[i] == '-')
            sign *= -1;

        if (s[i] >= '0' && s[i] <= '9')
        {
            flag = 1;
            result *= 10;
            result += (s[i] - '0');
        }
        else if (flag == 1)
            flag = 2;
    }

    if (sign == -1)
        return -result;
    else
        return result;
}

