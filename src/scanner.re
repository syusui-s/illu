/* vim: set filetype=cpp : */
#include "scanner.hpp"

/**
 * namespace lexer
 */
namespace lexer {
	/**
	 * Get current lexeme
	 *
	 * @return std::string
	 */
	std::string Scanner::current_lexeme() {
		if (token_first == nullptr) throw "";
		return input.substr(token_first - input_cstr, cursor - token_first);
	}

	/**
	 * Get current Token-type
	 *
	 * @return tokenizer::TokenType
	 */
	tokenizer::TokenType Scanner::current_tokentype() const {
		return type;
	}

	/**
	 * Read next lexeme
	 */
	bool Scanner::read_next() {
		for (;;) {
			token_first = cursor;

			/*!re2c
				re2c:define:YYCTYPE  = "char";
				re2c:define:YYCURSOR = cursor;
				re2c:define:YYMARKER = marker;
				re2c:yyfill:enable   = 0;
				re2c:yych:conversion = 1;
				re2c:indent:top      = 1;

				// Literal Expressions Definitions
				IDENTIFIER = [a-zA-Z_][a-zA-Z_0-9]*;
				INTEGER    = [+-]?[0-9]+;
				FLOAT      = [+-]?[0-9]+"."[0-9]+;
				STRING     = ["][^"\000\n]*["];
				SYMBOL     = ":"IDENTIFIER;
				nullptr       = "\000";

				// Special Chars
				" "			{ continue; }
				nullptr		{ --cursor; type = tokenizer::TokenType::EOFTOK; return false; }

				// Stack Expressions
				"["			{ type = tokenizer::TokenType::STACK_START; return true; }
				"]"			{ type = tokenizer::TokenType::STACK_END;   return true; }

				// Instructions
				// - Basic Arithmetic Operations
				"+"			{ type = tokenizer::TokenType::INST_PLUS; return true; }
				"-"			{ type = tokenizer::TokenType::INST_MINUS; return true; }
				"*"			{ type = tokenizer::TokenType::INST_MULTIPLICATION; return true; }
				"/"			{ type = tokenizer::TokenType::INST_DIVISION; return true; }

				// - Basic Stack Operations
				"drop"		{ type = tokenizer::TokenType::INST_DROP; return true; }
				"."			{ type = tokenizer::TokenType::INST_DROP; return true; }

				// - Evrironment Operations
				"="			{ type = tokenizer::TokenType::INST_BIND; return true; }

				// - Control Operations
				"if"		{ type = tokenizer::TokenType::INST_IF; return true; }

				// Singleton Objects
				"nil"		{ type = tokenizer::TokenType::NIL; return true; }

				// Literal Expressions
				STRING		{ type = tokenizer::TokenType::STRING; return true; }
				INTEGER		{ type = tokenizer::TokenType::INTEGER; return true; }
				FLOAT		{ type = tokenizer::TokenType::FLOAT; return true; }
				SYMBOL		{ type = tokenizer::TokenType::SYMBOL; return true; }

				// Boolean Expressions
				"true"		{ type = tokenizer::TokenType::BOOLEAN_TRUE; return true; }
				"false"		{ type = tokenizer::TokenType::BOOLEAN_FALSE; return true; }

				// Identifier
				IDENTIFIER	{ type = tokenizer::TokenType::IDENTIFIER; return true; }

				// Undefined
				[^]			{ type = tokenizer::TokenType::UNDEFINED; return true; }
			 */
		}
	}
} // lexer
