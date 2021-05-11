#ifndef SABATO_CONFIGURATOR_INL
#define SABATO_CONFIGURATOR_INL

using namespace experis;

namespace smart_home {

template<typename Container, typename Stream>
void Configurator::Configurate(Container& a_container, Stream& a_stream) { 
    while (!a_stream.eof()) {
        addAgentDetails(a_container, a_stream);
    }
}

template<typename Container, typename Stream>
void Configurator::addAgentDetails(Container& a_container, Stream& a_stream) {
    std::string line, field, value;
    AgentDetails details;
            
    while (std::getline(a_stream, line)) {
        removeWhitespaces(line);
        
        if (line.empty()) {
            break;
        }

        if (startsWith(line, "[")) {
            if(details.Id() != "") {
                throw AgentAlreadyInitializedException();
            }
        
            if (line.size() < 3 || !endsWith(line, "]")) {
                throw InvalidArgumentException();
            }

            details.Id(line.substr(1, line.size() - 2));
        }
        else {
            if (!parseFieldAndValue(line, field, value)) {
                throw InvalidArgumentException();
            }
            
            getAgentDetails(field, value, details);
        }
    }
    
    if (details.Id() == "" || details.Type() == "" || details.Room() == "" || details.Floor() == "") {
        throw MissingArgumentException();
    }
    
    a_container.push_back(details);
}

} // smart_home

#endif  // SABATO_CONFIGURATOR_INL