#include "shell.h"

/**
 * is_valid_command - checks if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if it's a valid command, 0 otherwise
 */
int is_valid_command(info_t *info, char *path)
{
    struct stat st;

    (void)info;
    if (!path || stat(path, &st))
        return 0;

    if (st.st_mode & S_IFREG)
    {
        return 1;
    }
    return 0;
}

/**
 * duplicate_substring - duplicates characters from a string
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to a new buffer
 */
char *duplicate_substring(char *pathstr, int start, int stop)
{
    static char buf[1024];
    int i = 0, k = 0;

    for (k = 0, i = start; i < stop; i++)
        if (pathstr[i] != ':')
            buf[k++] = pathstr[i];
    buf[k] = 0;
    return buf;
}

/**
 * find_valid_command_path - finds a valid command in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the command to find
 *
 * Return: full path of the command if found or NULL
 */
char *find_valid_command_path(info_t *info, char *pathstr, char *cmd)
{
    int i = 0, curr_pos = 0;
    char *path;

    if (!pathstr)
        return NULL;
    if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
    {
        if (is_valid_command(info, cmd))
            return cmd;
    }
    while (1)
    {
        if (!pathstr[i] || pathstr[i] == ':')
        {
            path = duplicate_substring(pathstr, curr_pos, i);
            if (!*path)
                _strcat(path, cmd);
            else
            {
                _strcat(path, "/");
                _strcat(path, cmd);
            }
            if (is_valid_command(info, path))
                return path;
            if (!pathstr[i])
                break;
            curr_pos = i;
        }
        i++;
    }
    return NULL;
}

