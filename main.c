#include "main.h"

int main(int argc, char **arguments)
{
    /*Initialize the info structure.*/
    info_t info[] = { INFO_INIT };

    int read_fd = 2;  /*Default to stderr.*/

    if (argc == 2)
    {
        read_fd = open(arguments[1], O_RDONLY);
        if (read_fd == -1)
        {
            if (errno == EACCES)
            {
                /*Permission denied.*/
                exit(126);
            }
            else if (errno == ENOENT)
            {
                printString(arguments[0]);
                printString(": 0: sorry! Node allowed");
                printString(arguments[1]);
                writeCharacterToStdErr('\n');
                writeCharacterToStdErr(BUF_FLUSH);
                exit(127);  /*Command not found.*/
            }
            /*Handle other errors if needed.*/
            perror("open");
            return EXIT_FAILURE;
        }
        info->readfd = read_fd;
    }

    /*Populate the environment list.*/
    populateEnvironmentList(info);

    /*Read command history from a file.*/
    read_history(info);

    /*Call the shell function (e.g., mainShellLoop).*/
    mainShellLoop(info, arguments);

    return EXIT_SUCCESS;
}
