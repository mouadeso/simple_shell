#include "shell.h"

/**
 * display_history - displays the command history with line numbers
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int display_history(info_t *info)
{
    print_command_history(info->history);
    return (0);
}

/**
 * remove_alias - removes an alias from the list
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int remove_alias(info_t *info, char *str)
{
    char *p, c;
    int ret;

    p = _strchr(str, '=');
    if (!p)
        return (1);
    c = *p;
    *p = 0;
    ret = delete_alias_node(&(info->alias), get_alias_node_index(info->alias, alias_starts_with(info->alias, str, -1)));
    *p = c;
    return (ret);
}

/**
 * add_alias - adds an alias to the list
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int add_alias(info_t *info, char *str)
{
    char *p;

    p = _strchr(str, '=');
    if (!p)
        return (1);
    if (!*++p)
        return (remove_alias(info, str));

    remove_alias(info, str);
    return (append_alias_node(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias_entry - prints an alias entry
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias_entry(list_t *node)
{
    char *p = NULL, *a = NULL;

    if (node)
    {
        p = _strchr(node->str, '=');
        for (a = node->str; a <= p; a++)
            _putchar(*a);
        _putchar('\'');
        _puts(p + 1);
        _puts("'\n");
        return (0);
    }
    return (1);
}

/**
 * alias_command - manages aliases, mimicking the alias built-in
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int alias_command(info_t *info)
{
    int i = 0;
    char *p = NULL;
    list_t *node = NULL;

    if (info->argc == 1)
    {
        node = info->alias;
        while (node)
        {
            print_alias_entry(node);
            node = node->next;
        }
        return (0);
    }
    for (i = 1; info->argv[i]; i++)
    {
        p = _strchr(info->argv[i], '=');
        if (p)
            add_alias(info, info->argv[i]);
        else
            print_alias_entry(alias_starts_with(info->alias, info->argv[i], '='));
    }

    return (0);
}

