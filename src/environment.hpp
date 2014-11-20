#pragma once

#include <iostream>
#include <memory>

#include "model.hpp"

namespace environment {
	model::Stack& elem_interpret(const model::sp_Element& elem, model::Stack& stack);
} // namespace environment
