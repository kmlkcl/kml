#ifndef KML_AST_H
#define KML_AST_H

#include "smlkr_linked_list.h"

typedef SMLKR_LinkedList LinkedList;

typedef struct AST{void** SyntaxItems; int* EOFToken;} AST;
typedef struct AST_Type_Real{int bitToken; int size;} AST_Type_Real;
typedef struct AST_Expression_Alias{AST_Type_Real* realType; const char* alias;} AST_Expression_Alias;

bool Parser(LinkedList * tokens);

#endif //KML_AST_H
