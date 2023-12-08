#include "kml_lexer.h"
#define PCRE2_CODE_UNIT_WIDTH 8
#include <pcre2.h>
#include <iostream>

int GetToken(char* charStream){
    if(*charStream == '\0'){
        return EOF;
    }
    return 0;
}

void __exampleRegex(){
// The regular expression pattern
    const char *pattern = "world";

    // The input string to match against
    const char *input = "Hello, world!";

    // Compile the regular expression
    pcre2_code *re;
    int errorcode;
    PCRE2_SIZE erroroffset;
    re = pcre2_compile(
            reinterpret_cast<PCRE2_SPTR8>(pattern),
            PCRE2_ZERO_TERMINATED,
            0,
            &errorcode,
            &erroroffset,
            nullptr
    );

    if (re == nullptr) {
        PCRE2_UCHAR buffer[256];
        pcre2_get_error_message(errorcode, buffer, sizeof(buffer));
        std::cerr << "PCRE2 compilation failed at offset " << erroroffset << ": " << buffer << std::endl;
        return;
    }

    // Create a match data block
    pcre2_match_data *match_data = pcre2_match_data_create_from_pattern(re, nullptr);

    // Perform the match
    int rc = pcre2_match(
            re,
            reinterpret_cast<PCRE2_SPTR8>(input),
            PCRE2_ZERO_TERMINATED,
            0,
            0,
            match_data,
            nullptr
    );

    // Check for a successful match
    if (rc > 0) {
        std::cout << "Match found at position " << pcre2_get_ovector_pointer(match_data)[0] << std::endl;
    } else if (rc == PCRE2_ERROR_NOMATCH) {
        std::cout << "No match found." << std::endl;
    } else {
        std::cerr << "PCRE2 matching failed with error code " << rc << std::endl;
    }

    // Free resources
    pcre2_match_data_free(match_data);
    pcre2_code_free(re);

}