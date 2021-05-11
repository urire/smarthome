#include "timestamp.hpp"		// smart_home::Timestamp
#include <sys/time.h>			// gettimeofday, struct timeval

namespace smart_home {

Timestamp::Timestamp()
: m_time() 
{
	struct timeval tp;
	
	gettimeofday(&tp, 0);
	m_time = tp.tv_sec * 1000 + tp.tv_usec / 1000;
}

bool Timestamp::operator==(const Timestamp& a_other) const {
	return m_time == a_other.m_time;
}

bool Timestamp::operator!=(const Timestamp& a_other) const {
	return m_time != a_other.m_time;
}

bool Timestamp::operator<(const Timestamp& a_other) const {
	return m_time < a_other.m_time;
}

bool Timestamp::operator>(const Timestamp& a_other) const {
	return m_time > a_other.m_time;
}

bool Timestamp::operator>=(const Timestamp& a_other) const {
	return m_time >= a_other.m_time;
}

bool Timestamp::operator<=(const Timestamp& a_other) const {
	return m_time <= a_other.m_time;
}
	
size_t Timestamp::Time() const{
	return m_time;
}

} // smart_home
