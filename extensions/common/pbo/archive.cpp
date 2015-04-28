#pragma once

#include "archive.hpp"
#include "p3d/read_helpers.hpp"

namespace ace {
    namespace pbo {
        
        bool      archive::get_file(std::istream &, const std::string & file, file_p output) {
            return false;
        }

        bool      archive::get_file(std::istream & stream_, const entry_p entry, file_p output) {
            uint32_t file_offset;

            std::streampos _save = stream_.tellg();
            file_offset = begin_data_offset + entry->offset;
            stream_.seekg(file_offset, stream_.beg);

            output->data = new uint8_t[entry->size];
            stream_.read((char *)output->data, entry->size);
            output->size = stream_.gcount();
            output->entry = entry;

            stream_.seekg(_save, stream_.beg);

            return true;
        }

        archive::archive() { }
        archive::archive(std::istream &stream_) {
            // Read the first entry, then info, then next entry
            uint32_t offset = 0;
            entry_p root_entry = std::make_shared<entry>(stream_);
            info = std::make_shared<ext_entry>(stream_);
            root_entry->offset = 0;
            entries.push_back(root_entry);

            entry_p next_entry = std::make_shared<entry>(stream_);
            while (next_entry->filename != "") { // off by 1006 ?!
                next_entry->offset = offset;
                entries.push_back(next_entry);
                offset += next_entry->storage_size;

                next_entry = std::make_shared<entry>(stream_);
            }
            begin_data_offset = stream_.tellg();
        }
        archive::~archive() {}

        entry::entry() {}
        entry::entry(std::istream &stream_) { 
            READ_STRING(filename);

            stream_.read((char *)&compression, sizeof(uint32_t));
            stream_.read((char *)&size, sizeof(uint32_t));
            stream_.read((char *)&reserved, sizeof(uint32_t));
            stream_.read((char *)&timestamp, sizeof(uint32_t));
            stream_.read((char *)&storage_size, sizeof(uint32_t));
        }

        ext_entry::ext_entry() {}
        ext_entry::ext_entry(std::istream &stream_) {
            READ_STRING(name);
            READ_STRING(data);
            READ_STRING(version);

            std::string temp;
            temp = version;
            
            while (temp != "") {
                extras.push_back(temp);
                READ_STRING(temp);
            }
            
        }
    }
}
