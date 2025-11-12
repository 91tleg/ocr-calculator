#include <gtest/gtest.h>
#include "../src/modules/parser/parser.h"

TEST(ParserTest, TokenMapping)
{
    EXPECT_EQ(get_token_by_index(0), '0');
    EXPECT_EQ(get_token_by_index(10), '+');
    EXPECT_EQ(get_token_by_index(12), '*');
}