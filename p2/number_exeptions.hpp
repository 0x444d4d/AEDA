#pragma once

#include <exception>

#define STACK_LIMIT_DEFAULT 100


class exception_numbers: public std::exception
{
};

class base_exception: public exception_numbers
{
public:
	virtual const char* what(void) const throw ()
	{
		return "Numbers template exception: invalid base";
	}
};

class overflow: public exception_numbers 
{
public:
	virtual const char* what(void) const throw ()
	{
		return "Numbers template exception: overflow";
	}
};


class double_free: public exception_numbers 
{
public:
	virtual const char* what(void) const throw ()
	{
		return "Numbers template exception: double free";
	}
};


class out_of_range: public exception_numbers 
{
public:
	virtual const char* what(void) const throw ()
	{
		return "Numbers template exception: out of range";
	}
};
