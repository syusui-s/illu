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
		if (token_first == NULL) throw "";
		return input.substr(token_first - input_cstr, cursor - token_first);
	}

	/**
	 * Get current Token-type
	 *
	 * @return tokentype::Type
	 */
	tokentype::Type Scanner::current_tokentype() const {
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
				NULL       = "\000";

				// Special Chars
				" "			{ continue; }
				NULL		{ --cursor; type = tokentype::T_EOF; return false; }

				// Stack Expressions
				"["			{ type = tokentype::T_STACK_START; return true; }
				"]"			{ type = tokentype::T_STACK_END;   return true; }

				// Instructions
				// - Basic Arithmetic Operations
				"+"			{ type = tokentype::T_INST_PLUS; return true; }
				"-"			{ type = tokentype::T_INST_MINUS; return true; }
				"*"			{ type = tokentype::T_INST_MULTIPLICATION; return true; }
				"/"			{ type = tokentype::T_INST_DIVISION; return true; }

				// - Basic Stack Operations
				"drop"		{ type = tokentype::T_INST_DROP; return true; }
				"."			{ type = tokentype::T_INST_DROP; return true; }

				// - Control Operations
				"if"		{ type = tokentype::T_INST_IF; return true; }

				// Singleton Objects
				"nil"		{ type = tokentype::T_NIL; return true; }

				// Literal Expressions
				STRING		{ type = tokentype::T_STRING; return true; }
				INTEGER		{ type = tokentype::T_INTEGER; return true; }
				FLOAT		{ type = tokentype::T_FLOAT; return true; }
				SYMBOL		{ type = tokentype::T_SYMBOL; return true; }

				// Boolean Expressions
				"true"		{ type = tokentype::T_BOOLEAN_TRUE; return true; }
				"false"		{ type = tokentype::T_BOOLEAN_FALSE; return true; }

				// Identifier
				IDENTIFIER	{ type = tokentype::T_IDENTIFIER; return true; }

				// Undefined
				[^]			{ type = tokentype::T_UNDEFINED; return true; }
			 */
		}
	}
} // lexer
