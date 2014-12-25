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
		using namespace tokenizer;

		switch (this->type) {
			// Data Types
			case TokenType::IDENTIFIER:
				return std::make_shared<model::Identifier>(lexeme);
			case TokenType::INTEGER:
				return std::make_shared<model::Integer>(lexeme, 10);
			case TokenType::FLOAT:
				return std::make_shared<model::Float>(lexeme);
			case TokenType::STRING:
				return std::make_shared<model::String>( lexeme.substr(1, lexeme.length() - 2 ) );
			case TokenType::NIL:
				return std::make_shared<model::Nil>();
			case TokenType::BOOLEAN_TRUE:
				return std::make_shared<model::Boolean>(true);
			case TokenType::BOOLEAN_FALSE:
				return std::make_shared<model::Boolean>(false);
			case TokenType::SYMBOL:
				return std::make_shared<model::Symbol>( lexeme.substr(1, lexeme.length() - 1 ) );
			// INST_tructions
			// - Basic Arithmetic Operations
			case TokenType::INST_PLUS:
				return std::make_shared<model::Instruction>(tokenizer::TokenType::INST_PLUS);
			case TokenType::INST_MINUS:
				return std::make_shared<model::Instruction>(tokenizer::TokenType::INST_MINUS);
			case TokenType::INST_MULTIPLICATION:
				return std::make_shared<model::Instruction>(tokenizer::TokenType::INST_MULTIPLICATION);
			case TokenType::INST_DIVISION:
				return std::make_shared<model::Instruction>(tokenizer::TokenType::INST_DIVISION);
			// - Basic Stack Operations
			case TokenType::INST_DROP:
				return std::make_shared<model::Instruction>(tokenizer::TokenType::INST_DROP);
			// - Control Operations
			case TokenType::INST_IF:
				return std::make_shared<model::Instruction>(tokenizer::TokenType::INST_IF);
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
