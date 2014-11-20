#include "tokenizer.hpp"

namespace lexer {
	//////////////////////////////////
	// Token
	/**
	 * Convert Token to Element if possible
	 *
	 * @return Element*
	 */
	model::sp_Element Token::to_element()
	{
		using namespace tokentype;

		switch (this->type) {
			// Data Types
			case T_IDENTIFIER:
				return std::make_shared<model::Identifier>(lexeme);
			case T_INTEGER:
				return std::make_shared<model::Integer>(lexeme, 10);
			case T_FLOAT:
				return std::make_shared<model::Float>(lexeme);
			case T_STRING:
				return std::make_shared<model::String>( lexeme.substr(1, lexeme.length() - 2 ) );
			case T_NIL:
				return std::make_shared<model::Nil>();
			case T_BOOLEAN_TRUE:
				return std::make_shared<model::Boolean>(true);
			case T_BOOLEAN_FALSE:
				return std::make_shared<model::Boolean>(false);
			case T_SYMBOL:
				return std::make_shared<model::Symbol>( lexeme.substr(1, lexeme.length() - 1 ) );
			// Instructions
			// - Basic Arithmetic Operations
			case T_INST_PLUS:
				return std::make_shared<model::Instruction>(tokentype::T_INST_PLUS);
			case T_INST_MINUS:
				return std::make_shared<model::Instruction>(tokentype::T_INST_MINUS);
			case T_INST_MULTIPLICATION:
				return std::make_shared<model::Instruction>(tokentype::T_INST_MULTIPLICATION);
			case T_INST_DIVISION:
				return std::make_shared<model::Instruction>(tokentype::T_INST_DIVISION);
			// - Basic Stack Operations
			case T_INST_DROP:
				return std::make_shared<model::Instruction>(tokentype::T_INST_DROP);
			// - Control Operations
			case T_INST_IF:
				return std::make_shared<model::Instruction>(tokentype::T_INST_IF);
			default:
				return nullptr;
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
