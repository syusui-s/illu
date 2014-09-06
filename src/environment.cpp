#include "environment.hpp"

namespace environment {
	/**
	 * add/applicate element into/to stack
	 */
	model::Stack& elem_interpret(model::Element* elem, model::Stack& stack) {
		// Identifier
		if (elem->instance_of<model::Identifier>()) {
			std::cerr << "Identifier is not implemented." << std::endl;
			// Instruction
		} else if (elem->instance_of<model::Instruction>()) {
			model::Instruction* inst = elem->cast<model::Instruction>();

			if (stack.size() >= inst->num_of_args()) {
				inst->applicate(stack);
			} else {
				std::cerr << "Cannot Applicate Instruction : too few arguments" << std::endl;
			}
			// Data Objects
		} else {
			stack.push(elem);
		}

		return stack;
	}
} // namespace envir
