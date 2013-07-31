#include "tree.h"
#include <list>
#include <stack>
#include <utility>

class InorderIterator
{
public:
   InorderIterator( Tree * root, bool reversed ):
      m_position( root ), m_current( 0 ), m_reversed( reversed )
   {
      next();
   }

   Tree * get() const { return m_current; }

   Tree * next()
   {
      while( m_position || !m_stack.empty() )
      {
         if( m_position )
         {
            m_stack.push( m_position );
            m_position = m_reversed ? m_position->right : m_position->left;
         }
         else
         {
            m_current = m_stack.top();
            m_stack.pop();
            m_position = m_reversed ? m_current->left : m_current->right;

            return m_current;
         }
      }

      return 0;
   }

private:
   Tree * m_position;
   Tree * m_current;
   std::stack<Tree *> m_stack;
   bool m_reversed;
};

typedef std::list< std::pair<Tree *, Tree *> > Pairs;

Pairs findSum( Tree * root, int sum )
{
   Pairs ret;

   InorderIterator lo( root, false );
   InorderIterator hi( root, true );

   while( lo.get() != hi.get() )
   {
      int s = lo.get()->data + hi.get()->data;

      if( s == sum )
      {
         ret.push_back( std::make_pair(lo.get(), hi.get()) );

         if( lo.next() == hi.get() )
            break;

         hi.next();
      }
      else if( s < sum )
      {
         lo.next();
      }
      else
      {
         hi.next();
      }
   }

   return ret;
}

// -- TEST --
#include <ctime>
#include <cstdlib>
#include <iostream>

Tree * find( Tree * root, int x )
{
   while( root )
   {
      if( root->data == x )
         return root;

      root = root->data < x ? root->right : root->left;
   }

   return 0;
}

void inorder( Tree * current, Tree * root, int sum, Pairs & out )
{
   if( !current )
      return;

   inorder( current->left, root, sum, out );

   int p = sum - current->data;

   if( current->data < p )
   {
      Tree * x = find( root, p );

      if( x )
         out.push_back( std::make_pair(current, x) );
   }

   inorder( current->right, root, sum, out );
}

Pairs inorder( Tree * root, int sum )
{
   Pairs ret;
   inorder( root, root, sum, ret );
   return ret;
}

Tree * leftmost( Tree * root )
{
   if( root )
      while( root->left )
         root = root->left;

   return root;
}

Tree * rightmost( Tree * root )
{
   if( root )
      while( root->right )
         root = root->right;

   return root;
}

std::ostream & operator<<( std::ostream & os, Pairs const & p )
{
   os << '(';
   char const * sep = "";

   for( Pairs::const_iterator i = p.begin(), end = p.end(); i != end; ++i )
   {
      os << sep << '[' << i->first->data << ", " << i->second->data << ']';
      sep = " ";
   }

   return os << ')';
}

void test( Tree * root, int sum )
{
   Pairs a = findSum( root, sum );
   Pairs b = inorder( root, sum );

   if( a != b )
   {
      std::cout << "sum=" << sum << " a=" << a << " b=" << b << std::endl;
      print( root );
      abort();
   }
}

void test( Tree * root )
{
   fill_rand_bst( root, -20, 20 );

   Tree * min = leftmost( root );
   Tree * max = rightmost( root );

   if( !min )
      test( root, 0 );
   else
      for( int sum = min->data * 2; sum <= max->data * 2; ++sum )
         test( root, sum );
}

int main()
{
   srand( time(0) );
   for_each_skel( &test, 11 );
}
