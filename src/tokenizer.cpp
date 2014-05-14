#include "tokenizer.hpp"

namespace lexer {
	//////////////////////////////////
	// Token
	/**
	 * Convert Token to Element
	 *
	 * @return Element*
	 */
	model::Element* Token::to_element()
	{
		using namespace tokentype;

		switch (this->type) {
			case T_INTEGER:
				return new model::Integer(lexeme, 10);
			case T_FLOAT:
				return new model::Float(lexeme);
			default:
				throw "TokenConvertionError";
		}

	}

	//////////////////////////////////
	// TokenVector
	/**
	 * Convert self into Stack
	 *
	 * @return model::Stack
	 */
	model::Stack TokenVector::to_stack()
	{
		model::Stack stack;
		
		for (auto&& elem : *this) {
			stack.push(elem.to_element());
		}

		return stack;
	}

	//////////////////////////////////
	// Tokenizer
	/**
	 * Read Next Token
	 *
	 * @bool
	 */
	bool Tokenizer::read_next() {
		return this->scanner->read_next();
	}

	/**
	 * Get current Token
	 *
	 * @return Token
	 */
	Token Tokenizer::current_token() {
		return Token(
			this->scanner->current_lexeme(),
			this->scanner->current_tokentype()
		);
	}

	/**
	 * Tokenize string and convert it into TokenVector
	 *
	 * @return TokenVector
	 */
	TokenVector Tokenizer::tokenize() {
		TokenVector token_vector;

		while (this->read_next()) {
			token_vector.push_back(this->current_token());
		}

		return token_vector;
	}

	
} // namespace lexer
