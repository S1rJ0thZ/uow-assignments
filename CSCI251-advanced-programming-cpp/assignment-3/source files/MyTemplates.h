// Templates file
//
// File name: MyTemplates.h

#include <cmath>

// scalar difference
template <typename T>
double scalar_difference(T param1, T param2) 
{
	return abs( param1.getScalarValue() - param2.getScalarValue() );
}

// equals
template <typename T>
bool equal(T param1, T param2) 
{
	return param1 == param2;	// Requires overloading == 
}
