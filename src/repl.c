#include "include/repl.h"

reader_t *repl_read(FILE *fp)
{
    char line[BUFSIZE];

    if (fgets(line, BUFSIZE, fp) == NULL)
    {
        fclose(fp);
        return NULL;
    }
    *strchr(line, '\n') = '\0';

    lexer_t *lexer = lexer_init(line);
    reader_t *reader = lexer_tokenize(lexer);
    free(lexer);
    return reader;
}

void repl_print(reader_t *reader)
{
    for (int i = 0; i < reader->toknum; i++)
        printf("<VAL: '%s', TYPE: %d>\n", reader->tokens[i]->value, reader->tokens[i]->type);
}

reader_t *repl_eval(reader_t *reader)
{
    return reader;
}
