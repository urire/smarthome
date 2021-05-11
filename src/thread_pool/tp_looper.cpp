#include "tp_looper.hpp"			// experis::TPLooper

namespace experis {

TPLooper::TPLooper(ThreadSafeQueue<SharedPtr<Command> >& a_commands)
: m_commands(a_commands) {
}

void TPLooper::Perform() {
	SharedPtr<Command> cmd;

	while(true) {	
		m_commands.Dequeue(cmd);		
		cmd->Do();
	}
}

} // experis
