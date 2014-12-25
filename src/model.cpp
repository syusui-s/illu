#include "model.hpp"
#include "environment.hpp"

/**
 * namespace model
 * defined several sp_Elements
 */
namespace model {
	//////////////////////////
	// Integer

	/**
	 * Convert Integer to String
	 *
	 * @return std::string
	 */
	std::string Integer::to_string() const {
		std::stringstream ss;
		ss << this->data;

		return ss.str();
	}

	/**
	 * Add this data and other data
	 *
	 * @return std::string
	 */
	sp_Element Integer::add(const sp_Element& other) {
		sp_Element rtn;

		if (other->instance_of<Integer>()) {
			rtn = std::make_shared<Integer>( data + other->cast<Integer>()->data );
		} else if (other->instance_of<Float>()) {
			rtn = std::make_shared<Float>(static_cast<Float::TYPE>(data) + other->cast<Float>()->data );
		// } else if (other.instance_of<>)
		} else {
			throw "UnexpectedTypeError";
		}

		return rtn;
	}

	/**
	 * Sub this data and other data
	 *
	 * @return std::string
	 */
	sp_Element Integer::sub(const sp_Element& other) {
		sp_Element rtn;

		if (other->instance_of<Integer>()) {
			rtn = std::make_shared<Integer>( data - other->cast<Integer>()->data );
		} else if (other->instance_of<Float>()) {
			rtn = std::make_shared<Float>(static_cast<Float::TYPE>(data) - other->cast<Float>()->data );
		// } else if (other.instance_of<>) {
		} else {
			throw "UnexpectedTypeError";
		}

		return rtn;
	}

	/**
	 * applicate mutliplication
	 */
	sp_Element Integer::mul(const sp_Element& other) {
		sp_Element rtn;

		if (other->instance_of<Integer>()) {
			rtn = std::make_shared<Integer>( data * other->cast<Integer>()->data );
		} else if (other->instance_of<Float>()) {
			rtn = std::make_shared<Float>( data * other->cast<Float>()->data );
		// } else if (other.instance_of<>)
		} else {
			throw "UnexpectedTypeError";
		}

		return rtn;
	}

	/**
	 * applicate division
	 */
	sp_Element Integer::div(const sp_Element& other) {
		sp_Element rtn;

		if (other->instance_of<Integer>()) {
			rtn = std::make_shared<Integer>( data / other->cast<Integer>()->data );
		} else if (other->instance_of<Float>()) {
			rtn = std::make_shared<Float>( data / other->cast<Float>()->data );
		// } else if (other.instance_of<>)
		} else {
			throw "UnexpectedTypeError";
		}

		return rtn;
	}

	//////////////////////////
	// Float

	/**
	 * Convert Float to String
	 */
	std::string Float::to_string() const {
		std::stringstream ss;
		ss << this->data;

		return ss.str();
	}
	/**
	 * applicate addtion
	 */
	sp_Element Float::add(const sp_Element& other) {
		sp_Element rtn;

		if (other->instance_of<Float>()) {
			rtn = std::make_shared<Float>( data + other->cast<Float>()->data );
		} else if (other->instance_of<Integer>()) {
			rtn = std::make_shared<Float>( data + other->cast<Integer>()->data );
		// } else if (other.instance_of<>)
		} else {
			throw "UnexpectedTypeError";
		}

		return rtn;
	}

	/**
	 * applicate subtruction
	 */
	sp_Element Float::sub(const sp_Element& other) {
		sp_Element rtn;

		if (other->instance_of<Float>()) {
			rtn = std::make_shared<Float>( data - other->cast<Float>()->data );
		} else if (other->instance_of<Integer>()) {
			rtn = std::make_shared<Float>( data - other->cast<Integer>()->data );
		// } else if (other.instance_of<>)
		} else {
			throw "UnexpectedTypeError";
		}

		return rtn;
	}

	/**
	 * applicate mutliplication
	 */
	sp_Element Float::mul(const sp_Element& other) {
		sp_Element rtn;

		if (other->instance_of<Float>()) {
			rtn = std::make_shared<Float>( data * other->cast<Float>()->data );
		} else if (other->instance_of<Integer>()) {
			rtn = std::make_shared<Float>( data * other->cast<Integer>()->data );
		// } else if (other.instance_of<>)
		} else {
			throw "UnexpectedTypeError";
		}

		return rtn;
	}

