#ifndef SABATO_READER_ONL
#define SABATO_READER_ONL

#include <fstream>          // std::ifstream

namespace smart_home {

template<typename Stream>
void Reader::Read(const std::string& a_fileName, Stream& a_stream) {
    std::ifstream file(a_fileName.c_str());

	if(!file.is_open()) {
        throw FileNotOpenedExcpetion();
    }

    a_stream << file.rdbuf();
    
    if (!a_stream.good()) {
        throw FileContentNotGoodExcpetion();
    }

	file.close();
}

} // smart_home

#endif  // SABATO_READER_ONL