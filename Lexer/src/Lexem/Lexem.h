#pragma once
#include <string>

namespace lexem
{
    enum class LexemType
    {
		KEYWORD,
		IDENTIFIER,
        NUMBER,
        SEPARATOR,
        PLUS,
        MINUS,
        MULTIPLICATION,
        DIVISION,
        ASSIGNMENT,
        STRING,
        ERROR,
		COMMENT,
		LOGICAL,
    };

    LexemType GetLexemType(const std::string& data);
}