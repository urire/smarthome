#include "completion_aware_thread.hpp"		// experis::CompletionAwareThread

namespace experis {

CompletionAwareThread::CompletionAwareAction::CompletionAwareAction(const SharedPtr<IAction>& a_action, CompletionAwareThread* a_thread)
: IAction()
, m_action(a_action)
, m_thread(a_thread) {
}

void CompletionAwareThread::CompletionAwareAction::Perform() {
	m_action->Perform();
	m_thread->MarkAsDead();
}
	
void CompletionAwareThread::Exit() {
	pthread_exit(NULL);
}
	
CompletionAwareThread::CompletionAwareThread(const SharedPtr<IAction>& a_action, RendezvousPoint& a_rendPoint)
: IUnassignable()
, m_action(a_action, this)
, m_thread(m_action)
, m_isAlive(true)
, m_rendPoint(a_rendPoint){
	m_thread.Start();
}

bool CompletionAwareThread::IsAlive() const {
	return m_isAlive;
}
	
void CompletionAwareThread::MarkAsDead() {
	m_isAlive = false;
	m_rendPoint.Notify();
}	

} // experis
