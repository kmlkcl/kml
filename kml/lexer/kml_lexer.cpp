#include "kml_lexer.h"

#define PCRE2_CODE_UNIT_WIDTH 8

#include <pcre2.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "smlkr_linked_list.h"

typedef SMLKR_LinkedList *LinkedList;

const int char_hashTag = (int) '#';
const int char_a = (int) 'a';
const int char_z = (int) 'z';
const int char_A = (int) 'A';
const int char_Z = (int) 'Z';
const int char_0 = (int) '0';
const int char_9 = (int) '9';


bool isAlpha(int charValue) {
    return (charValue >= char_a && charValue <= char_z) || (charValue >= char_A && charValue <= char_Z);
}

bool isDigit(int charValue) { return (charValue >= char_0 && charValue <= char_9); }
/*
 * EOF_TOKEN = -1,
    DECIMAL = -2,
    TYPE = -3,
    IDENTIFIER = -6,
    FUNCTION = -7
 */
SMLKR_LinkedList *Tokenize(char *charStream) {
    if (charStream == NULL) {
        return  NULL;
    }

    LinkedList l = SMLKR_LinkedList_Init();

    char *currentPosition = charStream;

    while (*currentPosition != '\0') {

        int charValue = (int) (*currentPosition);
        char *nextPosition = NULL;

        Token* token = (Token*) malloc(sizeof (Token));
        token->value = NULL;
        token->type = TokenType::EOF_TOKEN;

        if (charValue == char_hashTag) {
            nextPosition = Regex("#.*?#", currentPosition, &token->value);
            free(token->value);
            free(token);
            currentPosition = nextPosition;
            continue;
        } else if (isAlpha(charValue)) {
            nextPosition = Regex("[a-zA-Z]+", currentPosition, &token->value);

            if(strcmp(token->value,"bit")==0){
                token->type = TokenType::TYPE;
            }else if(strcmp(token->value,"function")==0){
                token->type = TokenType::FUNCTION;
            }else{
                token->type = TokenType::IDENTIFIER;
            }
            currentPosition =  nextPosition;
        } else if (isDigit(charValue)) {
            nextPosition = Regex("[0-9]+", currentPosition, &token->value);
            token->type = TokenType::DECIMAL;
            currentPosition = nextPosition;
        } else if (*currentPosition == ' ' || *currentPosition=='\n' ) {
            free(token->value);
            free(token);
            currentPosition = currentPosition + 1;
            continue;
        } else {
            token->value = (char *) malloc(sizeof(char));
            *token->value = *currentPosition;
            currentPosition = currentPosition+1;
        }


        SMLKR_LinkedList_AddNode_Tail(l, token);

    }

    Token* eofToken = (Token*) malloc(sizeof (Token));
    eofToken->value = NULL;
    eofToken->type = TokenType::EOF_TOKEN;
    SMLKR_LinkedList_AddNode_Tail(l, eofToken);

    return l;
}

char *Regex(const char *regexPattern, char *input, char **token) {
    pcre2_code *pattern;
    int errorCode;
    PCRE2_SIZE errorOffset;

    pattern = pcre2_compile((PCRE2_SPTR8) regexPattern, PCRE2_ZERO_TERMINATED, 0,
                            &errorCode, &errorOffset, NULL);

    if (pattern == NULL) {
        PCRE2_UCHAR buffer[256];
        pcre2_get_error_message(errorCode, buffer, sizeof(buffer));
        printf("PCRE2 compilation failed at offset %zu: %s \n", errorOffset, buffer);
        return NULL;
    }

    // Create a match data block
    pcre2_match_data *match_data = pcre2_match_data_create_from_pattern(pattern, NULL);

    // Perform the match
    int rc = pcre2_match(pattern, (PCRE2_SPTR8) input, PCRE2_ZERO_TERMINATED,
                         0, 0, match_data, NULL);

    // Check for a successful match
    if (rc > 0) {
        // Extract the matched substring
        PCRE2_SIZE *ovector = pcre2_get_ovector_pointer(match_data);
        PCRE2_SPTR8 substring_start = (PCRE2_SPTR8) input + ovector[0];
        PCRE2_SIZE substring_length = ovector[1] - ovector[0];

        // Allocate memory for the matched string
        char *matchedString = (char *) malloc(substring_length + 1);

        // Copy the matched substring to the matchedString variable
        memcpy(matchedString, substring_start, substring_length);
        matchedString[substring_length] = '\0'; // Null-terminate the string

        // Print or process the matched string as needed
        *token = matchedString;

        // Free resources
        pcre2_match_data_free(match_data);
        pcre2_code_free(pattern);

        return (char *) substring_start + substring_length;
    } else if (rc == PCRE2_ERROR_NOMATCH) {
        printf("No match found.\n");
    } else {
        printf("PCRE2 matching failed with error code %d\n", rc);
    }

    // Free resources in case of failure
    pcre2_match_data_free(match_data);
    pcre2_code_free(pattern);

    return input;
}