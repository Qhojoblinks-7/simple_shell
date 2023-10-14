#include "main.h"

/**
 * listLength - Determines the length of a linked list.
 * @head: Pointer to the first node.
 *
 * Return: Size of the list.
 */
size_t listLength(const list_t *head)
{
    size_t nodeIndex = 0;

    while (head)
    {
        head = head->next;
        nodeIndex++;
    }

    return (nodeIndex);
}

/**
 * listToStrings - Converts a linked list of strings to an array of strings.
 * @head: Pointer to the first node.
 *
 * Return: Array of strings.
 */
char **listToStrings(list_t *headNode)
{
    list_t *newNode = headNode;
    size_t i = listLength(headNode), j;
    char **strs;
    char *str;

    if (!headNode || !i)
    {
        return NULL;
    }

    strs = malloc(sizeof(char *) * (i + 1));
    if (!strs)
    {
        return (NULL);
    }

    for (i = 0; newNode; newNode = newNode->next, i++)
    {
        str = malloc(stringLength(newNode->str) + 1);
        if (!str)
        {
            for (j = 0; j < i; j++)
            {
                free(strs[j]);
            }
            free(strs);
            return (NULL);
        }
        str = stringCopy(str, newNode->str);
        strs[i] = str;
    }

    strs[i] = NULL;
    return (strs);
}

/**
 * printList - Prints all elements of a list_t linked list.
 * @head: Pointer to the first node.
 *
 * Return: Size of the list.
 */
size_t printList(const list_t *head)
{
    size_t i = 0;

    while (head)
    {
        printString(convertNumberToString(head->num, 10, 0));
        printCharacter(':');
        printCharacter(' ');
        if (head->str)
        {
            printString(head->str);
        }
        else
        {
            printString("(nil)");
        }
        printString("\n");
        head = head->next;
        i++;
    }

    return (i);
}

/**
 * nodeStartsWith - Finds the node whose string starts with a prefix.
 * @node: Pointer to the list head.
 * @prefix: String to match.
 * @c: The next character after the prefix to match.
 *
 * Return: The matching node or NULL.
 */
list_t *nodeStartsWith(list_t *currentNode, char *prefix, char c)
{
    char *ptr = NULL;

    while (currentNode)
    {
        ptr = startsWith(currentNode->str, prefix);
        if (ptr && ((c == -1) || (*ptr == c)))
        {
            return (currentNode);
        }
        currentNode = currentNode->next;
    }

    return (NULL);
}

/**
 * getNodeIndex - Gets the index of a node in a linked list.
 * @head: Pointer to the list head.
 * @node: Pointer to the node.
 *
 * Return: The index of the node or -1 if not found.
 */
ssize_t getNodeIndex(list_t *headNode, list_t *newNode)
{
    size_t i = 0;

    while (headNode)
    {
        if (headNode == newNode)
        {
            return (i);
        }
        headNode = headNode->next;
        i++;
    }

    return (-1);
}
