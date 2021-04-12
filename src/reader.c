#include "include/reader.h"

reader_t *reader_init(int maxtoks)
{
    reader_t *reader = calloc(1, sizeof(reader_t) + sizeof(token_t *[maxtoks]));
    return reader;
}

reader_t *lexer_tokenize(lexer_t *lexer)
{
    reader_t *reader = reader_init(lexer->src_size);
    while(lexer->c != '\0')
    {
        reader->tokens[reader->toknum] = lexer_next_token(lexer);
        reader->toknum++;
    }
    return reader;
}

token_t *reader_peek(reader_t *reader)
{
    return reader->tokens[reader->i];
}

token_t *reader_next(reader_t *reader)
{
    reader->i++;
    return reader_peek(reader);
}
