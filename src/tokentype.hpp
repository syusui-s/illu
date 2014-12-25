#pragma once

// namespace tokenizer
namespace tokenizer {
	/**
	 * Definition of All Token-types
	 */
	enum class TokenType : int {
		// Special Tokens
		UNDEFINED  = -1,
		EOFTOK     =  0,

		// Identifier
		IDENTIFIER =  1,

		// Stack Expressions
		STACK_START,
		STACK_END,

		// Data Types
		INTEGER,
		FLOAT,
		STRING,
		NIL,
		BOOLEAN_TRUE,
		BOOLEAN_FALSE,
		SYMBOL,

		// Instructions
		// - Basic Arithmec Operations
		INST_PLUS,
		INST_MINUS,
		INST_MULTIPLICATION,
		INST_DIVISION,
		// - Basic Stack Operations
		INST_DROP,
		// - Control Operation
		INST_IF,
	};
} // namespace tokenizer
