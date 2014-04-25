#pragma once

#include <string>

#include "tokentype.hpp"
#include "model.hpp"

namespace lexer {
	/**
	 * Scanner Class
	 */
	class Scanner
	{
		private:
			std::string input;
			tokentype::Type type;
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
				type(tokentype::T_UNDEFINED),
				input_cstr(const_cast<char*>(_input.c_str())),
				cursor(input_cstr),
				token_first(NULL)
				{}
			~Scanner() { }
			void reset();
			bool read_next();
			std::string current_lexeme();
			tokentype::Type current_tokentype() const;
	};

	/**
	 * Token Class
	 * representation of Token
	 */
	class Token
	{
		public:
			const std::string lexeme;
			const tokentype::Type type;

			Token(const std::string &_lexeme, const tokentype::Type _type) :
				lexeme(_lexeme), type(_type) {}
			model::Element to_element();
	};

	/**
	 * Vector of Tokens
	 */
	class TokenVector : public std::vector<Token>
	{
		public:
			model::Stack to_stack();
	};

	/**
	 * Tokenizer Class
	 */
	class Tokenizer
	{
		private:
			std::string input;
		public:
			Tokenizer(const std::string &_input) : input(_input) {}
			bool read_next();
			Token current_token();
			TokenVector tokenize();
	};
} // parser
