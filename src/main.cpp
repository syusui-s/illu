#include <iostream>

#include "model.hpp"
#include "scanner.hpp"
#include "tokenizer.hpp"

int main()
{
	// REPL
	std::string input;
	model::Stack stack5;
	lexer::TokenVector tokvec;

	while (true) {
		std::cout << "Input> ";
		std::getline(std::cin, input);

		lexer::Tokenizer* p_tokenizer = new lexer::Tokenizer(input);
		tokvec = p_tokenizer->tokenize();

		for (auto& tok : tokvec) {
			switch (tok.type) {
				// Instruction: Basic Operations
				case tokentype::T_INST_PLUS:
				case tokentype::T_INST_MINUS:
				case tokentype::T_INST_MULTIPLICATION:
				case tokentype::T_INST_DIVISION:
					if (stack5.size() > 1) {
						tok.to_element()->cast<model::Instruction>()->applicate(stack5);
					} else {
						std::cout << "Cannot Applicate Instruction" << std::endl;
					}
					break;
				case tokentype::T_INST_DROP:
					if (! stack5.empty()) {
						tok.to_element()->cast<model::Instruction>()->applicate(stack5);
					} else {
						std::cout << "Cannot Applicate Instruction" << std::endl;
					}
					break;
				// Literal Data
				case tokentype::T_INTEGER:
				case tokentype::T_FLOAT:
				case tokentype::T_STRING:
				case tokentype::T_NIL:
					stack5.push(tok.to_element());
					break;
				default:
					std::cout << "Unknown TokenType" << std::endl;
			}
		}
		delete p_tokenizer;

		std::cout << "Data Stack: " << stack5.to_string() << std::endl;
	}

	return 0;
}
