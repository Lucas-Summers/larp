#include "include/lexer.h"

lexer_t *lexer_init(char *src)
{
    lexer_t *lexer = calloc(1, sizeof(lexer_t));
    lexer->src = src;
    lexer->c = lexer->src[lexer->i];
    lexer->src_size = strlen(src);
    return lexer;
}

token_t *token_init(char *value, int type)
{
    token_t *token = calloc(1, sizeof(token_t));
    token->value = value;
    token->type = type;
    return token;
}

void lexer_advance(lexer_t *lexer)
{
    if (lexer->c != '\0')
    {
        lexer->i++;
        lexer->c = lexer->src[lexer->i];
    }
}

char *lexer_advance_with(lexer_t *lexer, char *tok, int n)
{
    for(int i = 0; i < n; i++)
        lexer_advance(lexer);
    return tok;
}

int lexer_check_keyword(lexer_t *lexer, char *keyword, int size)
{
    char s[size+1];
    for(int i = 0; i < size; i++)
    {
        s[i] = lexer_peek(lexer, i);
    }
    s[size] = '\0';
    if (strcmp(keyword, s) == 0)
        return 1;
    else
        return 0;
}

char *lexer_parse_until(lexer_t *lexer, char c)
{
    char *tok = calloc(2, sizeof(char));
    tok[0] = lexer->c;
    lexer_advance(lexer);

    while(lexer->c != c && lexer->c != '\0')
    {
        tok = realloc(tok, (strlen(tok) + 2) * sizeof(char));
        strcat(tok, (char[]){lexer->c, 0});
        lexer_advance(lexer);
    }
    tok = realloc(tok, (strlen(tok) + 2) * sizeof(char));
    strcat(tok, (char[]){lexer->c, 0});

    return tok;
}

char lexer_peek(lexer_t *lexer, int offset)
{
    return lexer->src[MIN(lexer->i+offset, lexer->src_size)];
}

char *lexer_parse_id(lexer_t *lexer)
{
    char *tok = calloc(1, sizeof(char));

    while(strchr("[]{}()'`^@~", lexer->c) == NULL && lexer->c != ' ' && lexer->c != '\t' && lexer->c != '\0')
    {
        tok = realloc(tok, (strlen(tok) + 2) * sizeof(char));
        strcat(tok, (char[]){lexer->c, 0});
        lexer_advance(lexer);
    }
    return tok;
}

char *lexer_parse_int(lexer_t *lexer)
{
    char *tok = calloc(1, sizeof(char));
    while(isdigit(lexer->c))
    {
        tok = realloc(tok, (strlen(tok) + 2) * sizeof(char));
        strcat(tok, (char[]){lexer->c, 0});
        lexer_advance(lexer);
    }
    return tok;
}

void lexer_skip_whitespace(lexer_t *lexer)
{
    while(lexer->c == ' ' || lexer->c == '\t')
    {
        lexer_advance(lexer);
    }
}

char *lexer_advance_symbol(lexer_t *lexer)
{
    char *s = calloc(2, sizeof(char));
    s[0] = lexer->c;
    return lexer_advance_with(lexer, s, 1);
}

token_t *lexer_next_token(lexer_t *lexer)
{
    lexer_skip_whitespace(lexer);
    switch(lexer->c)
    {
        case '~': {
            if (lexer_peek(lexer, 1) == '@')
                return token_init(lexer_advance_with(lexer, "~@", 2), TOKEN_TILDEAT);
            return token_init(lexer_advance_symbol(lexer), TOKEN_SPECIAL);
        };
        case ';': return token_init(lexer_advance_with(lexer, lexer_parse_until(lexer, '\0'), 1), TOKEN_COMMENT);
        case '"': return token_init(lexer_advance_with(lexer, lexer_parse_until(lexer, '"'), 1), TOKEN_STRING);
        case 't': {
            if (lexer_check_keyword(lexer, "true", 4))
                return token_init(lexer_advance_with(lexer, "true", 4), TOKEN_BOOL);
        };
        case 'f': {
            if (lexer_check_keyword(lexer, "false", 5))
                return token_init(lexer_advance_with(lexer, "false", 5), TOKEN_BOOL);
        };
        case 'n': {
            if (lexer_check_keyword(lexer, "nil", 3))
                return token_init(lexer_advance_with(lexer, "nil", 3), TOKEN_NIL);
        };
    }

    if (strchr("[]{}()'`^@", lexer->c) != NULL)
        return token_init(lexer_advance_symbol(lexer), TOKEN_SPECIAL);
    else if (isdigit(lexer->c))
        return token_init(lexer_advance_with(lexer, lexer_parse_int(lexer), 1), TOKEN_INT);

    return token_init(lexer_advance_with(lexer, lexer_parse_id(lexer), 1), TOKEN_ID);
}
