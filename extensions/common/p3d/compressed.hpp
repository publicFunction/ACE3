#pragma once

#include "ace_common.h"
#include "vector.hpp"

#include "minilzo.h"
#include "read_helpers.hpp"

#include <limits.h>
#include <stddef.h>
#include <limits.h>
#include <stddef.h>
#include <string.h>
#include <malloc.h>

#define __lzo_assert(val) if (!(val)) return LZO_E_ERROR
#define M2_MAX_OFFSET   0x0800

#define NEED_OP(x)  if ((unsigned)(op_end - op) < (unsigned)(x)) return LZO_E_OUTPUT_OVERRUN;
#define TEST_LB()   if (m_pos < out || m_pos >= op) return LZO_E_LOOKBEHIND_OVERRUN;

#define COPY4(dst,src)    * (unsigned *)(dst) = * (const unsigned *)(src)

namespace ace {
    namespace p3d {
        class compressed_base {
        protected:
            int _lzo1x_decompress_safe(const uint8_t* in, uint8_t* out, unsigned OutLen)  {
                register uint8_t* op;
                register const uint8_t* ip;
                register size_t t;
                register const uint8_t* m_pos;

                uint8_t* const op_end = out + OutLen;

                OutLen = 0;
                op = out;
                ip = in;

                if (*ip > 17)
                {
                    t = *ip++ - 17;
                    if (t < 4) goto match_next;
                    __lzo_assert(t > 0);// return LZO_E_ERROR;
                    NEED_OP(t);
                    do *op++ = *ip++; while (--t > 0);
                    goto first_literal_run;
                }

                while (1)
                {
                    t = *ip++;
                    if (t >= 16)           goto match;
                    if (t == 0)
                    {
                        while (*ip == 0)
                        {
                            t += 255;
                            ip++;
                        }
                        t += 15 + *ip++;
                    }
                    __lzo_assert(t > 0); NEED_OP(t + 3);

                    COPY4(op, ip);
                    op += 4; ip += 4;
                    if (--t > 0)
                    {
                        if (t >= 4)
                        {
                            do {
                                COPY4(op, ip);
                                op += 4; ip += 4; t -= 4;
                            } while (t >= 4);
                            if (t > 0) do *op++ = *ip++; while (--t > 0);
                        }
                        else
                            do *op++ = *ip++; while (--t > 0);
                    }

                first_literal_run:

                    t = *ip++;
                    if (t >= 16)  goto match;

                    m_pos = op - (1 + M2_MAX_OFFSET);
                    m_pos -= t >> 2;
                    m_pos -= *ip++ << 2;

                    TEST_LB();
                    NEED_OP(3);
                    *op++ = *m_pos++; *op++ = *m_pos++; *op++ = *m_pos;

                    goto match_done;

                    do {
                    match:
                        if (t >= 64)
                        {

                            m_pos = op - 1;
                            m_pos -= (t >> 2) & 7;
                            m_pos -= *ip++ << 3;
                            t = (t >> 5) - 1;
                            TEST_LB();     __lzo_assert(t > 0); NEED_OP(t + 3 - 1);
                            goto copy_match;
                        }
                        else if (t >= 32)
                        {
                            t &= 31;
                            if (t == 0)
                            {
                                while (*ip == 0)
                                {
                                    t += 255;
                                    ip++;
                                }
                                t += 31 + *ip++;
                            }

                            m_pos = op - 1;
                            m_pos -= (ip[0] >> 2) + (ip[1] << 6);

                            ip += 2;
                        }
                        else if (t >= 16)
                        {

                            m_pos = op;
                            m_pos -= (t & 8) << 11;

                            t &= 7;
                            if (t == 0)
                            {
                                while (*ip == 0)
                                {
                                    t += 255;
                                    ip++;
                                }
                                t += 7 + *ip++;
                            }

                            m_pos -= (ip[0] >> 2) + (ip[1] << 6);

                            ip += 2;
                            ////// done
                            if (m_pos == op)
                            {
                                __lzo_assert(t == 1);
                                if (m_pos != op_end) {
                                    assert(true);
                                    return -1;
                                }
                                return ip - in;
                            }
                            m_pos -= 0x4000;
                        }
                        else
                        {
                            m_pos = op - 1;
                            m_pos -= t >> 2;
                            m_pos -= *ip++ << 2;

                            TEST_LB();
                            NEED_OP(2);
                            *op++ = *m_pos++; *op++ = *m_pos;
                            goto match_done;
                        }

                        TEST_LB();
                        __lzo_assert(t > 0);
                        NEED_OP(t + 3 - 1);

                        if (t >= 2 * 4 - (3 - 1) && (op - m_pos) >= 4)
                        {
                            COPY4(op, m_pos);
                            op += 4; m_pos += 4; t -= 4 - (3 - 1);
                            do {
                                COPY4(op, m_pos);
                                op += 4; m_pos += 4; t -= 4;
                            } while (t >= 4);
                            if (t > 0) do *op++ = *m_pos++; while (--t > 0);
                        }
                        else
                        {
                        copy_match:
                            *op++ = *m_pos++; *op++ = *m_pos++;

                            do *op++ = *m_pos++; while (--t > 0);

                        }
                    match_done:

                        t = ip[-2] & 3;
                        if (t == 0)   break;
                    match_next:
                        __lzo_assert(t > 0); __lzo_assert(t < 4); NEED_OP(t);
                        *op++ = *ip++;
                        if (t > 1) { *op++ = *ip++; if (t > 2) { *op++ = *ip++; } }

                        t = *ip++;
                    } while (1);
                }
                //    return LZO_E_EOF_NOT_FOUND;/never gets here
            }
        };

        template<typename T>
        class compressed : public compressed_base {
        public:
            compressed() : fill(false), size(0) { }
            compressed(std::fstream &stream_, bool compressed_ = false, bool fill_ = false) : fill(false), size(0) {
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
                            assert(true);
                           // this->_lzo1x_decompress_safe()

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
            compressed(std::fstream &stream_, bool compressed_ = false, bool fill_ = false) : fill(false), size(0) {
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
            compressed(std::fstream &stream_, bool compressed_ = false, bool fill_ = false) : fill(false), size(0) {
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