#include "LexerDialog.h"

namespace
{
	std::string TokenTypeToString(token::type::TokenType type)
	{
		switch (type)
		{
			case token::type::TokenType::KEYWORD:
				return "keyword";
			case token::type::TokenType::IDENTIFIER:
				return "identifier";
			case token::type::TokenType::ASSIGNMENT:
				return "assignment";
			case token::type::TokenType::NUMBER:
				return "number";
			case token::type::TokenType::SEPARATOR:
				return "separator";
			case token::type::TokenType::STRING:
				return "string";
			case token::type::TokenType::PLUS:
				return "plus";
			case token::type::TokenType::MINUS:
				return "minus";
			case token::type::TokenType::MULTIPLICATION:
				return "multiplication";
			case token::type::TokenType::DIVISION:
				return "division";
			case token::type::TokenType::LOGICAL:
				return "logical";
			default:
				return "Please, dont call the police. I dont want to go back to jail.";
		}
	}
}

LexerDialog::LexerDialog(std::ostream& output)
	: m_output(output)
{
}

void LexerDialog::OutputTokens(std::vector<token::Token>&& tokens)
{
	for (const auto& token: tokens)
	{
		m_output << TokenTypeToString(token.GetType()) << " ("
				 << token.GetData()
				 << ") [" << token.GetPosition().row << ", " << token.GetPosition().column << "]" << std::endl;
	}
}