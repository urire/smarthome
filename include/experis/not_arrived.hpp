#ifndef EXPERIS_NOT_ARRIVED_HPP
#define EXPERIS_NOT_ARRIVED_HPP
        
namespace experis {

class NotArrived {
public:
    inline NotArrived(bool& a_arrived);

    inline bool operator()();

private:
    bool& m_arrived;

};

inline NotArrived::NotArrived(bool& a_arrived) 
: m_arrived(a_arrived) 
{
}

inline bool NotArrived::operator()() { 
    return !m_arrived; 
}

} // experis

#endif  // EXPERIS_NOT_ARRIVED_HPP 
