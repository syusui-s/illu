#pragma once

// namespace tokentype
namespace tokentype {
	/**
	 * Definition of All Token-types
	 */
	typedef enum {
		// Special Tokens
		T_UNDEFINED  = -1,
		T_EOF        =  0,

		// Identifier
		T_IDENTIFIER =  1,

		// Stack Expressions
		T_STACK_START,
		T_STACK_END,

		// Data Types
		T_INTEGER,
		T_FLOAT,
		T_STRING,
		T_NIL,
		T_BOOLEAN_TRUE,
		T_BOOLEAN_FALSE,
		T_SYMBOL,

		// Instructions
		// - Basic Arithmec Operations
		T_INST_PLUS,
		T_INST_MINUS,
		T_INST_MULTIPLICATION,
		T_INST_DIVISION,
		// - Basic Stack Operations
		T_INST_DROP,
	} Type;
} // namespace tokentype
