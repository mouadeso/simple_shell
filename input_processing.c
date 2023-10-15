#include "shell.h"

/**
 * bufferChainedCommands - buffers chained commands
 * @info: parameter struct
 * @buffer: address of buffer
 * @bufferLength: address of buffer length variable
 *
 * Return: bytes read
 */
ssize_t bufferChainedCommands(info_t *info, char **buffer, size_t *bufferLength)
{
    ssize_t bytesRead = 0;
    size_t lengthProcessed = 0;

    if (!*bufferLength)
    {
        free(*buffer);
        *buffer = NULL;
        signal(SIGINT, interruptSignalHandler);
#if USE_GETLINE
        bytesRead = getline(buffer, &lengthProcessed, stdin);
#else
        bytesRead = customGetLine(info, buffer, &lengthProcessed);
#endif
        if (bytesRead > 0)
        {
            if ((*buffer)[bytesRead - 1] == '\n')
            {
                (*buffer)[bytesRead - 1] = '\0';
                bytesRead--;
            }
            info->linecountFlag = 1;
            removeComments(*buffer);
            buildHistoryList(info, *buffer, info->histcount++);
            *bufferLength = bytesRead;
            info->cmdBuffer = buffer;
        }
    }
    return bytesRead;
}

/**
 * getInputLine - gets a line minus the newline character
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t getInputLine(info_t *info)
{
    static char *chainedCommandsBuffer;
    static size_t currentPosition, chainedCommandsBufferLength;
    ssize_t bytesRead = 0;
    char **lineBufferPointer = &(info->arg), *lineStart;

    putchar(BUFFER_FLUSH);
    bytesRead = bufferChainedCommands(info, &chainedCommandsBuffer, &chainedCommandsBufferLength);
    if (bytesRead == -1)
        return -1;

    if (chainedCommandsBufferLength)
    {
        size_t j = currentPosition;
        lineStart = chainedCommandsBuffer + currentPosition;

        checkChainedCommands(info, chainedCommandsBuffer, &j, currentPosition, chainedCommandsBufferLength);

        while (j < chainedCommandsBufferLength)
        {
            if (isChainedCommand(info, chainedCommandsBuffer, &j))
                break;
            j++;
        }

        currentPosition = j + 1;

        if (currentPosition >= chainedCommandsBufferLength)
        {
            currentPosition = chainedCommandsBufferLength = 0;
            info->cmdBufferType = CMD_NORMAL;
        }

        *lineBufferPointer = lineStart;
        return _strlen(lineStart);
    }

    *lineBufferPointer = chainedCommandsBuffer;
    return bytesRead;
}

/**
 * readBuffer - reads data into a buffer
 * @info: parameter struct
 * @buffer: buffer
 * @bytesRead: size
 *
 * Return: r
 */
ssize_t readBuffer(info_t *info, char *buffer, size_t *bytesRead)
{
    ssize_t bytesRead = 0;

    if (*bytesRead)
        return 0;

    bytesRead = read(info->readfd, buffer, READ_BUFFER_SIZE);

    if (bytesRead >= 0)
        *bytesRead = bytesRead;

    return bytesRead;
}

/**
 * customGetLine - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int customGetLine(info_t *info, char **ptr, size_t *length)
{
    static char buffer[READ_BUFFER_SIZE];
    static size_t currentPosition, bufferLength;
    size_t bufferSpace;
    ssize_t bytesRead = 0, charactersProcessed = 0;
    char *linePointer = NULL, *newLinePointer = NULL, *currentCharacter;

    linePointer = *ptr;

    if (linePointer && length)
        charactersProcessed = *length;

    if (currentPosition == bufferLength)
    {
        currentPosition = bufferLength = 0;
    }

    bytesRead = readBuffer(info, buffer, &bufferLength);

    if (bytesRead == -1 || (bytesRead == 0 && bufferLength == 0))
        return -1;

    currentCharacter = _strchr(buffer + currentPosition, '\n');
    bufferSpace = currentCharacter ? 1 + (unsigned int)(currentCharacter - buffer) : bufferLength;

    newLinePointer = _realloc(linePointer, charactersProcessed, linePointer ? charactersProcessed + bufferSpace : bufferSpace + 1);

    if (!newLinePointer)
        return (linePointer ? free(linePointer), -1 : -1);

    if (linePointer)
        _strncat(newLinePointer, buffer + currentPosition, bufferSpace - currentPosition);
    else
        _strncpy(newLinePointer, buffer + currentPosition, bufferSpace - currentPosition + 1);

    charactersProcessed += bufferSpace - currentPosition;
    currentPosition = bufferSpace;

    linePointer = newLinePointer;

    if (length)
        *length = charactersProcessed;

    *ptr = linePointer;
    return charactersProcessed;
}

/**
 * interruptSignalHandler - blocks Ctrl-C
 * @signalNumber: the signal number
 *
 * Return: void
 */
void interruptSignalHandler(__attribute__((unused)) int signalNumber)
{
    _puts("\n");
    _puts("$ ");
    putchar(BUFFER_FLUSH);
}

