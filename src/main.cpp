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
	for (auto& it : stack3) {
		std::cout << it->to_string() << std::endl;
	}

	return 0;
}
