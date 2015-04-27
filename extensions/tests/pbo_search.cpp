#include "ace_common.h"
#include "pbo\archive.hpp"

#include "logging.hpp"
INITIALIZE_EASYLOGGINGPP


int main(int argc, char **argv) {
    //ace::p3d::parser _parser;
	

#ifdef _DEBUG
    el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format, "[%datetime] - %level - {%loc}t:%thread- %msg");
    //%d%M%Y-%H:%m:%s.%g			
#else
    el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format, "%datetime-{%level}- %msg");
#endif
    std::fstream filestream;
    ace::pbo::archive_p _archive = nullptr;

    if (argc < 2) {
        LOG(ERROR) << "No pbo name provided";
        return -1;
    }

    filestream.open(argv[1], std::ios::binary | std::ios::in);
    if (!filestream.good()) {
        LOG(ERROR) << "Cannot open file";
        return -1;
    }

    _archive = std::make_shared<ace::pbo::archive>(filestream);
    
    LOG(INFO) << "Archive opened: " << argv[1];
    LOG(INFO) << "\t" << _archive->info->name << "=" << _archive->info->data;
    LOG(INFO) << "Entries: " << _archive->entries.size();

    for (ace::pbo::entry_p & entry : _archive->entries) {
        LOG(INFO) << "\t" << entry->filename;
        LOG(INFO) << "\t\t" << "Size=" << entry->size << ", StorageSize=" << entry->storage_size << ", offset=" << entry->offset + _archive->begin_data_offset;
        if (entry->filename == "test.txt") {
            ace::pbo::file_p test_file = std::make_shared<ace::pbo::file>();
            bool result = _archive->get_file(filestream, entry, test_file);
            if (result) {
                LOG(INFO) << "File Read";
                LOG(INFO) << "--------------------------------";
                LOG(INFO) << "Data: [" << test_file->data << "]";
                LOG(INFO) << "--------------------------------";
            } else {
                LOG(ERROR) << "READ OF TEST FILE FAILED!!!!";
            }
        }
    }

    


    getchar();

    return 0;
} 