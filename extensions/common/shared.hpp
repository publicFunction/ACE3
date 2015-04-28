#pragma once

#include "targetver.h"
#include <assert.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <memory>
#include <cmath>
#include <cstdint>
#include <streambuf>

#include "logging.hpp"

namespace ace {
    template< typename T >
    struct array_deleter
    {
        void operator ()(T const * p)
        {
            delete[] p;
        }
    };

    std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
    std::vector<std::string> split(const std::string &s, char delim);
}