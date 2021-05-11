#ifndef SABATO_IRUNNER_HPP
#define SABATO_IRUNNER_HPP

namespace smart_home {

struct IRunner {
    // IRunner() = default;
    // IRunner(const IRunner&) = default;
    // IRunner& operator=(const IRunner&) = default;
    
    virtual ~IRunner() {}
    virtual void Run() = 0;
    virtual void Start() = 0;
    virtual void Shutdown() = 0;

};

} // smart_home

#endif  // SABATO_IRUNNER_HPP
