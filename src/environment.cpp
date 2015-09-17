#include "environment.hpp"

namespace environment {
	/**
	 * add/applicate element into/to stack
	 */
	model::Stack& elem_interpret(const model::sp_Element& elem, model::Stack& stack) {
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

	//////////////////////////
	// NameSpace

	bool NameSpace::add(const std::string& name, model::sp_Element object) {
		if (table.find(name) != table.end()) {
			table[name] = object;
			return true;
		}

		return false;
	}

	model::sp_Element NameSpace::get_elem(const std::string& name) {
		model::sp_Element& elem = this->table.at(name);
		return (not elem->instance_of<NameSpace>()) ? elem : nullptr;
	}

	std::shared_ptr<NameSpace> NameSpace::get_ns(const std::string& name) {
		return std::dynamic_pointer_cast<NameSpace>(this->table.at(name));
	}

} // namespace environment
