#include <iostream>
#include <list>

extern "C" {
	namespace editline {
		#include <editline/readline.h>
	} // namespace editline
}

#include "model.hpp"
#include "scanner.hpp"
#include "tokenizer.hpp"
#include "environment.hpp"


int main() {
	// REPL
	char* cstr_input;
	std::string input;
	environment::GlobalObject global;

	editline::using_history();

	while (true) {
		cstr_input = editline::readline("Input> ");
		editline::add_history(cstr_input);
		input = cstr_input;

		global.evaluate(input);

		std::cout << "Data Stack:"; // << loadstack.front()->to_string();
		for (auto&& stack : global.loadstack) {
			std::string stack_str = stack->to_string();

			std::cout << stack_str.substr((global.loadstack.front() == stack) ? 1 : 0, stack_str.length() - 2);
		}
		std::cout << std::endl;
	}

	return 0;
}
