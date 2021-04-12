#include "include/repl.h"

/* NOTE: need to create error_handle */
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("[ERROR] please supply a filename...");
        exit(1);
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("[ERROR] '%s' is not a file", argv[1]);
        exit(1);
    }

    // REPL loop
    while(1)
    {
        reader_t *reader = repl_read(fp);
        if (reader == NULL)
        {
            free(reader);
            exit(0);
        }
        reader = repl_eval(reader);
        repl_print(reader);
        free(reader);
    }
}
