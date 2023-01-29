#include "Token.h"

#include <utility>

namespace token
{
    Token::Token(type::TokenType tokenType, Position position, std::string data)
            : m_tokenType(tokenType)
            , m_position(position)
            , m_data(std::move(data))
    {
    }

    type::TokenType Token::GetType() const
    {
        return m_tokenType;
    }

    Position Token::GetPosition() const
    {
        return m_position;
    }

    std::string Token::GetData() const
    {
        return m_data;
    }
}