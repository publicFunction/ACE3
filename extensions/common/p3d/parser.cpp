#pragma once

#include "p3d/parser.hpp"

namespace ace {
    namespace p3d {
        parser::parser() { }
        parser::~parser() { }

        model * parser::load(const std::string) {
            return nullptr;
        }
    }
}

