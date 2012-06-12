#include "array.h"

#include <ctime>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <vector>
#include <iostream>

size_t find_min( int const a[], size_t i, size_t w )
{
   size_t min = i;

   for( size_t k=i+1; k<i+w; ++k )
   {
      if(a[min] > a[k])
         min = k;
   }

   return min;
}

void sliding_min_bruteforce( int const a[], size_t n, size_t w, int b[] )
{
   for( size_t i=0; i<=n-w; ++i )
   {
      size_t min = find_min( a, i, w );
      b[i] = a[min];
   }
}

void sliding_min_smart( int const a[], size_t n, size_t w, int b[] )
{
   std::deque<size_t> q;

   for( size_t i=0; i<w; ++i )
   {
      while( !q.empty() && a[q.back()] >= a[i] )
         q.pop_back();

      q.push_back(i);
   }

   for( size_t i=w; i<n; ++i )
   {
      b[i-w] = a[q.front()];

      while( !q.empty() && q.front() <= i-w )
         q.pop_front();

      while( !q.empty() && a[q.back()] >= a[i] )
         q.pop_back();

      q.push_back(i);
   }

   b[n-w] = a[q.front()];
}

void init( Array & a, size_t sz )
{
   a.resize( sz );

   for( size_t i=0; i<sz; ++i )
      a[i] = rand() % ( sz * 2 );
}

void test( Array const & a, size_t w )
{
   Array b( a.size() - w + 1 );
   Array s( a.size() - w + 1 );

   sliding_min_bruteforce( &a[0], a.size(), w, &b[0] );
   sliding_min_smart( &a[0], a.size(), w, &s[0] );

   if(b != s)
      abort();
}

void test( size_t sz )
{
   Array a;

   init( a, sz );

   for( size_t w=1; w<=sz; ++w )
      test( a, w );
}

int main()
{
   srand( time(0) );

   for( size_t sz=0; sz<=10; ++sz )
      for( size_t i=0; i<100000; ++i )
         test( sz );
}
