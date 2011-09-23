/*
 * Input: n items, with integer sizes Si and values Vi
 *        Knapsack of capacity C.
 *
 * Goal:
 *
 * M(i,j): the maximum value that can be attained with capacity less or equal to j using items up to i.
 *
 * i: 1..n
 * j: 1..C
 *
 * M(i,j) = max{ M(i-1, j), M(i-1, j-Si) + Vi }
 * Opt. objective value: max{ M(n,j), j=1..C }
 *
 * Complexity: time: O(n*C), space: O(n*C)
 */

#include <time.h>
#include <stddef.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

typedef std::vector<size_t> Array;

std::ostream & operator<<( std::ostream & stream, Array const & a )
{
   char const * sep = "";

   stream << '[' << a.size() << "](";

   for( size_t i=0; i<a.size(); ++i )
   {
      stream << sep << a[i];
      sep = " ";
   }

   return stream << ')';
}

size_t knapsack_dp( Array const & value, Array const & weight, size_t capacity )
{
   if( value.size() != weight.size() || value.empty() )
   {
      return 0;
   }

   Array dp[2];

   dp[0].resize( capacity+1, 0 );
   dp[1].resize( capacity+1, 0 );

   bool current = false;

   for( size_t i=0; i<value.size(); ++i )
   {
      current = !current;

      for( size_t j=0; j<=capacity; ++j )
      {
         dp[current][j] = dp[!current][j];

         if( j >= weight[i] )
         {
            size_t v = dp[!current][j-weight[i]] + value[i];

            if( dp[current][j] < v )
               dp[current][j] = v;
         }
      }
   }

   return dp[current].back();
}

size_t knapsack_bruteforce( Array const & value, Array const & weight, size_t capacity )
{
   if( value.size() != weight.size() || value.empty() )
   {
      return 0;
   }

   size_t count = (1 << value.size());
   size_t best  = 0;

   for( size_t i=1; i<count; ++i )
   {
      size_t sum_value  = 0;
      size_t sum_weight = 0;

      for( size_t j=0; j<value.size(); ++j )
      {
         if( i & (1 << j) )
         {
            sum_weight += weight[j];
            sum_value  += value[j];
         }

         if( sum_weight <= capacity && best < sum_value )
         {
            best = sum_value;
         }
      }
   }

   return best;
}

size_t init( Array & value, Array & weight, size_t sz )
{
   value.resize( sz );
   weight.resize( sz );

   size_t total = 0;

   for( size_t i=0; i<sz; ++i )
   {
      value[i]  = 1 + (rand() % (sz*2));
      weight[i] = 1 + (rand() % (sz*2));
      total    += weight[i];
   }

   return total;
}

void test( size_t size )
{
   Array value;
   Array weight;

   size_t total = init( value, weight, size );

   for( size_t i=0; i<=total+1; ++i )
   {
      size_t dp = knapsack_dp( value, weight, i );
      size_t bf = knapsack_bruteforce( value, weight, i );

      if( dp != bf )
      {
         std::cout
            << "weight: " << weight
            << "\nvalue: " << value
            << "\ncapacity: " << i
            << "\ndp: " << dp
            << "\nbf: " << bf
            << std::endl;

         abort();
      }
   }
}

int main()
{
   srand( time(0) );

   for( size_t sz = 0; sz < 8; ++sz )
   {
      for( size_t i = 0; i < 10000; ++i )
         test( sz );
   }
}
