#pragma once

#include <string>

#include "tokentype.hpp"

namespace lexer {
	/**
	 * Scanner Class
	 */
	class Scanner
	{
		private:
			std::string input;
			tokenizer::TokenType type;
			char *input_cstr;
			char *marker;
			char *cursor;
			char *token_first;
		public:
			/**
			 * constructor
			 */
			Scanner(const std::string& _input) :
				input(_input),
				type(tokenizer::TokenType::UNDEFINED),
				input_cstr(const_cast<char*>(_input.c_str())),
				cursor(input_cstr),
				token_first(nullptr)
				{}
			~Scanner() { }
			void reset();
			bool read_next();
			std::string current_lexeme();
			tokenizer::TokenType current_tokentype() const;
	};

} // lexer
