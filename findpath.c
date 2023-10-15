#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *findPath(info_t *info, const char *pathVar, const char *command) {
    if (pathVar == NULL || command == NULL) {
        return NULL;
    }
    char *pathCopy = strdup(pathVar);
    if (pathCopy == NULL) {
        perror("Memory allocation failed");
        return NULL;
    }

    char *token = strtok(pathCopy, ":");
    while (token != NULL) {
        char *path = (char *)malloc(strlen(token) + strlen(command) + 2);
        if (path == NULL) {
            perror("Memory allocation failed");
            free(pathCopy);
            return NULL;
        }
        
        sprintf(path, "%s/%s", token, command);
        if (access(path, F_OK) != -1) {
            free(pathCopy);
            return path;
        }

        free(path);
        token = strtok(NULL, ":");
    }

    free(pathCopy);
    return NULL;
}
