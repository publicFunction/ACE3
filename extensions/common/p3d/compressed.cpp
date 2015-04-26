#include "compressed.hpp"
#include "minilzo.h"

namespace ace {
    namespace p3d {
        /*lzo1x_decompress_safe   ( const lzo_bytep src, lzo_uint  src_len,
                                lzo_bytep dst, lzo_uintp dst_len,
                                lzo_voidp wrkmem  ) */
        int _decompress_safe(std::istream &in, uint8_t* out, unsigned expected_size) {
            // We read 512 bytes at a time, until we have hit the end of the compressed stream
            uint8_t     buffer[512];
            uint32_t    bytesOut = 0;
            uint32_t    bytesConsumedIn = 0;
            uint32_t    iter_size = 0;
            uint32_t    iter_input_size = 0;
            std::streampos   save_pos;

            save_pos = in.tellg();

            while (bytesOut != expected_size) {
                in.read((char *)buffer, 512);
                iter_input_size = in.gcount();
                bytesConsumedIn += iter_input_size;
                
                lzo1x_decompress_safe(buffer, iter_input_size, out+bytesOut, (lzo_uint *)&iter_size, NULL);

                bytesOut += iter_size;
            }
            save_pos += bytesConsumedIn;
            in.seekg(save_pos);

            return bytesOut;
        }
    }
}

