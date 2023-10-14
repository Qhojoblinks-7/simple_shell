#include "main.h"

/**
 * getHistoryFile - Gets the path to the history file
 * @info: Parameter struct
 *
 * Return: Allocated string containing the history file path
 */
char *getHistoryFile(info_t *info)
{
    char *homeDir, *historyFile;

    homeDir = getEnvironment(info, "HOME=");
    if (!homeDir)
        return (NULL);
    historyFile = malloc(sizeof(char) * (stringLength(homeDir) + stringLength(HIST_FILE) + 2));
    if (!historyFile)
        return (NULL);
    historyFile[0] = 0;
    stringCopy(historyFile, homeDir);
    stringConcat(historyFile, "/");
    stringConcat(historyFile, HIST_FILE);
    return (historyFile);
}

/**
 * writeHistory - Writes the command history to a file
 * @info: The parameter struct
 *
 * Return: 1 on success, -1 on failure
 */
int writeHistory(info_t *info)
{
    ssize_t fd;
    char *filename = getHistoryFile(info);
    list_t *currentNode = NULL;

    if (!filename)
        return (-1);

    fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
    free(filename);
    if (fd == -1)
        return (-1);
    for (currentNode = info->history; currentNode; node = node->next)
    {
        printStringToFileDescriptor(node->str, fd);
        writeCharToFileDescriptor('\n', fd);
    }
    writeCharToFileDescriptor(BUF_FLUSH, fd);
    close(fd);
    return (1);
}

/**
 * readHistory - Reads command history from a file
 * @info: The parameter struct
 *
 * Return: The new histcount on success, 0 on failure
 */
int readHistory(info_t *info)
{
    int index, last = 0, linecount = 0;
    ssize_t fd, readdlen, fileSize = 0;
    struct stat state;
    char *buffer = NULL, *filename = getHistoryFile(info);

    if (!filename)
        return (0);

    fd = open(filename, O_RDONLY);
    free(filename);
    if (fd == -1)
        return (0);
    if (!fstat(fd, &st))
        fileSize = state.st_size;
    if (fileSize < 2)
        return (0);
    buffer = malloc(sizeof(char) * (fileSize + 1));
    if (!buffer)
        return (0);
    readlen = read(fd, buffer, fileSize);
    buf[fileSize] = 0;
    if (readlen <= 0)
        return (free(buffer), 0);
    close(fd);
    for (index = 0; index < fileSize; index++)
        if (buf[index] == '\n')
        {
            buf[index] = 0;
            buildHistoryList(info, buffer + last, linecount++);
            last = index + 1;
        }
    if (last != i)
        buildHistoryList(info, buffer + last, linecount++);
    free(buffer);
    info->histcount = linecount;
    while (info->histcount-- >= HIST_MAX)
        deleteNodeAtIndex(&(info->history), 0);
    renumberHistory(info);
    return (info->histcount);
}

/**
 * buildHistoryList - Adds an entry to the history linked list
 * @info: The parameter struct
 * @buf: The command buffer
 * @linecount: The history linecount (histcount)
 *
 * Return: Always 0
 */
int buildHistoryList(info_t *info, char *buf, int linecount)
{
    list_t *currentNode = NULL;

    if (info->history)
        currentNode = info->history;
    addNodeEnd(&currentNode, buf, linecount);

    if (!info->history)
        info->history = currentNode;
    return (0);
}

/**
 * renumberHistory - Renumbers the history linked list after changes
 * @info: The parameter struct
 *
 * Return: The new histcount
 */
int renumberHistory(info_t *info)
{
    list_t *currentNode = info->history;
    int newLinecount = 0;

    while (currentNode)
    {
        node->num = newLinecount++;
        currentNode = node->next;
    }
    return (info->histcount = newLinecount);
}
