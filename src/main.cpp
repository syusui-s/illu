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

int main()
{
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
				// Instruction: Basic Operations
				case tokentype::T_INST_PLUS:
				case tokentype::T_INST_MINUS:
				case tokentype::T_INST_MULTIPLICATION:
				case tokentype::T_INST_DIVISION:
					if (loadstack.back() != loadstack.front()) {
						loadstack.back()->push(tok.to_element());
					} else if (loadstack.back()->size() > 1) {
						tok.to_element()->cast<model::Instruction>()->applicate(*loadstack.back());
					} else {
						std::cerr << "Cannot Applicate Instruction : too few arguments" << std::endl;
					}
					break;
				// Instruction: Stack Operations
				case tokentype::T_INST_DROP:
					if (loadstack.back() != loadstack.front()) {
						loadstack.back()->push(tok.to_element());
					} else if (! loadstack.back()->empty()) {
						tok.to_element()->cast<model::Instruction>()->applicate(*loadstack.back());
					} else {
						std::cerr << "Cannot Applicate Instruction : too few arguments" << std::endl;
					}
					break;
				// Literal Data
				case tokentype::T_INTEGER:
				case tokentype::T_FLOAT:
				case tokentype::T_STRING:
				case tokentype::T_NIL:
					loadstack.back()->push(tok.to_element());
					break;
				default:
					// generally this error stops this program,
					// but I'll keep it for debug until exception function is implemented.
					std::cerr << "Unknown TokenType" << std::endl;
			}
		}
		delete p_tokenizer;

		std::cout << "Data Stack: " << loadstack.front()->to_string() << std::endl;
	}

	return 0;
}
