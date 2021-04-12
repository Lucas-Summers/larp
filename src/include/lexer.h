#ifndef LARP_LEXER_H
#define LARP_LEXER_H

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <sys/param.h>

typedef struct LEXER {
    char *src;
    int src_size;
    char c;
    int i;
} lexer_t;

typedef struct TOKEN {
    char *value;
    enum {
        TOKEN_ID,
        TOKEN_INT,
        TOKEN_BOOL,
        TOKEN_STRING,
        TOKEN_NIL,
        TOKEN_COMMENT,
        TOKEN_SPECIAL,
        TOKEN_TILDEAT
    } type;
} token_t;

lexer_t *lexer_init(char *src);
token_t *token_init(char *value, int type);
token_t *lexer_next_token(lexer_t *lexer);
void lexer_skip_whitespace(lexer_t *lexer);
char lexer_peek(lexer_t *lexer, int offset);
void lexer_advance(lexer_t *lexer);
char *lexer_advance_with(lexer_t *lexer, char *tok, int n);
int lexer_check_keyword(lexer_t *lexer, char *keyword, int size);
char *lexer_parse_until(lexer_t *lexer, char c);
char *lexer_parse_id(lexer_t *lexer);
char *lexer_advance_symbol(lexer_t *lexer);
char *lexer_parse_int(lexer_t *lexer);

#endif
