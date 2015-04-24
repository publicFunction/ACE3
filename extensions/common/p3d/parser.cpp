#pragma once

#include "p3d/parser.hpp"

namespace ace {
    namespace p3d {
        parser::parser() { }
        parser::~parser() { }

        model * parser::load(const std::string &filepath) {
            std::fstream filestream;
            model * _model = nullptr;

            filestream.open(filepath, std::ios::binary | std::ios::in);
            if (!filestream.good()) {
                LOG(ERROR) << "Cannot open file";
                return _model;
            }

            _model = new model(filestream, filepath);
            
            return _model;
        }
    }
}

