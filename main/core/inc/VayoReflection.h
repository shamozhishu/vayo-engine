/*************************************************************************\
* 望友引擎1.0
* Copyright (c) 2018-2019 authored by 朱加浩
* 反射机制
\*************************************************************************/
#ifndef __VAYO_REFLECTION_H__
#define __VAYO_REFLECTION_H__

#define VAYO_REFLEX_DECLARE(CLASS_TYPE) private: static Vayo::Reflex<CLASS_TYPE> _dynReflex;
#define VAYO_REFLEX_IMPLEMENT(CLASS_TYPE) Vayo::Reflex<CLASS_TYPE> CLASS_TYPE::_dynReflex;

#include "VayoSupport.h"
NS_VAYO_BEGIN

class Type;

template<typename ...Args>
class ReflexFactory
{
public:
	static ReflexFactory& getInstance()
	{
		static ReflexFactory factory;
		return factory;
	}

	static string getTypeName(const char* name)
	{
#ifdef __GNUC__
		char* real_name = abi::__cxa_demangle(name, nullptr, nullptr, nullptr);
		std::string real_name_string(real_name);
		free(real_name);
		return real_name_string;
#else
		const char* p = strstr(name, " ");
		if (p)
		{
			size_t prev_len = (size_t)(p - name);
			if (memcmp(name, "class", prev_len) == 0 ||
				memcmp(name, "struct", prev_len) == 0 ||
				memcmp(name, "enum", prev_len) == 0 ||
				memcmp(name, "union", prev_len) == 0)
			{
				p += 1;
				return std::string(p);
			}
		}
		return std::string(name);
#endif
	}

	Type* create(const string& typeName, Args... args)
	{
		if (typeName.empty())
			return NULL;
		unordered_map<string, function<Type*(Args...)>>::iterator it = _createFuncMap.find(typeName);
		if (it == _createFuncMap.end())
			return NULL;
		return it->second(args...);
	}

	template<typename T>
	T* create(const string& typeName, Args... args)
	{
		Type* pTypeObject = create(typeName, args...);
		if (NULL == pTypeObject)
			return NULL;
		T* pRealObject = dynamic_cast<T*>(pTypeObject);
		if (NULL == pRealObject)
			delete pTypeObject;
		return pRealObject;
	}

	bool enroll(const char* name, function<Type*(Args...)> func)
	{
		if (NULL == name || 0 == strcmp(name, ""))
			return false;
		string typeName = getTypeName(name);
		return _createFuncMap.insert(make_pair(typeName, func)).second;
	}

private:
	unordered_map<string, function<Type*(Args...)>> _createFuncMap;
};

class Type
{
public:
	virtual ~Type() {}
	virtual string getType() const
	{
		return ReflexFactory<>::getInstance().getTypeName(typeid(*this).name());
	}

protected:
	Type() {}
};

template<typename T, typename ...Args>
class Reflex
{
public:
	static Type* dynCreate(Args... args)
	{
		return new T(args...);
	}
	Reflex()
	{
		if (!ReflexFactory<Args...>::getInstance().enroll(typeid(T).name(), dynCreate))
		{
			VAYO_ASSERT(false && "ReflexFactory.enroll() has failed!");
		}
	}
};

NS_VAYO_END

#endif // __VAYO_REFLECTION_H__
