#include "main.h"

/**
 * addNode - Adds a new node to the start of the linked list.
 * @head: Address of the pointer to the head node.
 * @str: The string to be stored in the node.
 * @num: Node index used by history.
 *
 * Return: A pointer to the newly created node.
 */
list_t *addNode(list_t **head, const char *str, int number)
{
    list_t *newNode;

    if (!head)
        return (NULL);

    newNode = malloc(sizeof(list_t));
    if (!newNode)
        return (NULL);

    memorySet((void *)newNode, 0, sizeof(list_t));
    newNode->num = number;

    if (str)
    {
        newNode->str = stringDuplicate(str);
        if (!newNode->str)
        {
            free(newNode);
            return (NULL);
        }
    }

    newNode->next = *head;
    *head = newNode;

    return (newNode);
}

/**
 * addNodeEnd - Adds a new node to the end of the linked list.
 * @head: Address of the pointer to the head node.
 * @str: The string to be stored in the node.
 * @num: Node index used by history.
 *
 * Return: A pointer to the newly created node.
 */
list_t *addNodeEnd(list_t **head, const char *str, int number)
{
    list_t *newNode, *lastNode;

    if (!head)
        return (NULL);

    lastNode = *head;
    newNode = malloc(sizeof(list_t));
    if (!newNode)
        return (NULL);

    memorySet((void *)newNode, 0, sizeof(list_t));
    newNode->number = number;

    if (str)
    {
        newNode->str = stringDuplicate(str);
        if (!newNode->str)
        {
            free(newNode);
            return (NULL);
        }
    }

    if (lastNode)
    {
        while (lastNode->next)
            lastNode = lastNode->next;
        lastNode->next = newNode;
    }
    else
    {
        *head = newNode;
    }

    return (newNode);
}

/**
 * printListStrings - Prints only the 'str' element of a list_t linked list.
 * @head: Pointer to the first node.
 *
 * Return: The number of nodes in the list.
 */
size_t printListStrings(const list_t *head)
{
    size_t count = 0;

    while (head)
    {
        printString(head->str ? head->str : "(nil)");
        printString("\n");
        head = head->next;
        count++;
    }

    return count;
}

/**
 * deleteNodeAtIndex - Deletes a node at the specified index.
 * @head: Address of the pointer to the first node.
 * @index: The index of the node to delete.
 *
 * Return: 1 on success, 0 on failure.
 */
int deleteNodeAtIndex(list_t **head, unsigned int index)
{
    list_t *newNode, *prevNode;
    unsigned int i = 0;

    if (!head || !*head)
        return (0);

    if (!index)
    {
        newNode = *head;
        *head = (*head)->next;
        free(newNode->str);
        free(newNode);
        return (1);
    }

    newNode = *head;
    while (newNode)
    {
        if (i == index)
        {
            prevNode->next = newNode->next;
            free(newNode->str);
            free(newNode);
            return (1);
        }
        i++;
        prevNode = newNode;
        newNode = newNode->next;
    }

    return (0);
}

/**
 * freeList - Frees all nodes of a list.
 * @head_ptr: Address of the pointer to the head node.
 *
 * Return: void
 */
void freeList(list_t **headPtr)
{
    list_t *currentNode, *nextNode, *head;

    if (!headPtr || !*headPtr)
        return;

    head = *headPtr;
    currentNode = head;

    while (currentNode)
    {
        nextNode = currentNode->next;
        free(currentNode->str);
        free(currentNode);
        currentNode = nextNode;
    }

    *headPtr = (NULL);
}