	/**
	 * applicate division
	 */
	sp_Element Float::div(const sp_Element& other) {
		sp_Element rtn;

		if (other->instance_of<Float>()) {
			rtn = std::make_shared<Float>( data / other->cast<Float>()->data );
		} else if (other->instance_of<Integer>()) {
			rtn = std::make_shared<Float>( data / other->cast<Integer>()->data );
		// } else if (other.instance_of<>)
		} else {
			throw "UnexpectedTypeError";
		}

		return rtn;
	}

	//////////////////////////
	// String
	std::string String::to_string() const {
		return "\"" + this->data + "\"";
	}

	/**
	 * Add this data and other data
	 */
	sp_Element String::add(const sp_Element& other) {
		sp_Element rtn;

		if (other->instance_of<String>()) {
			rtn = std::make_shared<String>( data + other->cast<String>()->data );
		} else {
			throw "UnexpectedTypeError";
		}

		return rtn;
	}

	//////////////////////////
	// Nil
	std::string Nil::to_string() const {
		return "nil";
	}

	//////////////////////////
	// Boolean
	std::string Boolean::to_string() const {
		return this->data ? "true" : "false";
	}

	//////////////////////////
	// Symbol
	std::string Symbol::to_string() const {
		return ":" + this->data;
	}

	//////////////////////////
	// Identifier
	std::string Identifier::to_string() const {
		return this->data;
	}

	//////////////////////////
	// Instruction
	
	/**
	 * Functions map
	 */
	const std::map<tokenizer::TokenType, Instruction::S_Instruction> Instruction::instructions = {
		{ tokenizer::TokenType::INST_PLUS,            { Instruction::add,     2, "+" } },
		{ tokenizer::TokenType::INST_MINUS,           { Instruction::sub,     2, "-" } },
		{ tokenizer::TokenType::INST_MULTIPLICATION,  { Instruction::mul,     2, "*" } },
		{ tokenizer::TokenType::INST_DIVISION,        { Instruction::div,     2, "/" } },
		{ tokenizer::TokenType::INST_DROP,            { Instruction::drop,    1, "drop" } },
		{ tokenizer::TokenType::INST_IF,              { Instruction::if_func, 3, "if" } },
	};
	
	/**
	 * returns string expression of Instruction
	 *
	 * @return std::string
	 */
	std::string Instruction::to_string() const {
		return this->instructions.at(toktype).string_expression;
	}

	/**
	 * returns number of arguments
	 *
	 * @return size_t Number of Arguments
	 */
	size_t Instruction::num_of_args() const {
		return this->instructions.at(toktype).num_of_args;
	}

	/**
	 * applicate instruction
	 */
	Stack& Instruction::applicate(Stack& stack) {
		return this->instructions.at(toktype).pfunc(stack);
	}

	/**
	 * applicate addition
	 *
	 * @param  Stack& stack which will be applicated
	 * @return Stack&
	 */
	Stack& Instruction::add(Stack& stack) {
		sp_Element arg1, arg2, result;
		
		arg2 = stack.pop();
		arg1 = stack.pop();
		result = nullptr;

		if (arg1->instance_of<Integer>()) {
			result = arg1->cast<Integer>()->add(arg2);
		} else if (arg1->instance_of<Float>()) {
			result = arg1->cast<Float>()->add(arg2);
		} else if (arg1->instance_of<String>()) {
			result = arg1->cast<String>()->add(arg2);
		} else if (arg1->instance_of<Stack>()) {
			// TODO: stack must be immutable
			if (! arg2->instance_of<Stack>()) throw "UnexpectedTypeError";
			*arg1->cast<Stack>() += *arg2->cast<Stack>();
			stack.push(arg1);
			return stack;
		}

		stack.push(result);
		return stack;
	}

