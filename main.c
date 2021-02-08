#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define TSS_READ_LINE_BUFSIZE 1024

char *tss_read_line(void)
{
    int bufsize = TSS_READ_LINE_BUFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;

    if (!buffer) {
        fprintf(stderr, "TSS: allocation error\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // Read a character
        c = getchar();

        // If we hit EOF, replace it with a null character and return
        if (c == EOF || c == '\n') {
            buffer[position] = '\0';
            return buffer;
        } else {
            buffer[position] = c;
        }
        position++;

        // If we have exceeded the bugger, reallocate
        if (position >= bufsize) {
            bufsize += TSS_READ_LINE_BUFSIZE;
            buffer = realloc(buffer, bufsize);
            if (!buffer) {
                fprintf(stderr, "TSS: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

void tss_loop(void)
{
    char *line;
    char **args;
    int status;

    do {
        printf("> ");
        line = tss_read_line();
        // args = tss_split_line(line);
        // status = tss_execute(args);

        free(line);
        free(args);
    } while (status);
}

int main(int argc, char **argv)
{
    tss_loop();
}