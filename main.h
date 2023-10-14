#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for () */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@arguments: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@lineCount: the error count
 *@errorNumber: the error code for exit()s
 *@lineCountFlag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@envChanged: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcounter: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **arguments;
	char *path;
	int argc;
	unsigned int lineCount;
	int errorNumber;
	int lineCountFlag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int envChanged;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory management */
	int commandChainType; /* CMD_type ||, &&, ; */
	int readfd;
	int histcounter;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtinTable;


/* shloop.c */
int mainShellLoop(info_t *info, char **av);
int findBuiltin(info_t *info);
int findBuiltin(info_t *info);
void forkCommand(info_t *info);

/* execution.c */
int isExecutable(info_t *info, char *path);
char *extractSubstring(char *source, int start, int end);
char *findExecutablePath(info_t *info, char *pathString, char *command);

/* loophmainShellLoop.c */
int loopMainShellLoop(char **);

/* handleErrors.c */
void printString(char *str);
int writeCharacterToStdErr(char);
int charToFileDescriptor(char c, int fd);
int printStringToFileDescriptor(char *str, int fd);

/* toem_string.c */
int stringLength(char *);
int stringCompare(char *, char *);
char *stringStartsWith(const char *, const char *);
char *stringConcat(char *, char *);

/* toem_string1.c */
char *stringCopy(char *, char *);
char *stringDuplicate(const char *);
void printString(char *);
int printCharacter(char);

/* strings.c */
char *stringNumCopy(char *dest, const char *src, int n);
char *stringNumConcat(char *dest, const char *src, int n);
char *stringLocateChar(const char *str, char character);

/* toem_tokenizer.c */
char **splitString(char *, char *);
char **splitStringBySingleDelimiter(char *str, char delimiter);
int countWords(char *str, char *delimiters);
int countWordsBySingleDelimiter(char *str, char delimiter);


/*realloc.c */
char *memorySet(char *, char, unsigned int);
void freeStringArray(char **strArr);
void *customRealloc(void *ptr, unsigned int oldSize, unsigned int newSize);

/* toem_memory.c */
int befreed(void **);

/* 1-builtin.c */
int checkIfInteractive(info_t *);
int isDelimiter(char, const char *);
int isAlpha(char);
int stringToInt(const char *);

/* handleErrors1.c */
int convertStringToInteger(char *s);
void printError(info_t *info, char *errorString);
int printDecimal(int input, int fd);
char *convertNumberToString(long int num, int base, int flags);
void removeComments(char *);

/* 2-builtin.c */
int exitShell(info_t *);
int changeDirectory(info_t *);
int displayHelp(info_t *);

/* 3-builtin1.c */
int displayHistory(info_t *);
int manageAliases(info_t *);
int unsetAlias(info_t *info, char *str);
int setAlias(info_t *info, char *str);
int printAlias(list_t *node);

/*getLine.c */
ssize_t getInput(info_t *);
int getlineFromStdin(info_t *, char **, size_t *);
void handleCtrlC(int sig_num);
ssize_t inputBuffer(info_t *info, char **buf, size_t *len);

/* getinfo.c */
void initializeInfoStruct(info_t *info);
void initializeInfoFromCommandLine(info_t *info, char **commandLineArgs);
void freeInfoStructure(info_t *info, int freeAllFields);

/* environment.c */
char *getEnvironment(info_t *, const char *);
int printEnvironment(info_t *info);
int setEnvironment(info_t *info);
int unsetEnvironment(info_t *info);
int populateEnvironmentList(info_t *);

/* getenv.c */
char **getEnviron(info_t *info);
int unsetEnvironmentVariable(info_t *info, char *var);
int setEnvironmentVariable(info_t *info, char *var, char *value);

/* CLI_history.c */
char *getHistoryFile(info_t *info);
int writeHistory(info_t *info);
int readHistory(info_t *info);
int buildHistoryList(info_t *info, char *buf, int linecount);
int renumberHistory(info_t *info);

/* 1-lists.c */
list_t *addNode(list_t **, const char *, int);
list_t *addNodeEnd(list_t **, const char *, int);
size_t printListStrings(const list_t *);
int deleteNodeAtIndex(list_t **, unsigned int);
void freeList(list_t **);

/* 2-lists.c */
size_t listLen(const list_t *);
char **listToStrings(list_t *);
size_t printList(const list_t *);
list_t *nodeStartsWith(list_t *, char *, char);
ssize_t getNodeIndex(list_t *, list_t *);

/* toem_vars.c */
int isChainDelimiter(info_t *, char *, size_t *);
void checkChainStatus(info_t *, char *, size_t *, size_t, size_t);
int replaceAliases(info_t *);
int replaceVariables(info_t *);
int replaceString(char **, char *);

#endif
