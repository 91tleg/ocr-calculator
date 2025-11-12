#ifndef PARSER_H
#define PARSER_H

#include <cstdint>

constexpr char token_lookup[] = {
    '0','1','2','3','4','5','6','7','8','9','+','-','*'
};

char get_token_by_index(uint8_t index);

#endif // PARSER_H
