#include "Lexer.h"
#include "../Lexem/Lexem.h"

namespace
{
    token::type::TokenType GetTokenType(const lexem::LexemType lexemType)
    {
        switch (lexemType)
        {
            case lexem::LexemType::KEYWORD:
                return token::type::TokenType::KEYWORD;
            case lexem::LexemType::IDENTIFIER:
                return token::type::TokenType::IDENTIFIER;
            case lexem::LexemType::ASSIGNMENT:
                return token::type::TokenType::ASSIGNMENT;
            case lexem::LexemType::NUMBER:
                return token::type::TokenType::NUMBER;
            case lexem::LexemType::SEPARATOR:
                return token::type::TokenType::SEPARATOR;
            case lexem::LexemType::STRING:
                return token::type::TokenType::STRING;
            case lexem::LexemType::PLUS:
                return token::type::TokenType::PLUS;
            case lexem::LexemType::MINUS:
                return token::type::TokenType::MINUS;
            case lexem::LexemType::MULTIPLICATION:
                return token::type::TokenType::MULTIPLICATION;
            case lexem::LexemType::DIVISION:
                return token::type::TokenType::DIVISION;
            case lexem::LexemType::LOGICAL:
                return token::type::TokenType::LOGICAL;
            default:
                throw std::runtime_error("Error, cannot associate lexem type to token type");
        }
    }
}

namespace lexer
{
    Lexer::Lexer(std::istream& input)
    : m_input(input)
    {
    }

    void Lexer::Process()
    {
        std::string line;
        while (std::getline(m_input, line))
        {
            m_position.row++;
            std::istringstream iss(line);

            std::string data;
			try
			{
				while (iss >> data)
				{
					if (iss.tellg() == -1)
					{
						m_position.column = line.size() - data.size();
					}
					else
					{
						m_position.column = static_cast<int>(iss.tellg()) - data.size();
					}
					if (data.size() != 1 && data[data.size() - 1] == ';')
					{
						AddNewToken(data.substr(0, data.size() - 1));
						m_position.column += data.size() - 1;
						data = data.substr(data.size() - 1, 1);
					}
					AddNewToken(data);
				}
			}
			catch (const std::logic_error& exception)
			{
			}
        }
    }

    std::vector<token::Token> Lexer::GetAllTokens()
    {
        return m_tokens;
    }

    void Lexer::AddNewToken(const std::string& data)
    {
        auto newLexemType = lexem::GetLexemType(data);
        if (newLexemType == lexem::LexemType::ERROR)
        {
            throw std::runtime_error("Error, wrong lexem at pos(" + std::to_string(m_position.row) + ", " + std::to_string(m_position.column) + "); [..." + data + "...]");
        }
		if (newLexemType == lexem::LexemType::COMMENT)
		{
			throw std::logic_error("Comment is not required");
		}

        m_tokens.emplace_back(token::Token(GetTokenType(newLexemType), m_position, data));
    }
}