#pragma once

#include <iostream>
#include <string>
#include <map>
#include <memory>

#include "tokenizer.hpp"
#include "model.hpp"

namespace environment {

	class NameSpace : public model::Element {
		private:
			std::map<std::string, model::sp_Element> table;
		public:
			NameSpace(){}
			~NameSpace(){};
			std::string to_string() const override { return ""; }

			bool add(const std::string& name, model::sp_Element object);
			model::sp_Element get_elem(const std::string& name);
			std::shared_ptr<NameSpace> get_ns(const std::string& name);
	};

	/**
	 * StackFrame
	 * represents StackFrame in Stack Area.
	 * This is created when Function is called.
	 * StackFrame has local variables and a local stack;
	 */
	struct StackFrame {
		NameSpace ns;
		model::Stack stack;
	};

	/**
	 * FrameList
	 */
	class GlobalObject {
		private:

		public:
		std::list<std::shared_ptr<model::Stack>> loadstack = {};
		std::shared_ptr<model::Stack> laststack = nullptr;

		GlobalObject() {
			this->loadstack.push_back(std::make_shared<model::Stack>());
		}
		void evaluate(std::string& input);
	};

	model::Stack& elem_interpret(const model::sp_Element& elem, model::Stack& stack);
} // namespace environment
