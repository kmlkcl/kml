#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "ast.h"
#include "lexer/kml_lexer.h"

AST *Tree;

typedef SMLKR_Node_Linked Node;

/**
 *
 * @param tokenList
 * @return -1 when rule is broken, 0 when still have a chance, specific rule number, when success
 */
typedef int (*Rule)(LinkedList *tokenList);

#define RULE_TypeAlias 1

int Rule_TypeAlias(LinkedList *tokenList);

bool EvaluateRules(LinkedList *ruleSet, LinkedList *tokens);

bool Parser(LinkedList *tokens) {

    Tree = (AST *) malloc(sizeof(AST));

    Node *current = tokens->Head;

    LinkedList *ruleSet = SMLKR_LinkedList_Init();
    LinkedList *tokenPool = SMLKR_LinkedList_Init();

    while (current->Next != NULL) {
        Token *token = (Token *) current->Node;
        SMLKR_LinkedList_AddNode_Tail(tokenPool, token);

        if (token->type == TokenType::TYPE) {
            Rule typeAliasExpressionRule = Rule_TypeAlias;
            SMLKR_LinkedList_AddNode_Tail(ruleSet, &typeAliasExpressionRule);
        }

        EvaluateRules(ruleSet, tokenPool);
        current = current->Next;
    }
    return true;
}

bool EvaluateRules(LinkedList *ruleSet, LinkedList *tokens) {

    int foundRule = 0;

    for (int i = 0; i < ruleSet->Size; i++) {
        Rule rule = *(Rule *) (SMLKR_LinkedList_Get(ruleSet, i)->Node);

        int ruleResult = rule(tokens);

        if (ruleResult == -1) {
            SMLKR_LinkedList_DestroyAt(ruleSet, i);
            i--;
            continue;
        }

        if (ruleResult > 0) {
            if (foundRule != 0) {
                printf("Ambiguity! More than one rule is appliable.");
                return false;
            } else {
                foundRule = ruleResult;
            }
        }
    }

    switch (foundRule) {
        case 0:
            break;
        case RULE_TypeAlias:
            AST_Type_Real *realType = (AST_Type_Real *) malloc(sizeof(AST_Type_Real));
            AST_Expression_Alias *e = (AST_Expression_Alias *) malloc(sizeof(AST_Expression_Alias));


            Token *token = (Token *) (SMLKR_LinkedList_Get(tokens, 2)->Node);
            realType->size = (unsigned char)*token->value;
            realType->bitToken = int(TokenType::TYPE);

            break;
    }

    if (ruleSet->Size == 0)
        return false;
    return true;
}

int Rule_TypeAlias(LinkedList *tokenList) {
    Node *current = tokenList->Head;


    for (int i = 0; i < tokenList->Size; i++) {
        Token *t = (Token *) current->Node;

        if (
                (i == 0 && t->type != TokenType::TYPE) ||
                (i == 1 && strcmp(&*t->value, "_") != 0) ||
                (i == 2 && t->type != TokenType::NUMERIC) ||
                (i == 3 && strcmp(&*t->value, "=") != 0) ||
                (i == 4 && strcmp(&*t->value, ">") != 0) ||
                (i == 5 && t->type != TokenType::IDENTIFIER))
        {
            return -1;
        }
        else if (i == 6) {
            if (strcmp(&*t->value, ";") == 0) {
                return RULE_TypeAlias;
            } else {
                return -1;
            }
        }

        current = current->Next;
    }

    return 0;
}
