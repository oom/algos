#include "merge_bst.h"
#include "array.h"
#include "rand.h"

#include <ctime>
#include <cstdlib>
#include <iostream>

Tree * clone( Tree * root )
{
   if( !root )
      return 0;

   Tree * ret = new Tree( root->data );
   ret->left = clone( root->left );
   ret->right = clone( root->right );

   return ret;
}

bool is_bst( Tree * root, int * min, int * max )
{
   if( !root )
      return true;

   if( min && root->data <= *min )
      return false;

   if( max && root->data >= *max )
      return false;

   return
      is_bst( root->left, min, &root->data ) &&
      is_bst( root->right, &root->data, max );
}

bool is_bst( Tree * root )
{
   return is_bst( root, NULL, NULL );
}

void inorder( Tree * root, Array & ret )
{
   if( !root )
      return;

   inorder( root->left, ret );
   ret.push_back( root->data );
   inorder( root->right, ret );
}

Array inorder( Tree * root )
{
   Array ret;
   inorder( root, ret );
   return ret;
}

Tree * find( Tree * root, int x )
{
   while( root )
   {
      if( root->data == x )
         return root;

      if( x < root->data )
         root = root->left;
      else
         root = root->right;
   }

   return 0;
}

bool contains_all( Array const & array, Tree * a, Tree * b )
{
   for( size_t i = 0; i < array.size(); ++i )
   {
      bool found = find(a, array[i]) || find(b, array[i]);

      if( !found )
         return false;
   }

   return true;
}

static Tree * outer = 0;

void complain( Tree * a, Tree * b, Tree * m )
{
   std::cout << "a:\n";
   print( a );
   std::cout << "b:\n";
   print( b );
   std::cout << "m:\n";
   print( m );
   abort();
}

void test_inner( Tree * inner )
{
   fill_rand_bst( inner, -100, 100 );

   Tree * a = clone( outer );
   Tree * b = clone( inner );

   Tree * m = merge_bst( a, b ); // a and b are destroyed at this point

   if( !is_bst(m) )
      complain( outer, inner, m );

   if( !contains_all(inorder(outer), m, 0) )
      complain( outer, inner, m );

   if( !contains_all(inorder(inner), m, 0) )
      complain( outer, inner, m );

   if( !contains_all(inorder(m), outer, inner) )
      complain( outer, inner, m );

   delete m;
}

static int const MaxSize = 8;

void test_outer( Tree * root )
{
   outer = clone( root );
   fill_rand_bst( outer, -100, 100 );

   for_each_skel( &test_inner, MaxSize );
   delete outer;
}

int main()
{
   srand( time(0) );
   for_each_skel( &test_outer, MaxSize );
}
