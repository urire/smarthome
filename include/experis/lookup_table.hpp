#ifndef EXPERIS_LOOKUP_TABLE_HPP
#define EXPERIS_LOOKUP_TABLE_HPP

#include "shared_ptr.hpp"		// experis::SharedPtr
#include "iuncopyable.hpp"		// experis::IUncopyable
#include <exception>			// std::exception
#include <map>					// std::map

namespace experis {

template<typename Key, typename Value>
class LookupTable : private IUncopyable {
public:
	struct KeyNotFoundException : public std::exception {};

	typedef SharedPtr<Value> ValuePtr;

public:
	// LookupTable() = default;
	// ~LookupTable() = default;

	void Add(ValuePtr a_item);
	void Add(const Key& a_key, ValuePtr a_item);
	Value& Get(const Key& a_key);
	bool Contains(const Key& a_key);
	
private:
	std::map<Key, ValuePtr> m_factories;

};

} // experis

#include "inl/lookup_table.inl"

#endif	// EXPERIS_LOOKUP_TABLE_HPP
