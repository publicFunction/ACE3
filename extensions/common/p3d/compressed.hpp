#pragma once

#include "shared.hpp"
#include "vector.hpp"

#include "read_helpers.hpp"


namespace ace {
    namespace p3d {
        class _compressed_base {
        protected:
            int _mikero_lzo1x_decompress_safe(const uint8_t*, uint8_t*, uint32_t);
            int _decompress_safe(std::istream &, uint32_t);
            std::unique_ptr<uint8_t[]> _data;
        };
        template<typename T>
        class compressed_base : public _compressed_base {
        public:
            compressed_base() : fill(false), size(0) {}

            T & operator[] (const int index) { return data[index]; }

            uint32_t          size;
            bool              fill;
            std::vector<T>    data;
        };

        template<typename T>
        class compressed : public compressed_base<T> {
        public:
            compressed() { }
            compressed(std::istream &stream_, bool compressed_ = false, bool fill_ = false)  {
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
                        if (size * sizeof(T) >= 1024 && compressed_) {
                            int32_t result = _decompress_safe(stream_, size * sizeof(T));
                            T * ptr = (T *)(_data.get());
                            data.assign(ptr, ptr + size );
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
        };

        template<>
        class compressed<vector3<float>> : public compressed_base<vector3<float>>{
        public:
            compressed()  {}
            compressed(std::istream &stream_, bool compressed_ = false, bool fill_ = false, bool xyzCompressed = false) {
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
                    if (size * (sizeof(float) * 3) >= 1024 && compressed_) {
                        if (xyzCompressed) {
                            int32_t result = _decompress_safe(stream_, size * sizeof(float));
                            uint32_t * ptr = (uint32_t *)(_data.get());
                            for (int x = 0; x < size; x++) {
                                uint32_t value = ptr[x];
                                data.push_back(decode_xyz(value));
                            }
                        } else {
                            int32_t result = _decompress_safe(stream_, size * sizeof(float) * 3);
                            float * ptr = (float *)(_data.get());
                            for (int x = 0; x < size*3; x+=3) {
                                data.push_back(ace::vector3<float>(ptr+x));
                            }
                        }
                    } else {
                        for (int x = 0; x < size; x++) {
                            data.push_back(ace::vector3<float>(stream_));
                        }
                    }
                }
            }

            ace::vector3<float> decode_xyz(uint32_t CompressedXYZ)
            {
                double scaleFactor = -1.0 / 511;

                int x = CompressedXYZ & 0x3FF;
                int y = (CompressedXYZ >> 10) & 0x3FF;
                int z = (CompressedXYZ >> 20) & 0x3FF;
                if (x > 511) x -= 1024;
                if (y > 511) y -= 1024;
                if (z > 511) z -= 1024;

                return ace::vector3<float>(x * scaleFactor, y * scaleFactor, z * scaleFactor);
            }
        };

        template<>
        class compressed<ace::pair<float>> : public compressed_base<ace::pair<float>>{
        public:
            compressed() {}
            compressed(std::istream &stream_, bool compressed_ = false, bool fill_ = false) {
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
                    if (size * (sizeof(float) * 2) > 1024 && compressed_) {
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
        };
    }
}