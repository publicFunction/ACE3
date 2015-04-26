#pragma once

#include "ace_common.h"
#include "vector.hpp"

#include "read_helpers.hpp"

namespace ace {
    namespace p3d {
        class compressed_base {
        protected:
            int _decompress_safe(std::istream & in, uint8_t* out, unsigned OutLen);
        };

        template<typename T>
        class compressed : public compressed_base {
        public:
            compressed() : fill(false), size(0) { }
            compressed(std::istream &stream_, bool compressed_ = false, bool fill_ = false) : fill(false), size(0) {
                stream_.read((char *)&size, sizeof(uint32_t));
                
                if(fill_)
                    READ_BOOL(fill);

                assert(size < 4095 * 10);
                if (size > 0) {
                    if (fill) {
                        T val;
                        stream_.read((char *)&val, sizeof(T));
                        for (int x = 0; x < size; x++) {
                            data.push_back(val);
                        }
                    }  else {
                        if (size > 1024 && compressed_) {
                            LOG(DEBUG) << "Decompressing blob: " << size;
                            assert(false);

                        } else {
                            for (int x = 0; x < size; x++) { 
                                T val;
                                stream_.read((char *)&val, sizeof(T));
                                data.push_back(val);
                            }
                        }
                    }
                }
            }

            uint32_t          size;
            bool              fill;
            std::vector<T>    data;
        };

        template<>
        class compressed<vector3<float>> : public compressed_base{
        public:
            compressed() : fill(false), size(0) {}
            compressed(std::istream &stream_, bool compressed_ = false, bool fill_ = false) : fill(false), size(0) {
                stream_.read((char *)&size, sizeof(uint32_t));
                
                if(fill_)
                    READ_BOOL(fill);
                
                if (fill) {
                    ace::vector3<float> val(stream_);
                    for (int x = 0; x < size; x++) {
                        data.push_back(val);
                    }
                }
                else {
                    if (size > 1024 && compressed_) {
                        // DECOMPRESS IT FIRST
                        assert(false);
                    }
                    else {
                        for (int x = 0; x < size; x++) {
                            data.push_back(ace::vector3<float>(stream_));
                        }
                    }
                }
            }

            uint32_t          size;
            bool              fill;
            std::vector<ace::vector3<float>>    data;
        };

        template<>
        class compressed<ace::pair<float>> : public compressed_base{
        public:
            compressed() : fill(false), size(0) {}
            compressed(std::istream &stream_, bool compressed_ = false, bool fill_ = false) : fill(false), size(0) {
                stream_.read((char *)&size, sizeof(uint32_t));

                if (fill_)
                    READ_BOOL(fill);

                if (fill) {
                    ace::pair<float> val(stream_);
                    for (int x = 0; x < size; x++) {
                        data.push_back(val);
                    }
                }
                else {
                    if (size > 1024 && compressed_) {
                        // DECOMPRESS IT FIRST
                        assert(false);
                    }
                    else {
                        for (int x = 0; x < size; x++) {
                            data.push_back(ace::pair<float>(stream_));
                        }
                    }
                }
            }

            uint32_t          size;
            bool              fill;
            std::vector<ace::pair<float>>    data;
        };
    }
}