#include "p3d/model.hpp"

namespace ace {
    namespace p3d {
        model::model() {
            
            // Parse header here
            

            // parse model info here


            // Read ahead because i dunno
            while (true) {
                char byte;
                stream_.read(&byte, 1);
                if (byte != -1) {
                    stream_.seekg(-1, stream_.cur);
                    break;
                };
            }
        }
        model::~model() {}
    }
}
