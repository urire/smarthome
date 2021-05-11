#include "exit_looper.hpp"		// experis::ExitLooper

namespace experis {

void ExitLooper::Do() { 
	CompletionAwareThread::Exit(); 
}

} // experis
