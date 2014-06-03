#include <iostream>

#include "model.hpp"
#include "scanner.hpp"
#include "tokenizer.hpp"

int main()
{
	model::Stack stack, stack2;

	stack.push(new model::Integer(1));
	stack.push(new model::Integer(2));

	stack2.push(new model::Integer(3));
	stack2.push(new model::Integer(4));

	// スタックの内容確認
	std::cout << "stack: " << stack.to_string() << std::endl;
	std::cout << "stack2: " << stack2.to_string() << std::endl;

	//////////////////
	
	// オーバーライドの確認
	model::Integer a(321);
	model::Integer b(123);

	std::cout << "321 + 123 = " << a.add(&b)->cast<model::Integer>()->get_data() << std::endl;

	// スタックの結合確認
	std::cout << "[ " << stack.to_string() << "] + [ " << stack2.to_string() << "] = ";
	stack += stack2;
	std::cout << stack.to_string() << std::endl;

	// 関数実行確認
	model::Instruction inst = model::Instruction::INST_PLUS;
	inst.applicate(stack);
	std::cout << "3 + 4 = " << stack.back()->cast<model::Integer>()->get_data() << std::endl;

	// スタックの内容確認
	/*
	stack.pop();
	stack.pop();

	int i;
	for (i = 0; i < 100; i++) {
		stack.push(new model::Integer(i));
	}
	std::cout << "stack: " << stack.to_string() << std::endl;
	for (i = 0; i < 100; i++) {
		std::cout << ((model::Integer*)(stack.pop()))->data << std::endl;
	}
	*/

	// stack1
	// std::cout << stack.at(-1) << std::endl;
	//
	
	// Lexer testing
	lexer::Tokenizer tokenizer("3 4");
	model::Stack stack3 = tokenizer.tokenize().to_stack();
	std::cout << "stack3: " << stack3.to_string() << std::endl;

	// applicate check
	lexer::Tokenizer tokenizer2("1 2 3 4 5 6 7 8 9 10");
	model::Stack stack4 = tokenizer2.tokenize().to_stack();

	std::cout << "stack4: " << stack4.to_string() << std::endl;

	while (stack4.size() > 1) {
		model::Instruction(model::Instruction::INST_PLUS).applicate(stack4);
	}

	std::cout << "stack4: " << stack4.to_string() << std::endl;

	// application
	std::string input;
	model::Stack stack5;
	lexer::TokenVector tokvec;

	while (true) {
		std::cout << std::endl << "Input> ";
		std::getline(std::cin, input);

		lexer::Tokenizer* p_tokenizer = new lexer::Tokenizer(input);
		tokvec = p_tokenizer->tokenize();

		for (auto& tok : tokvec) {
			if (tok.type == tokentype::T_INST_PLUS || tok.type == tokentype::T_INST_MINUS) {
				if (stack5.size() > 1) {
					tok.to_element()->cast<model::Instruction>()->applicate(stack5);
				} else {
					std::cout << "Cannot Applicate Instruction" << std::endl;
				}
			} else if (tok.type == tokentype::T_INTEGER || tok.type == tokentype::T_FLOAT || tok.type == tokentype::T_STRING) {
				stack5.push(tok.to_element());
			} else {
				std::cout << "Unknown TokenType" << std::endl;
			}
		}
		delete p_tokenizer;

		std::cout << "Data Stack: " << stack5.to_string() << std::endl;
	}

	return 0;
}
