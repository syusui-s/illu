#include <iostream>
#include <list>

#include "model.hpp"
#include "scanner.hpp"
#include "tokenizer.hpp"

int main()
{
	// REPL
	std::string input;
	std::list<model::Stack*> loadstack;
	loadstack.push_back(new model::Stack);

	while (true) {
		std::cout << "Input> ";
		std::getline(std::cin, input);

		lexer::Tokenizer* p_tokenizer = new lexer::Tokenizer(input);

		while (p_tokenizer->read_next()) {
			lexer::Token tok = p_tokenizer->current_token();

			switch (tok.type) {
				// Instruction: Basic Operations
				case tokentype::T_INST_PLUS:
				case tokentype::T_INST_MINUS:
				case tokentype::T_INST_MULTIPLICATION:
				case tokentype::T_INST_DIVISION:
					if (loadstack.back()->size() > 1) {
						tok.to_element()->cast<model::Instruction>()->applicate(*loadstack.back());
					} else {
						std::cerr << "Cannot Applicate Instruction : too few arguments" << std::endl;
					}
					break;
				// Instruction: Stack Operations
				case tokentype::T_INST_DROP:
					if (! loadstack.back()->empty()) {
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

		std::cout << "Data Stack: " << loadstack.back()->to_string() << std::endl;
	}

	return 0;
}
