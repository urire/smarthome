#ifndef EXPERIS_IACTION_HPP
#define EXPERIS_IACTION_HPP

#include "iunassignable.hpp"		// experis::IUnassignable

namespace experis {

struct IAction : private IUnassignable {
	inline IAction();
	inline virtual ~IAction();
	virtual void Perform() = 0;
};

inline IAction::IAction() {	
}

inline IAction::~IAction() {	
}

} // experis

#endif	// EXPERIS_IACTION_HPP
