#pragma once
#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <syncstream>
#include <thread>
#include <variant>
#include <typeinfo>

#include <iostream>
#include <fstream>

#include "ErrorCodes.h"

template <typename T>
size_t doesCoreObjectContainIndex(const std::shared_ptr<T>& source) {
	return source->isIndexNode();
}

template <typename... Types>
size_t doesVariantContainIndex(std::variant<std::shared_ptr<Types>...>& source) {
	return std::visit([](const auto& ptr) -> size_t {
		return doesCoreObjectContainIndex(ptr);
		}, source);
}

template <typename T>
size_t getCoreObjectMemoryFootprint(const std::shared_ptr<T>& source) {
	return source->getMemoryFootprint();
}

template <typename... Types>
size_t getVariantMemoryFootprint(std::variant<std::shared_ptr<Types>...>& source) {
	return std::visit([](const auto& ptr) -> size_t {
		return getCoreObjectMemoryFootprint(ptr);
		}, source);
}

template <typename T>
std::shared_ptr<T> cloneSharedPtr(const std::shared_ptr<T>& source) {
	return source ? std::make_shared<T>(*source) : nullptr;
}

template <typename... Types>
std::variant<std::shared_ptr<Types>...> cloneVariant(const std::variant<std::shared_ptr<Types>...>& source) {
	using VariantType = std::variant<std::shared_ptr<Types>...>;

	return std::visit([](const auto& ptr) -> VariantType {
		return VariantType(cloneSharedPtr(ptr));
		}, source);
}

template <typename T>
void resetCoreValue(std::shared_ptr<T>& source) {
	if (source == nullptr)
	{
		return;
	}
	source.reset();
}

template <typename... Types>
void resetVaraint(std::variant<std::shared_ptr<Types>...>& source) {
	return std::visit([](auto& ptr) {
		resetCoreValue(ptr);
		}, source);
}

template <typename ObjectUIDType, typename CoreTypesMarshaller, typename... ValueCoreTypes>
class LRUCacheObject
{
private:
	typedef LRUCacheObject<ObjectUIDType, CoreTypesMarshaller, ValueCoreTypes...> SelfType;

	typedef std::variant<std::shared_ptr<ValueCoreTypes>...> ValueCoreTypesWrapper;

public:
	typedef std::tuple<ValueCoreTypes...> ValueCoreTypesTuple;

public:
	std::shared_ptr<LRUCacheObject>* hook;
	bool m_bDirty;
	ValueCoreTypesWrapper m_objData;
	std::shared_mutex m_mtx;

	ObjectUIDType m_uidSelf;
	std::shared_ptr<SelfType> m_ptrPrev;
	std::shared_ptr<SelfType> m_ptrNext;

public:
	~LRUCacheObject()
	{
		resetVaraint(m_objData);
	}

	template<class ValueCoreType>
	LRUCacheObject(uint8_t nType, std::shared_ptr<ValueCoreType> ptrCoreObject)
		: m_bDirty(true)
		, m_ptrNext(nullptr)
		, m_ptrPrev(nullptr)
		, hook(NULL)
	{
		m_objData = ptrCoreObject;

		//ObjectUIDType::createAddressFromVolatilePointer(m_uidSelf, nType, reinterpret_cast<uintptr_t>(this));
	}

	template<class ValueCoreType>
	LRUCacheObject(/*const ObjectUIDType& uidObject, */std::shared_ptr<ValueCoreType> ptrCoreObject)
		: m_bDirty(true)
		, m_ptrNext(nullptr)
		, m_ptrPrev(nullptr)
		, hook(NULL)
	{
		m_objData = ptrCoreObject;

		//auto a = reinterpret_cast<uintptr_t>(this);
	}

	LRUCacheObject(/*const ObjectUIDType& uidObject, */std::fstream& fs)
		: m_bDirty(false)
		, m_ptrNext(nullptr)
		, m_ptrPrev(nullptr)
		, hook(NULL)
	{
		CoreTypesMarshaller::template deserialize<ValueCoreTypesWrapper, ValueCoreTypes...>(fs, m_objData);
	}

	LRUCacheObject(/*const ObjectUIDType& uidObject, */const char* szBuffer)
		: m_bDirty(false)
		, m_ptrNext(nullptr)
		, m_ptrPrev(nullptr)
		, hook(NULL)
	{
		CoreTypesMarshaller::template deserialize<ValueCoreTypesWrapper, ValueCoreTypes...>(szBuffer, m_objData);
	}

	inline void hook_(std::shared_ptr<LRUCacheObject>* ref)
	{
		hook = ref;
	}

	inline void unhook_()
	{
		if (hook == NULL)
		{
			return;
		}
		*hook = nullptr;

		m_ptrNext = nullptr;
		m_ptrPrev=nullptr;
	}


	inline void serialize(std::fstream& fs, uint8_t& uidObject, uint32_t& nBufferSize)
	{
		CoreTypesMarshaller::template serialize<ValueCoreTypes...>(fs, m_objData, uidObject, nBufferSize);
	}

	inline void serialize(char*& szBuffer, uint8_t& uidObject, uint32_t& nBufferSize)
	{
		CoreTypesMarshaller::template serialize<ValueCoreTypes...>(szBuffer, m_objData, uidObject, nBufferSize);
	}

	inline ObjectUIDType getUID() const
	{
		return m_uidSelf;
	}

	inline void setUID(ObjectUIDType& uid)
	{
		m_uidSelf = uid;
	}


	inline bool getDirtyFlag() const 
	{
		return m_bDirty;
	}

	inline void setDirtyFlag(bool bDirty)
	{
		m_bDirty = bDirty;
	}

	inline const ValueCoreTypesWrapper& getInnerData() const
	{
		return m_objData;
	}

	inline std::shared_mutex& getMutex()
	{
		return m_mtx;
	}

	inline bool tryLockObject()
	{
		return m_mtx.try_lock();
	}

	inline void unlockObject()
	{
		m_mtx.unlock();
	}

	inline size_t getMemoryFootprint()
	{
		return sizeof(*this) + getVariantMemoryFootprint(m_objData);
	}

	inline bool isIndexNode()
	{
		return sizeof(*this) + doesVariantContainIndex(m_objData);
	}
};