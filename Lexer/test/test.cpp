#include "../catch2/catch_amalgamated.cpp"
#include "../src/Lexer/Lexer.h"
#include "../src/utils/LexerDialog/LexerDialog.h"
#include <fstream>

TEST_CASE("Tests for single usage lexems")
{
	SECTION("Testing comments")
	{
		GIVEN("Lexer dialog, input and output")
		{
			std::stringstream input;
			std::stringstream output;

			auto lexerDialog = std::make_unique<LexerDialog>(output);

			WHEN("In lexer goes single comment with right usage")
			{
				input << "// this is a comment";
				auto lexer = std::make_unique<lexer::Lexer>(input);
				lexer->Process();

				THEN("List of token will be empty")
				{
					std::stringstream intendedOutput;

					lexerDialog->OutputTokens(lexer->GetAllTokens());
					REQUIRE(output.str() == intendedOutput.str());
				}
			}

			WHEN("In lexer goes double comments with right usage")
			{
				input << "// this is a comment" << std::endl
					  << "// and this is too comment";
				auto lexer = std::make_unique<lexer::Lexer>(input);
				lexer->Process();

				THEN("List of token will be empty")
				{
					std::stringstream intendedOutput;

					lexerDialog->OutputTokens(lexer->GetAllTokens());
					REQUIRE(output.str() == intendedOutput.str());
				}
			}

			WHEN("In lexer goes comment with wrong usage")
			{
				input << "//this is a comment";
				auto lexer = std::make_unique<lexer::Lexer>(input);

				THEN("there will be exception")
				{
					REQUIRE_THROWS_WITH(lexer->Process(), "Error, wrong lexem at pos(1, 0); [...//this...]");
				}
			}
		}
	}

	SECTION("Testing delimiter")
	{
		GIVEN("Lexer dialog, input and output")
		{
			std::stringstream input;
			std::stringstream output;

			auto lexerDialog = std::make_unique<LexerDialog>(output);

			WHEN("In lexer goes only `;`")
			{
				input << ";";
				auto lexer = std::make_unique<lexer::Lexer>(input);
				lexer->Process();

				THEN("List of token will be consist of delimiter")
				{
					std::stringstream intendedOutput;
					intendedOutput << "separator (;) [1, 0]" << std::endl;

					lexerDialog->OutputTokens(lexer->GetAllTokens());
					REQUIRE(output.str() == intendedOutput.str());
				}
			}

			WHEN("In lexer goes only `{}`")
			{
				input << "{" << std::endl << "}";
				auto lexer = std::make_unique<lexer::Lexer>(input);
				lexer->Process();

				THEN("List of token will be consist of 2 delimiter")
				{
					std::stringstream intendedOutput;
					intendedOutput << "separator ({) [1, 0]" << std::endl << "separator (}) [2, 0]" << std::endl;

					lexerDialog->OutputTokens(lexer->GetAllTokens());
					REQUIRE(output.str() == intendedOutput.str());
				}
			}

			WHEN("In lexer goes only `()`")
			{
				input << "(" << std::endl << ")";
				auto lexer = std::make_unique<lexer::Lexer>(input);
				lexer->Process();

				THEN("List of token will be consist of 2 delimiter")
				{
					std::stringstream intendedOutput;
					intendedOutput << "separator (() [1, 0]" << std::endl << "separator ()) [2, 0]" << std::endl;

					lexerDialog->OutputTokens(lexer->GetAllTokens());
					REQUIRE(output.str() == intendedOutput.str());
				}
			}

			WHEN("In lexer goes only `[]`")
			{
				input << "[" << std::endl << "]";
				auto lexer = std::make_unique<lexer::Lexer>(input);
				lexer->Process();

				THEN("List of token will be consist of 2 delimiter")
				{
					std::stringstream intendedOutput;
					intendedOutput << "separator ([) [1, 0]" << std::endl << "separator (]) [2, 0]" << std::endl;

					lexerDialog->OutputTokens(lexer->GetAllTokens());
					REQUIRE(output.str() == intendedOutput.str());
				}
			}
		}
	}

	SECTION("Testing keywords")
	{
		GIVEN("Lexer dialog, input and output")
		{
			std::stringstream input;
			std::stringstream output;

			auto lexerDialog = std::make_unique<LexerDialog>(output);

			WHEN("In lexer goes keyword int")
			{
				input << "int";
				auto lexer = std::make_unique<lexer::Lexer>(input);
				lexer->Process();

				THEN("List of token will be consist of keyword")
				{
					std::stringstream intendedOutput;
					intendedOutput << "keyword (int) [1, 0]" << std::endl;

					lexerDialog->OutputTokens(lexer->GetAllTokens());
					REQUIRE(output.str() == intendedOutput.str());
				}
			}

			WHEN("In lexer goes keyword float")
			{
				input << "float";
				auto lexer = std::make_unique<lexer::Lexer>(input);
				lexer->Process();

				THEN("List of token will be consist of keyword")
				{
					std::stringstream intendedOutput;
					intendedOutput << "keyword (float) [1, 0]" << std::endl;

					lexerDialog->OutputTokens(lexer->GetAllTokens());
					REQUIRE(output.str() == intendedOutput.str());
				}
			}

			WHEN("In lexer goes 2 keywords with delimiter")
			{
				input << "float;" << std::endl << "int;";
				auto lexer = std::make_unique<lexer::Lexer>(input);
				lexer->Process();

				THEN("List of token will be consist of keywords and delimiter")
				{
					std::stringstream intendedOutput;
					intendedOutput
						<< "keyword (float) [1, 0]" << std::endl
						<< "separator (;) [1, 5]" << std::endl
						<< "keyword (int) [2, 0]" << std::endl
						<< "separator (;) [2, 3]" << std::endl;

					lexerDialog->OutputTokens(lexer->GetAllTokens());
					REQUIRE(output.str() == intendedOutput.str());
				}
			}
		}
	}

	SECTION("Testing identifiers")
	{
		GIVEN("Lexer dialog, input and output")
		{
			std::stringstream input;
			std::stringstream output;

			auto lexerDialog = std::make_unique<LexerDialog>(output);

			WHEN("In lexer goes right identifier with only letters")
			{
				input << "id";
				auto lexer = std::make_unique<lexer::Lexer>(input);
				lexer->Process();

				THEN("List of token will be consist of identifier")
				{
					std::stringstream intendedOutput;
					intendedOutput << "identifier (id) [1, 0]" << std::endl;

					lexerDialog->OutputTokens(lexer->GetAllTokens());
					REQUIRE(output.str() == intendedOutput.str());
				}
			}

			WHEN("In lexer goes right identifier with letters and numbers")
			{
				input << "id123";
				auto lexer = std::make_unique<lexer::Lexer>(input);
				lexer->Process();

				THEN("List of token will be consist of identifier")
				{
					std::stringstream intendedOutput;
					intendedOutput << "identifier (id123) [1, 0]" << std::endl;

					lexerDialog->OutputTokens(lexer->GetAllTokens());
					REQUIRE(output.str() == intendedOutput.str());
				}
			}

			WHEN("In lexer goes identifier with only numbers")
			{
				input << "123";
				auto lexer = std::make_unique<lexer::Lexer>(input);
				lexer->Process();

				THEN("List of token will be consist of number")
				{
					std::stringstream intendedOutput;
					intendedOutput << "number (123) [1, 0]" << std::endl;

					lexerDialog->OutputTokens(lexer->GetAllTokens());
					REQUIRE(output.str() == intendedOutput.str());
				}
			}
		}
	}

	SECTION("Testing values")
	{
		GIVEN("Lexer dialog, input and output")
		{
			std::stringstream input;
			std::stringstream output;

			auto lexerDialog = std::make_unique<LexerDialog>(output);

			WHEN("In lexer goes 10 notation number")
			{
				input << "1234";
				auto lexer = std::make_unique<lexer::Lexer>(input);
				lexer->Process();

				THEN("List of token will be consist of number")
				{
					std::stringstream intendedOutput;
					intendedOutput << "number (1234) [1, 0]" << std::endl;

					lexerDialog->OutputTokens(lexer->GetAllTokens());
					REQUIRE(output.str() == intendedOutput.str());
				}
			}

			WHEN("In lexer goes 16 notation number")
			{
				input << "0x12EDA34";
				auto lexer = std::make_unique<lexer::Lexer>(input);
				lexer->Process();

				THEN("List of token will be consist of number")
				{
					std::stringstream intendedOutput;
					intendedOutput << "number (0x12EDA34) [1, 0]" << std::endl;

					lexerDialog->OutputTokens(lexer->GetAllTokens());
					REQUIRE(output.str() == intendedOutput.str());
				}
			}

			WHEN("In lexer goes 2 notation number")
			{
				input << "0b1010101";
				auto lexer = std::make_unique<lexer::Lexer>(input);
				lexer->Process();

				THEN("List of token will be consist of number")
				{
					std::stringstream intendedOutput;
					intendedOutput << "number (0b1010101) [1, 0]" << std::endl;

					lexerDialog->OutputTokens(lexer->GetAllTokens());
					REQUIRE(output.str() == intendedOutput.str());
				}
			}

			WHEN("In lexer goes 8 notation number")
			{
				input << "0e1010101";
				auto lexer = std::make_unique<lexer::Lexer>(input);
				lexer->Process();

				THEN("List of token will be consist of number")
				{
					std::stringstream intendedOutput;
					intendedOutput << "number (0e1010101) [1, 0]" << std::endl;

					lexerDialog->OutputTokens(lexer->GetAllTokens());
					REQUIRE(output.str() == intendedOutput.str());
				}
			}

			WHEN("In lexer goes string")
			{
				input << "\"string\"";
				auto lexer = std::make_unique<lexer::Lexer>(input);
				lexer->Process();

				THEN("List of token will be consist of string")
				{
					std::stringstream intendedOutput;
					intendedOutput << "string (\"string\") [1, 0]" << std::endl;

					lexerDialog->OutputTokens(lexer->GetAllTokens());
					REQUIRE(output.str() == intendedOutput.str());
				}
			}

			WHEN("In lexer goes float number")
			{
				input << "1.213132";
				auto lexer = std::make_unique<lexer::Lexer>(input);
				lexer->Process();

				THEN("List of token will be consist of number")
				{
					std::stringstream intendedOutput;
					intendedOutput << "number (1.213132) [1, 0]" << std::endl;

					lexerDialog->OutputTokens(lexer->GetAllTokens());
					REQUIRE(output.str() == intendedOutput.str());
				}
			}

			WHEN("In lexer goes 16 notation number with wrong value")
			{
				input << "0xGGG";
				auto lexer = std::make_unique<lexer::Lexer>(input);

				THEN("there will be exception")
				{
					REQUIRE_THROWS_WITH(lexer->Process(), "Error, wrong lexem at pos(1, 0); [...0xGGG...]");
				}
			}

			WHEN("In lexer goes 8 notation number with wrong value(letters)")
			{
				input << "0eGGG";
				auto lexer = std::make_unique<lexer::Lexer>(input);

				THEN("there will be exception")
				{
					REQUIRE_THROWS_WITH(lexer->Process(), "Error, wrong lexem at pos(1, 0); [...0eGGG...]");
				}
			}

			WHEN("In lexer goes 8 notation number with wrong value(digits)")
			{
				input << "0e123456789";
				auto lexer = std::make_unique<lexer::Lexer>(input);

				THEN("there will be exception")
				{
					REQUIRE_THROWS_WITH(lexer->Process(), "Error, wrong lexem at pos(1, 0); [...0e123456789...]");
				}
			}

			WHEN("In lexer goes 2 notation number with wrong value(digits)")
			{
				input << "0b1101023";
				auto lexer = std::make_unique<lexer::Lexer>(input);

				THEN("there will be exception")
				{
					REQUIRE_THROWS_WITH(lexer->Process(), "Error, wrong lexem at pos(1, 0); [...0b1101023...]");
				}
			}

			WHEN("In lexer goes 2 notation number with wrong value(letters)")
			{
				input << "0b1101023A";
				auto lexer = std::make_unique<lexer::Lexer>(input);

				THEN("there will be exception")
				{
					REQUIRE_THROWS_WITH(lexer->Process(), "Error, wrong lexem at pos(1, 0); [...0b1101023A...]");
				}
			}

			WHEN("In lexer goes float number with 2 separators(1.232131.2313)")
			{
				input << "1.232131.2313";
				auto lexer = std::make_unique<lexer::Lexer>(input);

				THEN("there will be exception")
				{
					REQUIRE_THROWS_WITH(lexer->Process(), "Error, wrong lexem at pos(1, 0); [...1.232131.2313...]");
				}
			}
		}
	}

	SECTION("Testing expressions")
	{
		GIVEN("Lexer dialog, input and output")
		{
			std::stringstream input;
			std::stringstream output;

			auto lexerDialog = std::make_unique<LexerDialog>(output);

			WHEN("In lexer goes int + int")
			{
				input << "1 + 1";
				auto lexer = std::make_unique<lexer::Lexer>(input);
				lexer->Process();

				THEN("List of token will be consist of 3 tokens")
				{
					std::stringstream intendedOutput;
					intendedOutput << "number (1) [1, 0]" << std::endl;
					intendedOutput << "plus (+) [1, 2]" << std::endl;
					intendedOutput << "number (1) [1, 4]" << std::endl;

					lexerDialog->OutputTokens(lexer->GetAllTokens());
					REQUIRE(output.str() == intendedOutput.str());
				}
			}

			WHEN("In lexer goes int * int")
			{
				input << "1 * 1";
				auto lexer = std::make_unique<lexer::Lexer>(input);
				lexer->Process();

				THEN("List of token will be consist of 3 tokens")
				{
					std::stringstream intendedOutput;
					intendedOutput << "number (1) [1, 0]" << std::endl;
					intendedOutput << "multiplication (*) [1, 2]" << std::endl;
					intendedOutput << "number (1) [1, 4]" << std::endl;

					lexerDialog->OutputTokens(lexer->GetAllTokens());
					REQUIRE(output.str() == intendedOutput.str());
				}
			}

			WHEN("In lexer goes int / int")
			{
				input << "1 / 1";
				auto lexer = std::make_unique<lexer::Lexer>(input);
				lexer->Process();

				THEN("List of token will be consist of 3 tokens")
				{
					std::stringstream intendedOutput;
					intendedOutput << "number (1) [1, 0]" << std::endl;
					intendedOutput << "division (/) [1, 2]" << std::endl;
					intendedOutput << "number (1) [1, 4]" << std::endl;

					lexerDialog->OutputTokens(lexer->GetAllTokens());
					REQUIRE(output.str() == intendedOutput.str());
				}
			}

			WHEN("In lexer goes int - int")
			{
				input << "1 - 1";
				auto lexer = std::make_unique<lexer::Lexer>(input);
				lexer->Process();

				THEN("List of token will be consist of 3 tokens")
				{
					std::stringstream intendedOutput;
					intendedOutput << "number (1) [1, 0]" << std::endl;
					intendedOutput << "minus (-) [1, 2]" << std::endl;
					intendedOutput << "number (1) [1, 4]" << std::endl;

					lexerDialog->OutputTokens(lexer->GetAllTokens());
					REQUIRE(output.str() == intendedOutput.str());
				}
			}
		}
	}
}

TEST_CASE("Tests for different cases")
{
	const std::string fileName = GENERATE("ids_and_assignments", "brackets", "all");
	std::ifstream input;
	input.open("../test/files/" + fileName + ".txt");
	std::stringstream output;

	auto lexerDialog = std::make_unique<LexerDialog>(output);

	WHEN("In lexer goes file content")
	{
		auto lexer = std::make_unique<lexer::Lexer>(input);
		lexer->Process();

		THEN("List of token will be empty")
		{
			std::ifstream intendedOutput;
			intendedOutput.open("../test/files/" + fileName + "-output.txt");
			std::stringstream buffer;
			buffer << intendedOutput.rdbuf();

			lexerDialog->OutputTokens(lexer->GetAllTokens());

			REQUIRE(output.str() == buffer.str());
		}
	}
}