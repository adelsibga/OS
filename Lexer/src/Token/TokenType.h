#pragma once
#include <map>
#include <string>

namespace token::type
{
    enum class TokenType
    {
        IDENTIFIER,
        KEYWORD,
        NUMBER,
        SEPARATOR,
        PLUS,
        MINUS,
        MULTIPLICATION,
        DIVISION,
        ASSIGNMENT,
        STRING,
        END,
		LOGICAL,
    };
}