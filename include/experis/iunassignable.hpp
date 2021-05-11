#ifndef EXPERIS_IUNASSIGNABLE_HPP
#define EXPERIS_IUNASSIGNABLE_HPP

namespace experis {

class IUnassignable {
public:
    inline IUnassignable();
    inline IUnassignable (const IUnassignable& a_other);
    inline virtual ~IUnassignable() = 0;
    
private:
	IUnassignable& operator=(const IUnassignable& a_other);     // forbidden from user

};

inline IUnassignable::IUnassignable() {
}

inline IUnassignable::IUnassignable(const IUnassignable& a_other) {
}

inline IUnassignable::~IUnassignable() {
}

} // experis

#endif	// EXPERIS_IUNASSIGNABLE_HPP
