#ifndef SABATO_READER_HPP
#define SABATO_READER_HPP

#include <string>				// std::string
#include <exception>			// std::exception

namespace smart_home {

class Reader {
public:
	struct FileNotOpenedExcpetion : public std::exception {};
    struct FileContentNotGoodExcpetion : public std::exception {};

public:
    template<typename Stream>
    static void Read(const std::string& a_fileName, Stream& a_stream);

private:

};

} // smart_home

#include "inl/reader.inl"

#endif  // SABATO_READER_HPP
