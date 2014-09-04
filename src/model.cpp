#include "model.hpp"

/**
 * namespace model
 * defined several Elements
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
	Element* Integer::add(Element *other) {
		Element* rtn;

		if (other->instance_of<Integer>()) {
			rtn = new Integer( data + other->cast<Integer>()->get_data() );
		} else if (other->instance_of<Float>()) {
			rtn = new Float(static_cast<Float::TYPE>(data) + other->cast<Float>()->get_data() );
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
	Element* Integer::sub(Element *other) {
		Element* rtn;

		if (other->instance_of<Integer>()) {
			rtn = new Integer( data - other->cast<Integer>()->get_data() );
		} else if (other->instance_of<Float>()) {
			rtn = new Float(static_cast<Float::TYPE>(data) - other->cast<Float>()->get_data() );
		// } else if (other.instance_of<>) {
		} else {
			throw "UnexpectedTypeError";
		}

		return rtn;
	}

	/**
	 * applicate mutliplication
	 */
	Element* Integer::mul(Element *other) {
		Element* rtn;

		if (other->instance_of<Integer>()) {
			rtn = new Integer( data * other->cast<Integer>()->get_data() );
		} else if (other->instance_of<Float>()) {
			rtn = new Float( data * other->cast<Float>()->get_data() );
		// } else if (other.instance_of<>)
		} else {
			throw "UnexpectedTypeError";
		}

		return rtn;
	}

	/**
	 * applicate division
	 */
	Element* Integer::div(Element *other) {
		Element* rtn;

		if (other->instance_of<Integer>()) {
			rtn = new Integer( data / other->cast<Integer>()->get_data() );
		} else if (other->instance_of<Float>()) {
			rtn = new Float( data / other->cast<Float>()->get_data() );
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
	Element* Float::add(Element *other) {
		Element* rtn;

		if (other->instance_of<Float>()) {
			rtn = new Float( data + other->cast<Float>()->get_data() );
		} else if (other->instance_of<Integer>()) {
			rtn = new Float( data + other->cast<Integer>()->get_data() );
		// } else if (other.instance_of<>)
		} else {
			throw "UnexpectedTypeError";
		}

		return rtn;
	}

	/**
	 * applicate subtruction
	 */
	Element* Float::sub(Element *other) {
		Element* rtn;

		if (other->instance_of<Float>()) {
			rtn = new Float( data - other->cast<Float>()->get_data() );
		} else if (other->instance_of<Integer>()) {
			rtn = new Float( data - other->cast<Integer>()->get_data() );
		// } else if (other.instance_of<>)
		} else {
			throw "UnexpectedTypeError";
		}

		return rtn;
	}

	/**
	 * applicate mutliplication
	 */
	Element* Float::mul(Element *other) {
		Element* rtn;

		if (other->instance_of<Float>()) {
			rtn = new Float( data * other->cast<Float>()->get_data() );
		} else if (other->instance_of<Integer>()) {
			rtn = new Float( data * other->cast<Integer>()->get_data() );
		// } else if (other.instance_of<>)
		} else {
			throw "UnexpectedTypeError";
		}

		return rtn;
	}

	/**
	 * applicate division
	 */
	Element* Float::div(Element *other) {
		Element* rtn;

		if (other->instance_of<Float>()) {
			rtn = new Float( data / other->cast<Float>()->get_data() );
		} else if (other->instance_of<Integer>()) {
			rtn = new Float( data / other->cast<Integer>()->get_data() );
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
	Element* String::add(Element *other) {
		Element* rtn;

		if (other->instance_of<String>()) {
			rtn = new String( data + other->cast<String>()->get_data() );
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
	const std::map<tokentype::Type, Instruction::S_Instruction> Instruction::instructions = {
		{ tokentype::T_INST_PLUS,            { Instruction::add,  2, "+" } },
		{ tokentype::T_INST_MINUS,           { Instruction::sub,  2, "-" } },
		{ tokentype::T_INST_MULTIPLICATION,  { Instruction::mul,  2, "*" } },
		{ tokentype::T_INST_DIVISION,        { Instruction::div,  2, "/" } },
		{ tokentype::T_INST_DROP,            { Instruction::drop, 1, "drop" } },
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
		Element *arg1, *arg2, *result;
		
		arg2 = stack.pop();
		arg1 = stack.pop();
		result = NULL;

		if (arg1->instance_of<Integer>()) {
			result = arg1->cast<Integer>()->add(arg2);
		} else if (arg1->instance_of<Float>()) {
			result = arg1->cast<Float>()->add(arg2);
		} else if (arg1->instance_of<String>()) {
			result = arg1->cast<String>()->add(arg2);
		} else if (arg1->instance_of<Stack>()) {
			if (! arg2->instance_of<Stack>()) throw "UnexpectedTypeError";
			*arg1->cast<Stack>() += *arg2->cast<Stack>();
			stack.push(arg1);
			delete arg2;
			return stack;
		}

		stack.push(result);

		delete arg1;
		delete arg2;

		return stack;
	}

	/**
	 * applicate substruction
	 *
	 * @param  Stack& stack which will be applicated
	 * @return Stack&
	 */
	Stack& Instruction::sub(Stack& stack) {
		Element *arg1, *arg2, *result;
		
		arg2 = stack.pop();
		arg1 = stack.pop();
		result = NULL;

		if (arg1->instance_of<Integer>()) {
			result = arg1->cast<Integer>()->sub(arg2);
		} else if (arg1->instance_of<Float>()) {
			result = arg1->cast<Float>()->sub(arg2);
		}

		stack.push(result);

		delete arg1;
		delete arg2;

		return stack;
	}

	/**
	 * applicate mutliplication
	 *
	 * @param  Stack& stack which will be applicated
	 * @return Stack&
	 */
	Stack& Instruction::mul(Stack& stack) {
		Element *arg1, *arg2, *result;
		
		arg2 = stack.pop();
		arg1 = stack.pop();
		result = NULL;

		if (arg1->instance_of<Integer>()) {
			result = arg1->cast<Integer>()->mul(arg2);
		} else if (arg1->instance_of<Float>()) {
			result = arg1->cast<Float>()->mul(arg2);
		}

		stack.push(result);

		delete arg1;
		delete arg2;

		return stack;
	}

	/**
	 * applicate divison
	 *
	 * @param  Stack& stack which will be applicated
	 * @return Stack&
	 */
	Stack& Instruction::div(Stack& stack) {
		Element *arg1, *arg2, *result;
		
		arg2 = stack.pop();
		arg1 = stack.pop();
		result = NULL;

		if (arg1->instance_of<Integer>()) {
			result = arg1->cast<Integer>()->div(arg2);
		} else if (arg1->instance_of<Float>()) {
			result = arg1->cast<Float>()->div(arg2);
		}

		stack.push(result);

		delete arg1;
		delete arg2;

		return stack;
	}

	/**
	 * drop element
	 *
	 * @param  Stack& stack which will be applicated
	 * @return Stack&
	 */
	Stack& Instruction::drop(Stack& stack) {
		delete stack.pop();
		return stack;
	}

	//////////////////////////
	// Stack Class

	/**
	 * convert Stack to String
	 *
	 * @return std::string
	 */
	std::string Stack::to_string() const
	{
		std::string str("[ ");

		for (auto iterator : *this) {
			str += iterator->to_string() + " ";
		}
		str += "]";

		return str;
	}

	/**
	 * Push Element
	 *
	 * @param Element* Address of Element which is pushed
	 */
	void Stack::push(Element* data)
	{
		this->push_back(data);
		return;
	}

	/**
	 * Drop Element
	 * Pop and delete Element
	 */
	void Stack::drop()
	{
		Element *data;

		data = this->back();
		delete data;
		this->pop_back();
		return;
	}

	/**
	 * Pop and get Element
	 * Does not delete
	 *
	 * @return Element* Popped Element
	 */
	Element* Stack::pop()
	{
		Element* rtn;

		rtn = this->back();
		this->pop_back();

		return rtn;
	}

	/**
	 * Free Unused Memory
	 */
	void Stack::free_memory()
	{
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
	Stack& Stack::operator+=(Stack& other)
	{
		this->insert(this->end(), other.begin(), other.end());

		return *this;
	}
} // namespace model
