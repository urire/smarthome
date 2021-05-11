#ifndef EXPERIS_LOOKUP_TABLE_INL
#define EXPERIS_LOOKUP_TABLE_INL

namespace experis {

template<typename Key, typename Value>
void LookupTable<Key, Value>::Add(ValuePtr a_item)  {
	if(!Contains(a_item->Name())) {
		m_factories[a_item->Name()] = a_item;
	}	
}

template<typename Key, typename Value>
void LookupTable<Key, Value>::Add(const Key& a_key, ValuePtr a_item) {
	if(!Contains(a_key)) {
		m_factories[a_key] = a_item;
	}
}

template<typename Key, typename Value>
Value& LookupTable<Key, Value>::Get(const Key& a_key) {
	if (!Contains(a_key)) {
		throw KeyNotFoundException();
	}

	return *m_factories[a_key];
}

template<typename Key, typename Value>
bool LookupTable<Key, Value>::Contains(const Key& a_key) {
	return m_factories.find(a_key) != m_factories.end();
}

} // experis

#endif	// EXPERIS_LOOKUP_TABLE_INL
