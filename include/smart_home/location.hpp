#ifndef SABATO_LOCATION_HPP
#define SABATO_LOCATION_HPP

#include <string>				// std::string

namespace smart_home {

class Location {
public:
	// Location(const Location&) = default;
	// Location& operator=(const Location&) = default;
	// ~Location() = default;

	Location(const std::string& a_floor = "", const std::string& a_room = "");
	
    void Floor(const std::string& a_floor);
    void Room(const std::string& a_room);

	const std::string& Floor() const;
	const std::string& Room() const;

	bool operator<(const Location& a_other) const;

private:
	std::string m_floor;
	std::string m_room;
	
};

} // smart_home

#endif	// SABATO_LOCATION_HPP
