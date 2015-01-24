#pragma once

#include <iostream>
#include <map>

#include "model.hpp"

namespace environment {
	model::Stack& elem_interpret(const model::sp_Element& elem, model::Stack& stack);

	class NameSpace : public model::Element {
		private:
			std::map<std::string, model::sp_Element> table;
		public:
			NameSpace(){}
			~NameSpace(){};

			bool add(const std::string name, model::sp_Element object);
			model::sp_Element get_elem(const std::string name);
	};
} // namespace environment
