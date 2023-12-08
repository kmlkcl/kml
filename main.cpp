#include <cstdio>
#include "smlkr_io.h"
#include "lexer/kml_lexer.h"

int main(){

    char* content = SMLKR_IO_ReadFileContent("example.kml");
    SMLKR_LinkedList* list = Tokenize(content);

    SMLKR_Node_Linked* Current = list->Head;

    while(Current!=NULL){
        Token* t = (Token*)Current->Node;
        printf("Token Value: %s \n",(char*)t->value);
        Current = Current->Next;
    }

    return 0;
}