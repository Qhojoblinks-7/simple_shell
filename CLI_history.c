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
    for (currentNode = info->history; currentNode; currentNode = currentNode->next)
    {
        printStringToFileDescriptor(currentNode->str, fd);
        charToFileDescriptor('\n', fd);
    }
    charToFileDescriptor(BUF_FLUSH, fd);
    close(fd);
    return (1);
}

/**
 * readHistory - Reads command history from a file
 * @info: The parameter struct
 *
 * Return: The new histcounter on success, 0 on failure
 */
int readHistory(info_t *info)
{
    int index, last = 0, lineCount = 0;
    ssize_t fd, readLen, fileSize = 0;
    struct stat state;
    char *buffer = NULL, *filename = getHistoryFile(info);

    if (!filename)
        return (0);

    fd = open(filename, O_RDONLY);
    free(filename);
    if (fd == -1)
        return (0);
    if (!fstat(fd, &state))
        fileSize = state.st_size;
    if (fileSize < 2)
        return (0);
    buffer = malloc(sizeof(char) * (fileSize + 1));
    if (!buffer)
        return (0);
    readLen = read(fd, buffer, fileSize);
    buffer[fileSize] = 0;
    if (readLen <= 0)
        return (free(buffer), 0);
    close(fd);
    for (index = 0; index < fileSize; index++)
        if (buffer[index] == '\n')
        {
            buffer[index] = 0;
            buildHistoryList(info, buffer + last, lineCount++);
            last = index + 1;
        }
    if (last != index)
        buildHistoryList(info, buffer + last, lineCount++);
    free(buffer);
    info->histcounter = lineCount;
    while (info->histcounter-- >= HIST_MAX)
        deleteNodeAtIndex(&(info->history), 0);
    renumberHistory(info);
    return (info->histcounter);
}

/**
 * buildHistoryList - Adds an entry to the history linked list
 * @info: The parameter struct
 * @buf: The command buffer
 * @lineCount: The history lineCounter (histcounter)
 *
 * Return: Always 0
 */
int buildHistoryList(info_t *info, char *buf, int lineCount)
{
    list_t *currentNode = NULL;

    if (info->history)
        currentNode = info->history;
    addNodeEnd(&currentNode, buf, lineCount);

    if (!info->history)
        info->history = currentNode;
    return (0);
}

/**
 * renumberHistory - Renumbers the history linked list after changes
 * @info: The parameter struct
 *
 * Return: The new histcounter
 */
int renumberHistory(info_t *info)
{
    list_t *currentNode = info->history;
    int newLineCount = 0;

    while (currentNode)
    {
        currentNode->number = newLineCount++;
        currentNode = currentNode->next;
    }
    return (info->histcounter = newLineCount);
}
