#ifndef SABATO_TIMESTAMP_HPP
#define SABATO_TIMESTAMP_HPP

#include <cstddef>		// size_t

namespace smart_home {

struct Timestamp {
	// Timestamp(const Timestamp&) = default;
	// Timestamp& operator=(const Timestamp&) = default;
	// ~Timestamp() = default;

	Timestamp();
	
	bool operator==(const Timestamp& a_other) const;
	bool operator!=(const Timestamp& a_other) const;
	bool operator<(const Timestamp& a_other) const;
	bool operator>(const Timestamp& a_other) const;
	bool operator<=(const Timestamp& a_other) const;
	bool operator>=(const Timestamp& a_other) const;

	size_t Time() const;

private:
	size_t m_time;
	
};

} // smart_home

#endif	// SABATO_TIMESTAMP_HPP
