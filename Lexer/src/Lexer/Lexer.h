#pragma once

#include <sstream>
#include <vector>
#include "../Common/Position.h"
#include "../Token/Token.h"

namespace lexer
{
    class Lexer
    {
    public:
        explicit Lexer(std::istream& input);

        void Process();

        std::vector<token::Token> GetAllTokens();
    private:
        void AddNewToken(const std::string& data);

        std::istream& m_input;
        Position m_position;
        std::vector<token::Token> m_tokens;
    };
}