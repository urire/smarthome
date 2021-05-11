#ifndef SABATO_EVENT_TYPE_HPP
#define SABATO_EVENT_TYPE_HPP

#include <string>			// std::string
#include "location.hpp"		// smart_home::Location

namespace smart_home {

class EventType {
public:
	static const std::string& All();

public:
	// EventType() = delete;
	// EventType(const EventType&) = default;
	// EventType& operator=(const EventType&) = default;
	// ~EventType() = default;

	EventType(const std::string& a_name = s_all, const std::string& a_room = s_all, const std::string& a_floor = s_all);

	void Name(const std::string& a_name);
	void Room(const std::string& a_room);
	void Floor(const std::string& a_floor);
	void Position(const Location& a_location);

	const std::string& Name() const;
	const std::string& Room() const;
	const std::string& Floor() const;
	const Location& Position() const;

	bool ContainsAll() const;

	bool operator<(const EventType& a_other) const;

private:
	static const std::string s_all;

private:
	std::string m_name;
	Location m_location;

};

} // smart_home

#endif  // SABATO_EVENT_TYPE_HPP
