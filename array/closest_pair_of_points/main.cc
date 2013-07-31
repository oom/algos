// http://en.wikipedia.org/wiki/Closest_pair_of_points_problem

#include <cstddef>
#include <vector>
#include <list>
#include <map>

struct Point
{
   int x;
   int y;
};

typedef std::vector< Point > Points;
typedef std::multimap< int, size_t > YMap;
typedef std::list< YMap::iterator > Queue;

static inline unsigned square( int x ) { return x * x; }

static size_t dist( Point const & a, Point const & b )
{
   return square( a.x - b.x ) + square( a.y - b.y );
}

static void add( Points const & points, size_t i, YMap & m, Queue & q )
{
   q.push_back( m.insert(YMap::value_type(points[i].y, i) ) );
}

static void shrink( int min_x, Points const & points, YMap & m, Queue & q )
{
   while( !q.empty() && points[ q.front()->second ].x < min_x )
   {
      m.erase( q.front() );
      q.pop_front();
   }
}

static std::pair<size_t, size_t> smart( Points const & points )
{
   if( points.size() < 2 )
      return std::make_pair( points.size(), points.size() );

   size_t min_a    = 0;
   size_t min_b    = 1;
   size_t min_dist = dist( points[0], points[1] );

   YMap  m;
   Queue q;

   add( points, 0, m, q );
   add( points, 1, m, q );

   for( size_t i = 2; i < points.size(); ++i )
   {
      shrink( points[i].x - min_dist + 1, points, m, q );

      YMap::const_iterator first = m.lower_bound( points[i].y - min_dist );
      YMap::const_iterator last  = m.upper_bound( points[i].y + min_dist );

      for( ; first != last; ++first )
      {
         size_t d = dist( points[i], points[first->second] );

         if( d < min_dist )
         {
            min_a    = first->second;
            min_b    = i;
            min_dist = d;
         }
      }

      add( points, i, m, q );
   }

   return std::make_pair( min_a, min_b );
}

// -- TEST --
#include "rand.h"
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <iostream>

std::ostream & operator<<( std::ostream & os, Point const & p )
{
   return os << '{' << p.x << ", " << p.y << '}';
}

std::ostream & operator<<( std::ostream & os, Points const & p )
{
   char const * sep = "";

   os << '[' << p.size() << "](";

   for( size_t i=0; i<p.size(); ++i )
   {
      os << sep << p[i];
      sep = " ";
   }

   return os << ')';
}

static std::pair<size_t, size_t> bruteforce( Points const & points )
{
   size_t min_a    = points.size();
   size_t min_b    = points.size();
   size_t min_dist = size_t(-1);

   for( size_t i = 0; i < points.size(); ++i )
      for( size_t j = i + 1; j < points.size(); ++j )
      {
         size_t d = dist( points[i], points[j] );

         if( d < min_dist )
         {
            min_a    = i;
            min_b    = j;
            min_dist = d;
         }
      }

   return std::make_pair( min_a, min_b );
}

static Point randPoint( int cap )
{
   Point ret;

   ret.x = rand_range( -cap, cap );
   ret.y = rand_range( -cap, cap );

   return ret;
}

struct LessX
{
   bool operator()( Point const & a, Point const & b ) { return a.x < b.x; }
};

static Points randPoints( size_t sz, int cap )
{
   Points points( sz );

   for( size_t i = 0; i < sz; ++i )
      points[ i ] = randPoint( cap );

   std::sort( points.begin(), points.end(), LessX() );

   return points;
}

static void test( size_t sz, int cap )
{
   Points points = randPoints( sz, cap );

   std::pair<size_t, size_t> a = bruteforce( points );
   std::pair<size_t, size_t> b = smart( points );

   if( a != b && dist(points[a.first], points[a.second]) != dist(points[b.first], points[b.second]) )
   {
      std::cout << points << std::endl;
      std::cout << a.first << '-' << a.second << ": " << dist( points[a.first], points[a.second] ) << std::endl;
      std::cout << b.first << '-' << b.second << ": " << dist( points[b.first], points[b.second] ) << std::endl;
      abort();
   }
}

int main()
{
   srand( time(0) );

   test( 0, 100 );
   test( 1, 100 );

   for( size_t sz = 2; sz < 20; ++sz )
      for( size_t i = 0; i < 10000; ++i )
         test( sz, sz * 10 );
}
