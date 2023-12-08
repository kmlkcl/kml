#ifndef KML_KML_LEXER_H
#define KML_KML_LEXER_H
enum Token{
    EOF                 = -1,
    TYPE                = -3,
    IDENTIFIER          = -6,
    FUNCTION            = -7
};
#endif //KML_KML_LEXER_H


int GetToken(char* charStream);
void __exampleRegex();