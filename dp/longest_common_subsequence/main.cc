#include "array.h"

#include <time.h>
#include <stdlib.h>

#include <vector>
#include <iostream>
#include <numeric>

std::string backtrack(
      std::vector<Array> const & dp, std::string const & a, std::string const & b, size_t i, size_t j )
{
   if( i == 0 || j == 0 )
      return std::string();

   if( a[i-1] == b[j-1] )
      return backtrack( dp, a, b, i-1, j-1 ) + a[i-1];

   if( dp[i][j-1] > dp[i-1][j] )
      return backtrack( dp, a, b, i, j-1 );

   return backtrack( dp, a, b, i-1, j );
}

std::string lcs_dp( std::string const & a, std::string const & b )
{
   std::vector< Array > dp( a.size() + 1, Array( b.size() + 1, 0 ) );

   for( size_t i=1; i<dp.size(); ++i )
   {
      for( size_t j=1; j<dp[i].size(); ++j )
      {
         dp[i][j] =
            a[i-1] == b[j-1] ?
            dp[i-1][j-1] + 1 :
            std::max( dp[i-1][j], dp[i][j-1] );
      }
   }

   return backtrack( dp, a, b, a.size(), b.size() );
}

bool is_subsequence( std::string const & str, std::string const & sub )
{
   size_t pos = 0;

   for( size_t i=0; i<sub.size(); ++i )
   {
      size_t p = str.find( sub[i], pos );

      if( p == std::string::npos )
         return false;

      pos = p + 1;
   }

   return true;
}

std::string lcs_bruteforce( std::string const & a, std::string const & b )
{
   if( a.empty() || b.empty() )
      return std::string();

   if( a.size() > b.size() )
      return lcs_bruteforce( b, a );

   std::string sub;
   std::string max;
   size_t count = (1 << a.size());

   for( size_t i=1; i<count; ++i )
   {
      sub.clear();

      for( size_t j=0; j<a.size(); ++j )
      {
         if( i & (1 << j) )
            sub += a[j];
      }

      if( is_subsequence( b, sub ) && max.size() < sub.size() )
         max = sub;
   }

   return max;
}

void init( std::string & a, size_t sz )
{
   static char const codes[] = { 'A', 'C', 'G', 'T' };

   a.resize( sz );

   for( size_t i=0; i<sz; ++i )
      a[i] = codes[ rand() % ( sizeof(codes)/sizeof(codes[0]) ) ];
}

void test( size_t asz, size_t bsz )
{
   std::string a, b;

   init( a, asz );
   init( b, bsz );

   std::string dp = lcs_dp( a, b );
   std::string bf = lcs_bruteforce( a, b );

   bool good =
         dp.size() == bf.size()  &&
         is_subsequence( a, dp ) &&
         is_subsequence( b, dp ) &&
         is_subsequence( a, bf ) &&
         is_subsequence( b, bf );

   if( !good )
   {
      std::cout << a << '\n' << b << '\n' << dp << '\n' << bf << std::endl;
      abort();
   }
}

void test( size_t sz )
{
   for( size_t i=0; i<sz; ++i )
      for( size_t j=0; j<sz; ++j )
         test( i, j );
}

int main()
{
   srand( time(0) );

   for( size_t i=0; i<10000; ++i )
      test( 10 );
}
