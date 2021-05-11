#ifndef EXPERIS_IUNCOPYABLE_HPP
#define EXPERIS_IUNCOPYABLE_HPP

namespace experis {

class IUncopyable {
public:
    inline IUncopyable();
    inline virtual ~IUncopyable() = 0;
    
private:
	IUncopyable (const IUncopyable& a_other);				// forbidden from user
    IUncopyable& operator=(const IUncopyable& a_other);		// forbidden from user

};

inline IUncopyable::IUncopyable() {
}

inline IUncopyable::~IUncopyable() {
}

} // experis

#endif	// EXPERIS_IUNCOPYABLE_HPP
