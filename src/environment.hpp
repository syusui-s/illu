#pragma once

#include <iostream>

#include "model.hpp"

namespace environment {
	model::Stack& elem_interpret(model::Element* elem, model::Stack& stack);
} // namespace environment
