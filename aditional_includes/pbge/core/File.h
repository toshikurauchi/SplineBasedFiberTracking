#include <string>
#include <fstream>

#ifndef pbge_file_h
#define pbge_file_h

namespace pbge {

class FileReader {
    public:
        FileReader() {
            buffer = NULL;
        }

        FileReader(const std::string & filename) {
            this->open(filename);
            buffer = NULL;
        }

        bool open(const std::string & filename) {
            this->close();

            file.open(filename.c_str(), std::ios::in|std::ios::binary|std::ios::ate);
            size = file.tellg();
            file.seekg(0, std::ios::beg);
            return true;
        }

        char * getData() {
            if(buffer == NULL) {
                long buffer_size = (long)size + 1;
                buffer = new char[buffer_size];
                buffer[buffer_size - 1] = 0;
                file.read(buffer, size);
            }
            
            return buffer;
        }

        bool is_open() {
            return file.is_open();
        }
        
        bool close() {
            if(file.is_open()) {
                file.close();
                deleteBuffer();
                return true;
            }
            return false;
        }

        void deleteBuffer() {
            if(buffer != NULL) {
                delete [] buffer;
                buffer = NULL;
            }
        }

        long getSize() {
            return static_cast<long> (size);
        }

        ~FileReader() {
            this->close();
        }
    private:
        std::ifstream file;
        std::ios::pos_type size;
        long buffer_size;
        char * buffer;
};


}

#endif