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
			enum tokentype::Types type;
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
			enum tokentype::Types current_tokentype() const;
	};

	//enum Types scan(char *input);
	//model::Stack tokenize();
	class Tokenizer
	{
		// tokenize string
		static model::Stack tokenize(std::string);
	};
} // parser
