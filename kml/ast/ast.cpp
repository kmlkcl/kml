//
// Created by kemal on 09.12.2023.
//

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


int TypeAliasRule(LinkedList *tokenList);

bool EvaluateRules(LinkedList *ruleSet, LinkedList *tokens);

bool Parser(LinkedList *tokens) {

    Tree = (AST *) malloc(sizeof(AST));

    Node *current = tokens->Head;

    LinkedList *ruleSet = SMLKR_LinkedList_Init();
    LinkedList *tokenPool = SMLKR_LinkedList_Init();

    while (current->Next != NULL) {
        Token *token = (Token *) current->Node;
        SMLKR_LinkedList_AddNode_Tail(tokenPool, token);

        Rule r = TypeAliasRule;

        if (token->type == TokenType::TYPE) {
            SMLKR_LinkedList_AddNode_Tail(ruleSet, &r);
        }

        EvaluateRules(ruleSet, tokenPool);

        current = current->Next;
    }
    return true;
}

bool EvaluateRules(LinkedList *ruleSet, LinkedList *tokens) {

    int appliableRule = 0;

    for (int i = 0; i < ruleSet->Size; i++) {
        Node *n = SMLKR_LinkedList_Get(ruleSet, i);
        Rule rule = *(Rule *) n->Node;

        int ruleResult = rule(tokens);

        if (ruleResult == -1) {
            SMLKR_LinkedList_DestroyAt(ruleSet, i);
            i--;
            continue;
        }

        if (ruleResult > 0) {
            if (appliableRule != 0) {
                printf("Ambiguity! More than one rule is appliable.");
                return false;
            } else {
                appliableRule = ruleResult;
            }
        }
    }

    switch (appliableRule) {
        case 0:
            break;
        case 1: //Alias Expression Rule
            AST_Type_Real *realType = (AST_Type_Real *) malloc(sizeof(AST_Type_Real));
            AST_Expression_Alias *e = (AST_Expression_Alias *) malloc(sizeof(AST_Expression_Alias));
            Token *token = (Token *) SMLKR_LinkedList_Get(tokens, 2);
            realType->size = *token->value;
            realType->bitToken = 1213;
            break;
    }

    if (ruleSet->Size == 0)
        return false;
    return true;
}

int TypeAliasRule(LinkedList *tokenList) {
    Node *current = tokenList->Head;


    for (int i = 0; i < tokenList->Size; i++) {
        Token *t = (Token *) current->Node;

        switch (i) {
            case 0: {
                if (t->type != TokenType::TYPE) {
                    return -1;
                }
            }
                break;

            case 1: {
                if (strcmp(&*t->value,"_")!=0) {
                    return -1;
                }
            }
                break;

            case 2: {
                if (t->type != TokenType::NUMERIC) {
                    return -1;
                }
            }
                break;

            case 3: {
                if (strcmp(&*t->value,"=")!=0) {
                    return -1;
                }
            }
                break;

            case 4 : {
                if (strcmp(&*t->value,">")!=0) {
                    return -1;
                }
            }
                break;

            case 5: {
                if (t->type != TokenType::IDENTIFIER) {
                    return -1;
                }
            }
                break;

            case 6: {
                if (*t->value != ';')  {
                    return -1;
                } else {
                    return 1;
                }
            }
                break;

        }

        current = current->Next;
    }

    return 0;
}
