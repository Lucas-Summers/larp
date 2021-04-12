#ifndef LARP_READER_H
#define LARP_READER_H

#include "lexer.h"

typedef struct READER {
    int toknum;
    int i;
    token_t *tokens[];
} reader_t;

reader_t *reader_init(int maxtoks);
reader_t *lexer_tokenize(lexer_t *lexer);
token_t *reader_peek(reader_t *reader);
token_t *reader_next(reader_t *reader);

#endif
