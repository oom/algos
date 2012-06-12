#ifndef ALGO_ARRAY_H_INCLUDED
#define ALGO_ARRAY_H_INCLUDED

#include <vector>
#include <iosfwd>

typedef std::vector< int > Array;

std::ostream & operator<<( std::ostream & os, Array const & a );

#endif // ALGO_ARRAY_H_INCLUDED
