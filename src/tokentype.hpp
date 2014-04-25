#pragma once

// namespace tokentype
namespace tokentype {
	/**
	 * Definition of All Token-types
	 */
	typedef enum {
		T_UNDEFINED  = -1,
		T_EOF        =  0,
		T_IDENTIFIER =  1,
		// Data Types
		T_INTEGER,
		T_FLOAT,
		T_STRING,
		// Instructions
		T_INST_PLUS,
		T_INST_MINUS,
		T_INST_MUL,
		T_INST_DIV,
	} Type;
} // namespace tokentype
