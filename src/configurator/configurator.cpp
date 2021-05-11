#include "configurator.hpp"			// smart_home::Configurator
#include <algorithm>				// std::remove_if
#include <ctype.h>					// isspace

namespace smart_home {

void Configurator::removeWhitespaces(std::string& a_str) {
	 a_str.erase(std::remove_if(a_str.begin(), a_str.end(), isspace), a_str.end());
}

bool Configurator::startsWith(const std::string& a_str, const std::string& a_prefix) {
	return a_str.find(a_prefix) == 0;
}

bool Configurator::endsWith(const std::string& a_str, const std::string& a_postfix) {
	return a_str.find(a_postfix, a_str.size() - a_postfix.size()) != std::string::npos;
}

bool Configurator::parseFieldAndValue(const std::string& a_line, std::string& a_field, std::string& a_value) {
	size_t equalIdx = a_line.find("=");
	bool isEqualFound = equalIdx != std::string::npos;

	if (isEqualFound) {
		a_field = a_line.substr(0, equalIdx);
		a_value = a_line.substr(equalIdx + 1, a_line.size() - equalIdx - 1);
	}

	return isEqualFound;
}

void Configurator::getAgentDetails(const std::string& a_field, const std::string& a_value, AgentDetails& a_details) {
	if (a_field == "type") {
		if (a_details.Type() != "") {
			throw InvalidArgumentException();
		}

		a_details.Type(a_value);
	}
	else if (a_field == "room") {
		if (a_details.Room() != "") {
			throw InvalidArgumentException();
		}

		a_details.Room(a_value);
	}
	else if (a_field == "floor") {
		if (a_details.Floor() != "") {
			throw InvalidArgumentException();
		}

		a_details.Floor(a_value);
	}
	else if (a_field == "config") {
		if (a_details.Config() != "") {
			throw InvalidArgumentException();
		}

		a_details.Config(a_value);
	}
	else if (a_field == "log") {
		if (a_details.Log() != "default") {
			throw InvalidArgumentException();
		}

		a_details.Log(a_value);
	}
	else {
		throw InvalidArgumentException();
	}
}

} // smart_home
