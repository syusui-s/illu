/* vim: set filetype=cpp : */
#include "lexer.hpp"

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
	 * @return tokentype::Types
	 */
	enum tokentype::Types Scanner::current_tokentype() const {
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

				IDENTIFIER = [a-zA-Z_][a-zA-Z_0-9]*;
				INTEGER    = [+-]?[0-9]+;
				FLOAT      = [+-]?[1-9][0-9]*"."[0-9]+;
				STRING     = "'".*"'";
				NULL       = "\000";

				" "			{ continue; }
				NULL		{ --cursor; type = tokentype::T_EOF; return false; }
				IDENTIFIER	{ type = tokentype::T_IDENTIFIER; return true; }
				STRING		{ type = tokentype::T_STRING; return true; }
				INTEGER		{ type = tokentype::T_INTEGER; return true; }
				FLOAT		{ type = tokentype::T_FLOAT; return true; }
				"+"			{ type = tokentype::T_INST_PLUS; return true; }
				"-"			{ type = tokentype::T_INST_MINUS; return true; }
				"*"			{ type = tokentype::T_INST_MUL; return true; }
				"/"			{ type = tokentype::T_INST_DIV; return true; }
				[^]			{ type = tokentype::T_UNDEFINED; return true; }
			 */
		}
	}
} // lexer
