#ifndef THREAD_POOL_COMPLETION_AWARE_THREAD_HPP
#define THREAD_POOL_COMPLETION_AWARE_THREAD_HPP

#include "iaction.hpp"						// experis::IAction
#include "iunassignable.hpp"				// experis::IUnassignable
#include "rendezvous_point.hpp"				// experis::RendezvousPoint
#include "shared_ptr.hpp"					// experis::SharedPtr
#include "old_thread.hpp"					// experis::OldThread

namespace experis {

class CompletionAwareThread : private IUnassignable {
public:
	class CompletionAwareAction : public IAction {
	public:
		CompletionAwareAction(const SharedPtr<IAction>& a_action, CompletionAwareThread* a_thread);
		
		virtual void Perform();
	
	private:
		SharedPtr<IAction> m_action;
		CompletionAwareThread* m_thread;
	
	};

public:	
	static void Exit();

public:	
	CompletionAwareThread(const SharedPtr<IAction>& a_action, RendezvousPoint& a_rendPoint);
	
	bool IsAlive() const;
	
private: // for friends
	void MarkAsDead();

private:
	CompletionAwareAction m_action;
	OldThread m_thread;
	bool m_isAlive;
	RendezvousPoint& m_rendPoint;
	
};

} // experis

#endif	// THREAD_POOL_COMPLETION_AWARE_THREAD_HPP
