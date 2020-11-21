#pragma once
#include<cassert>

template<class T> class Singleton
{
protected:
	static T* ms_singleton;

protected:
	Singleton(void) {
		assert(!ms_singleton);
		ms_singleton = static_cast<T*>(this);
	}

public:
	~Singleton(void) {
		assert(ms_singleton);
		ms_singleton = 0;
	}

	static T& GetSingleton(void) {
		return *(GetSingletonPtr());
	}

	static T*GetSingletonPtr(void) {
		if (!ms_singleton) {
			ms_singleton = new T();
		}
		return ms_singleton;
	}
};

template<class T> T* Singleton<T>::ms_singleton = 0;