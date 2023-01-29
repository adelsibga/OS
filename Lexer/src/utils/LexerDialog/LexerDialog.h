#pragma once
#include <sstream>
#include <vector>
#include "../../Token/Token.h"

class LexerDialog
{
public:
    explicit LexerDialog(std::ostream& output);
    void OutputTokens(std::vector<token::Token>&& tokens);
private:
    std::ostream& m_output;
};