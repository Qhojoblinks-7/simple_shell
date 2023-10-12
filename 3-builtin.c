#include "main.h"

/**
 * displayHistory -Displays the command history, one command per line, 
 * with line numbers
 * starting at 0.
 *
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int displayHistory(info_t *info) {
    /*Call a function (print_list) to display the history list*/
    print_list(info->history);

    return (0);
}

/**
 * unsetAlias - Removes an alias from the list of aliases.
 *
 * @info: The parameter struct.
 * @str: The string alias to unset.
 * Return: 0 on success, 1 on error.
 */
int unsetAlias(info_t *info, char *str)
{
    char *equal_sign_pos;
    char saved_char;
    int result;

    equal_sign_pos = _strchr(str, '=');

    if (equal_sign_pos == NULL) {
        /*Error: '=' not found in the alias string*/
        return (1);
    }

    saved_char = *equal_sign_pos;
    *equal_sign_pos = '\0';

    result = delete_node_at_index(&(info->alias),
        get_node_index(info->alias, node_starts_with(info->alias, str, -1)));

    *equal_sign_pos = saved_char;

    return (result);
}

/**
 * setAlias - Sets an alias to a string.
 *
 * @info: The parameter struct.
 * @str: The string alias to set.
 * Return: 0 on success, 1 on error.
 */
int setAlias(info_t *info, char *str) {
    char *equal_sign_pos;

    equal_sign_pos = _strchr(str, '=');

    if (!equal_sign_pos)
    {
        /*Error: '=' not found in the alias string*/
        return (1);
    }

    if (*++equal_sign_pos == '\0')
    {
        /*Error: Value for the alias is empty; unset the alias instead*/
        return (unset_alias(info, str));
    }

    /*Unset the existing alias and add the new alias to the end of the list*/
    unset_alias(info, str);
    return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * int printAlias - Prints an alias stored in a list node.
 *
 * @node: The list node containing the alias.
 * Return: 0 on success, 1 if the node is NULL.
 */
int printAlias(list_t *node)
{
    if (node)
    {
        char *equal_sign_pos = _strchr(node->str, '=');
        char *alias_name = node->str;
        char *alias_value = equal_sign_pos + 1;

        while (alias_name <= equal_sign_pos)
        {
            _putchar(*alias_name);
            alias_name++;
        }

        _putchar('\'');
        _puts(alias_value);
        _puts("'\n");

        return (0);
    }
    
    return (1);  /*Error: The node is NULL.*/
}

/**
 * manageAliases - Manages aliases in the shell, allowing users to set and print aliases.
 *
 * @param info The parameter struct.
 * @return Always 0.
 */
int manageAliases(info_t *info)
{
    int i = 0;
    char *equal_sign_pos = NULL;
    list_t *node = NULL;

    if (info->argc == 1)
    {
        /*If no arguments, print all aliases*/
        node = info->alias;
        while (node)
        {
            print_alias(node);
            node = node->next;
        }
        return (0);
    }

    /*Process alias-related commands*/
    for (i = 1; info->argv[i]; i++)
    {
        equal_sign_pos = _strchr(info->argv[i], '=');
        if (equal_sign_pos)
        {
            /*Set alias if '=' is found*/
            set_alias(info, info->argv[i]);
        }
        else
        {
            /*Print alias if no '=' is found*/
            print_alias(node_starts_with(info->alias, info->argv[i], '='));
        }
    }

    return (0);
}