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
	std::list<model::Stack*> loadstack;
	model::Stack* laststack;

	loadstack.push_back(new model::Stack);

	editline::using_history();

	while (true) {
		cstr_input = editline::readline("Input> ");
		editline::add_history(cstr_input);
		input = cstr_input;

		lexer::Tokenizer* p_tokenizer = new lexer::Tokenizer(input);

		while (p_tokenizer->read_next()) {
			lexer::Token tok = p_tokenizer->current_token();
			model::Element* elem = tok.to_element();

			switch (tok.type) {
				// Stack
				case tokentype::T_STACK_START:
					loadstack.push_back(new model::Stack);
					break;
				case tokentype::T_STACK_END:
					laststack = loadstack.back();
					loadstack.pop_back();
					loadstack.back()->push(laststack);
					break;
				default:
					if (elem == NULL) {
						// generally this error stops this program,
						// but I'll keep it for debug until exception function is implemented.
						std::cerr << "Unknown TokenType" << std::endl;
						while (p_tokenizer->read_next()) {}
					} else if (loadstack.back() != loadstack.front()) {
						loadstack.back()->push_back(elem);
					} else {
						environment::elem_interpret(elem, *loadstack.back());
					}
			}
		}
		delete p_tokenizer;

		std::cout << "Data Stack: " << loadstack.front()->to_string() << std::endl;
	}

	return 0;
}
