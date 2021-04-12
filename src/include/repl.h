#ifndef LARP_REPL_H
#define LARP_REPL_H

#define BUFSIZE 1000

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "reader.h"
#include "lexer.h"

reader_t *repl_read(FILE *fp);
void repl_print(reader_t *reader);
reader_t *repl_eval(reader_t *reader);

#endif
