#pragma once

#include <string>

#include "tokentype.hpp"
#include "scanner.hpp"
#include "model.hpp"

namespace lexer {
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
			model::Element* to_element();
	};

	/**
	 * Vector of Tokens
	 */
	class TokenVector : public std::vector<Token>
	{
	};

	/**
	 * Tokenizer Class
	 */
	class Tokenizer
	{
		private:
			std::string input;
			Scanner *scanner;
		public:
			Tokenizer(const std::string &_input) : input(_input) {
				this->scanner = new Scanner(input);
			}
			bool read_next();
			Token current_token();
	};

} // lexer
