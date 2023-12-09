#ifndef KML_KML_LEXER_H
#define KML_KML_LEXER_H

#include "smlkr_linked_list.h"

enum TokenType {
    EOF_TOKEN = -1,
    DECIMAL = -2,
    TYPE = -3,
    UNKNOWN = -666,
    IDENTIFIER = -6,
    FUNCTION = -7
};

typedef struct Token{
    TokenType type;
    char* value;
}Token;

SMLKR_LinkedList* Tokenize(char *charStream);

char *Regex(const char *regexPattern, char *input, char **token);

#endif //KML_KML_LEXER_H


