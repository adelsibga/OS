#pragma once
#include "./TokenType.h"
#include "../Common/Position.h"
#include <string>

namespace token
{
    class Token
    {
    public:
        explicit Token(type::TokenType tokenType, Position position, std::string data);
        [[nodiscard]] type::TokenType GetType() const;
        [[nodiscard]] Position GetPosition() const;
        [[nodiscard]] std::string GetData() const;
    private:
        type::TokenType m_tokenType;
        Position m_position;
        std::string m_data;
    };
}