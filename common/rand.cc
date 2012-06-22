#include "rand.h"

RandUnique::RandUnique( int left, int right ):
   m_size( right - left + 1 ),
   m_array( m_size )
{
   for( size_t i=0; i<m_size; ++i )
      m_array[ i ] = left + i;
}

int RandUnique::operator()()
{
   if( m_size == 0 )
      abort();

   int idx = rand() % m_size;

   std::swap( m_array[ idx ], m_array[ m_size-1 ] );

   return m_array[ --m_size ];
}
