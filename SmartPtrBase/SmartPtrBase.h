#pragma once
#include <utility>
template<typename T>
struct MemFuncTraits{};

template<typename R ,typename O>
struct MemFuncTraits<R (O::*)()>
{
	typedef R ReturnType;
	typedef O ObjectType;
};

template<typename R, typename O>
struct MemFuncTraits < R(O::*)() const >
{
	typedef R ReturnType;
	typedef O ObjectType;
};

template<typename R, typename O,typename P1>
struct MemFuncTraits < R(O::*)(P1) >
{
	typedef R ReturnType;
	typedef O ObjectType;
};

template<typename R, typename O, typename P1>
struct MemFuncTraits < R(O::*)(P1) const >
{
	typedef R ReturnType;
	typedef O ObjectType;
};
//new
template<typename R, typename O>
struct MemFuncTraits < R O::* >
{
	typedef R ReturnType;
	typedef O ObjectType;
};


template<typename MemFuncPtrType>
class PMFC{
public:
	typedef typename MemFuncTraits<MemFuncPtrType>::ObjectType ObjectType;
	typedef typename MemFuncTraits<MemFuncPtrType>::ReturnType ReturnType;
	typedef std::pair<ObjectType*, MemFuncPtrType> CallInfo;

	PMFC(const CallInfo& info) :_callInfo(info){}

	ReturnType operator()() const
	{
		return (_callInfo.first->*_callInfo.second)();
	}

	template<typename Param1>
	ReturnType operator()(Param1 p1) const
	{
		return (_callInfo.first->*_callInfo.second)(p1);
	}

	//new
	operator ReturnType() const
	{
		return (_callInfo.first->*_callInfo.second);
	}

private:
	CallInfo _callInfo;
};

template<typename T>
class SmartPtrBase
{
public:
	SmartPtrBase(T* p) :ptr(p){}

	template<typename MemFuncPtrType>
	const PMFC<MemFuncPtrType> operator->*(MemFuncPtrType pmf) const
	{
		return std::make_pair(ptr, pmf);
	}

private:
	T* ptr;
};

template<typename T>
class SP:public SmartPtrBase<T>
{
public:
	SP(T* p) :SmartPtrBase<T>(p),ptr(p){}
	//using SmartPtrBase<T>::operator->*;
	//smart point
	~SP(){ if(ptr) delete ptr; }
private:
	T* ptr;
};