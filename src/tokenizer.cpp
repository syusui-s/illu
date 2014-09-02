#include "tokenizer.hpp"

namespace lexer {
	//////////////////////////////////
	// Token
	/**
	 * Convert Token to Element if possible
	 *
	 * @return Element*
	 */
	model::Element* Token::to_element()
	{
		using namespace tokentype;

		switch (this->type) {
			// Data Types
			case T_IDENTIFIER:
				return new model::Identifier(lexeme);
			case T_INTEGER:
				return new model::Integer(lexeme, 10);
			case T_FLOAT:
				return new model::Float(lexeme);
			case T_STRING:
				return new model::String( lexeme.substr(1, lexeme.length() - 2 ) );
			case T_NIL:
				return new model::Nil();
			case T_BOOLEAN_TRUE:
				return new model::Boolean(true);
			case T_BOOLEAN_FALSE:
				return new model::Boolean(false);
			case T_SYMBOL:
				return new model::Symbol( lexeme.substr(1, lexeme.length() - 1 ) );
			// Instructions
			// - Basic Arithmetic Operations
			case T_INST_PLUS:
				return new model::Instruction(tokentype::T_INST_PLUS);
			case T_INST_MINUS:
				return new model::Instruction(tokentype::T_INST_MINUS);
			case T_INST_MULTIPLICATION:
				return new model::Instruction(tokentype::T_INST_MULTIPLICATION);
			case T_INST_DIVISION:
				return new model::Instruction(tokentype::T_INST_DIVISION);
			// - Basic Stack Operations
			case T_INST_DROP:
				return new model::Instruction(tokentype::T_INST_DROP);
			default:
				throw "TokenConvertionError";
		}

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
} // namespace lexer
