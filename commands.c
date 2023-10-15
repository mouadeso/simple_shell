#include "shell.h"

/**
 * exit_command - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int exit_command(info_t *info)
{
    int exitcheck;

    if (info->argv[1])  /* If there is an exit argument */
    {
        exitcheck = error_string_to_integer(info->argv[1]);
        if (exitcheck == -1)
        {
            info->status = 2;
            print_custom_error(info, "Illegal number: ");
            _custom_puts(info->argv[1]);
            _custom_putchar('\n');
            return (1);
        }
        info->err_num = error_string_to_integer(info->argv[1]);
        return (-2);
    }
    info->err_num = -1;
    return (-2);
}

/**
 * change_directory_command - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int change_directory_command(info_t *info)
{
    char *s, *dir, buffer[1024];
    int chdir_ret;

    s = get_custom_cwd(buffer, 1024);
    if (!s)
        _custom_puts("TODO: >>getcwd failure emsg here<<\n");
    if (!info->argv[1])
    {
        dir = get_custom_env(info, "HOME=");
        if (!dir)
            chdir_ret = /* TODO: what should this be? */
                custom_chdir((dir = get_custom_env(info, "PWD=")) ? dir : "/");
        else
            chdir_ret = custom_chdir(dir);
    }
    else if (_custom_strcmp(info->argv[1], "-") == 0)
    {
        if (!get_custom_env(info, "OLDPWD="))
        {
            _custom_puts(s);
            _custom_putchar('\n');
            return (1);
        }
        _custom_puts(get_custom_env(info, "OLDPWD=")), _custom_putchar('\n');
        chdir_ret = /* TODO: what should this be? */
            custom_chdir((dir = get_custom_env(info, "OLDPWD=")) ? dir : "/");
    }
    else
        chdir_ret = custom_chdir(info->argv[1]);
    if (chdir_ret == -1)
    {
        print_custom_error(info, "can't cd to ");
        _custom_eputs(info->argv[1]), _custom_eputchar('\n');
    }
    else
    {
        set_custom_env(info, "OLDPWD", get_custom_env(info, "PWD="));
        set_custom_env(info, "PWD", get_custom_cwd(buffer, 1024));
    }
    return (0);
}

/**
 * help_command - shows help information for the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int help_command(info_t *info)
{
    char **arg_array;

    arg_array = info->argv;
    _custom_puts("help call works. Function not yet implemented \n");
    if (0)
        _custom_puts(*arg_array); /* temp att_unused workaround */
    return (0);
}