	/**
	 * applicate substruction
	 *
	 * @param  Stack& stack which will be applicated
	 * @return Stack&
	 */
	Stack& Instruction::sub(Stack& stack) {
		sp_Element arg1, arg2, result;
		
		arg2 = stack.pop();
		arg1 = stack.pop();
		result = nullptr;

		if (arg1->instance_of<Integer>()) {
			result = arg1->cast<Integer>()->sub(arg2);
		} else if (arg1->instance_of<Float>()) {
			result = arg1->cast<Float>()->sub(arg2);
		}

		stack.push(result);

		return stack;
	}

	/**
	 * applicate mutliplication
	 *
	 * @param  Stack& stack which will be applicated
	 * @return Stack&
	 */
	Stack& Instruction::mul(Stack& stack) {
		sp_Element arg1, arg2, result;

		arg2 = stack.pop();
		arg1 = stack.pop();
		result = nullptr;

		if (arg1->instance_of<Integer>()) {
			result = arg1->cast<Integer>()->mul(arg2);
		} else if (arg1->instance_of<Float>()) {
			result = arg1->cast<Float>()->mul(arg2);
		} else {
			throw "UnexpectedTypeError";
		}

		stack.push(result);

		return stack;
	}

	/**
	 * applicate divison
	 *
	 * @param  Stack& stack which will be applicated
	 * @return Stack&
	 */
	Stack& Instruction::div(Stack& stack) {
		sp_Element arg1, arg2, result;
		
		arg2 = stack.pop();
		arg1 = stack.pop();
		result = nullptr;

		if (arg1->instance_of<Integer>()) {
			result = arg1->cast<Integer>()->div(arg2);
		} else if (arg1->instance_of<Float>()) {
			result = arg1->cast<Float>()->div(arg2);
		} else {
			throw "UnexpectedTypeError";
		}


		stack.push(result);

		return stack;
	}

	/**
	 * drop sp_Element
	 *
	 * @param  Stack& stack which will be applicated
	 * @return Stack&
	 */
	Stack& Instruction::drop(Stack& stack) {
		stack.pop();
		return stack;
	}

	/**
	 * if control instruction
	 *
	 * @param  Stack& stack which will be applicated
	 * @return Stack&
	 */
	Stack& Instruction::if_func(Stack& stack) {
		sp_Element true_stack, false_stack, bool_elem;

		false_stack = stack.pop();
		true_stack  = stack.pop();
		bool_elem   = stack.pop();

		if (true_stack->instance_of<Stack>() && false_stack->instance_of<Stack>() && bool_elem->instance_of<Boolean>()) {
			Stack tmp_data_stack;
			Stack* exec_stack = (bool_elem->cast<Boolean>()->data ? true_stack : false_stack)->cast<Stack>();

			for (auto elem : *exec_stack) {
				environment::elem_interpret(elem, tmp_data_stack);
			}

			if (tmp_data_stack.size() > 0) {
				stack.push(tmp_data_stack.pop());
			}
		}

		return stack;
	}

	//////////////////////////
	// Stack Class

	/**
	 * convert Stack to String
	 *
	 * @return std::string
	 */
	std::string Stack::to_string() const {
		std::string str("[ ");

		for (auto iterator : *this) {
			str += iterator->to_string() + " ";
		}
		str += "]";

		return str;
	}

	/**
	 * Push sp_Element
	 *
	 * @param sp_Element* Address of sp_Element which is pushed
	 */
	void Stack::push(sp_Element data) {
		this->push_back(data);
		return;
	}

	/**
	 * Drop sp_Element
	 * Pop and delete sp_Element
	 */
	void Stack::drop() {
		sp_Element data;

		data = this->back();
		this->pop_back();

		return;
	}

	/**
	 * Pop and get sp_Element
	 * Does not delete
	 *
	 * @return sp_Element* Popped sp_Element
	 */
	sp_Element Stack::pop() {
		sp_Element rtn;

		rtn = this->back();
		this->pop_back();

		return rtn;
	}

	/**
	 * Free Unused Memory
	 */
	void Stack::free_memory() {
		Stack swp = *this;
		this->swap(swp);

		return;
	}
	
	/**
	 * Appends the other Stack to self
	 *
	 * @param Stack& other
	 * @return Stack&
	 */
	Stack& Stack::operator+=(Stack& other) {
		this->insert(this->end(), other.begin(), other.end());

		return *this;
	}
} // namespace model
