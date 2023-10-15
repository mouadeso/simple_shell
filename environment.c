#include "shell.h"

/**
 * getEnvironment - returns the string array copy of our environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **getEnvironment(info_t *info)
{
    if (!info->environ || info->envChanged)
    {
        info->environ = listToStrings(info->env);
        info->envChanged = 0;
    }

    return (info->environ);
}

/**
 * unsetEnvironmentVariable - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @variable: the string env variable property
 */
int unsetEnvironmentVariable(info_t *info, char *variable)
{
    list_t *node = info->env;
    size_t i = 0;
    char *p;

    if (!node || !variable)
        return 0;

    while (node)
    {
        p = startsWith(node->str, variable);
        if (p && *p == '=')
        {
            info->envChanged = deleteNodeAtIndex(&(info->env), i);
            i = 0;
            node = info->env;
            continue;
        }
        node = node->next;
        i++;
    }
    return info->envChanged;
}

/**
 * setEnvironmentVariable - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @variable: the string env variable property
 * @value: the string env variable value
 *  Return: Always 0
 */
int setEnvironmentVariable(info_t *info, char *variable, char *value)
{
    char *buf = NULL;
    list_t *node;
    char *p;

    if (!variable || !value)
        return 0;

    buf = malloc(_strlen(variable) + _strlen(value) + 2);
    if (!buf)
        return 1;
    _strcpy(buf, variable);
    _strcat(buf, "=");
    _strcat(buf, value);
    node = info->env;
    while (node)
    {
        p = startsWith(node->str, variable);
        if (p && *p == '=')
        {
            free(node->str);
            node->str = buf;
            info->envChanged = 1;
            return 0;
        }
        node = node->next;
    }
    addNodeEnd(&(info->env), buf, 0);
    free(buf);
    info->envChanged = 1;
    return 0;
}

