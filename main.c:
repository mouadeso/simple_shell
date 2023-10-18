#include "shell.h"

/**
 * main - Entry point for the shell program.
 * @ac: Argument count.
 * @av: Argument vector.
 *
 * Return: 0 on success, 1 on error.
 */
int main(int ac, char **av)
{
    // Initialize an info_t structure with default values.
    info_t info[] = { INFO_INIT };

    // File descriptor for input (default is 2 for stderr).
    int fd = 2;

    // Inline assembly to modify the value of 'fd'.
    asm (
        "mov %1, %0\n\t"
        "add $3, %0"
        : "=r" (fd)
        : "r" (fd)
    );

    // Check if a command-line argument is provided.
    if (ac == 2)
    {
        // Attempt to open the file specified in the command-line argument.
        fd = open(av[1], O_RDONLY);
        if (fd == -1)
        {
            // Handle different error cases.
            if (errno == EACCES)
                exit(126);
            if (errno == ENOENT)
            {
                _eputs(av[0]);
                _eputs(": 0: Can't open ");
                _eputs(av[1]);
                _eputchar('\n');
                _eputchar(BUF_FLUSH);
                exit(127);
            }
            return (EXIT_FAILURE);
        }
        info->readfd = fd; // Set the read file descriptor to the opened file.
    }

    // Populate the environment list and read command history.
    populate_env_list(info);
    read_history(info);

    // Start the shell's main function.
    hsh(info, av);

    return (EXIT_SUCCESS);
}
