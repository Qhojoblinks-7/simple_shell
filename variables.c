#include "main.h"

/**
 * isChainDelimiter - Checks if the current character in the buffer is a command chain delimiter
 * @info: The parameter struct
 * @buffer: The character buffer
 * @position: Address of the current position in the buffer
 *
 * Return: 1 if it's a command chain delimiter, 0 otherwise
 */
int isChainDelimiter(info_t *info, char *buffer, size_t *position) {
    size_t j = *position;

    if (buffer[j] == '|' && buffer[j + 1] == '|') {
        buffer[j] = 0;
        j++;
        info->commandChainType = CMD_OR;
    } else if (buffer[j] == '&' && buffer[j + 1] == '&') {
        buffer[j] = 0;
        j++;
        info->commandChainType = CMD_AND;
    } else if (buffer[j] == ';') {
        buffer[j] = 0;
        info->commandChainType = CMD_CHAIN;
    } else {
        return 0;
    }

    *position = j;
    return 1;
}

/**
 * checkChainStatus - Checks if we should continue chaining based on the last command's status
 * @info: The parameter struct
 * @buffer: The character buffer
 * @position: Address of the current position in the buffer
 * @startPosition: Starting position in the buffer
 * @bufferLength: Length of the buffer
 *
 * Return: Void
 */
void checkChainStatus(info_t *info, char *buffer, size_t *position, size_t startPosition, size_t bufferLength) {
    size_t j = *position;

    if (info->commandChainType == CMD_AND) {
        if (info->status) {
            buffer[startPosition] = 0;
            j = bufferLength;
        }
    }

    if (info->commandChainType == CMD_OR) {
        if (!info->status) {
            buffer[startPosition] = 0;
            j = bufferLength;
        }
    }

    *position = j;
}

/**
 * replaceAliases - Replaces aliases in the tokenized string
 * @info: The parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceAliases(info_t *info)
{
    int i;
    list_t *aliasNode;
    char *aliasValue;

    for (i = 0; i < 10; i++)
    {
        aliasNode = findAliasStartsWith(info->alias, info->arguments[0], '=');
        if (!aliasNode)
        {
            return 0;
        }

        free(info->arguments[0]);
        aliasValue = stringLocateChar(aliasNode->str, '=');
        if (!aliasValue)
        {
            return (0);
        }

        aliasValue = stringDuplicate(aliasValue + 1);
        if (!aliasValue){
            return (0);
        }

        info->arguments[0] = aliasValue;
    }

    return (1);
}

/**
 * replaceVariables - Replaces variables in the tokenized string
 * @info: The parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceVariables(info_t *info)
{
    int i = 0;
    list_t *envNode;

    for (i = 0; info->arguments[i]; i++)
    {
        if (info->arguments[i][0] != '$' || !info->arguments[i][1])
        {
            continue;
        }

        if (!_strcmp(info->arguments[i], "$?"))
        {
            replaceString(&(info->arguments[i]), _strdup(convertNumber(info->status, 10, 0)));
            continue;
        }

        if (!_strcmp(info->arguments[i], "$$"))
        {
            replaceString(&(info->arguments[i]), _strdup(convertNumber(getpid(), 10, 0)));
            continue;
        }

        envNode = findEnvStartsWith(info->env, &info->arguments[i][1], '=');
        if (envNode)
        {
            replaceString(&(info->arguments[i]), _strdup(_strchr(envNode->str, '=') + 1));
            continue;
        }

        replaceString(&info->arguments[i], _strdup(""));
    }

    return (0);
}

/**
 * replaceString - Replaces a string with a new one
 * @oldString: Address of the old string
 * @newString: New string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceString(char **oldString, char *newString)
{
    free(*oldString);
    *oldString = newString;
    return (1);
}
