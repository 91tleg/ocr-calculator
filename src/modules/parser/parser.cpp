#include "parser.h"
#include <iterator>

char get_token_by_index(uint8_t index)
{
    if (index >= std::size(token_lookup)) { return '?'; }
    return token_lookup[index];
}
