#include "list.h"
#include "tree.h"
#include "array.h"

#include <ctime>
#include <climits>
#include <cstdlib>
#include <iostream>

static Tree * make( int *& first, int * end, int cap )
{
   if( first == end || *first > cap )
      return 0;

   Tree * root = new Tree( *first++ );

   root->left = make( first, end, root->data );
   root->right = make( first, end, cap );

   return root;
}

static Tree * make( Array & order )
{
   int * first = order.empty() ? 0 : &order[0];
   return make( first, first + order.size(), INT_MAX );
}

// -- TEST ---

static void preorder( Tree * root, Array & order )
{
   if( !root )
      return;

   order.push_back( root->data );
   preorder( root->left, order );
   preorder( root->right, order );
}

static Array preorder( Tree * root )
{
   Array ret;

   preorder( root, ret );
   return ret;
}

static bool is_equal( Tree * a, Tree * b )
{
   if( !a && !b )
      return true;

   if( !a || !b )
      return false;

   return
      a->data == b->data &&
      is_equal( a->left, b->left ) &&
      is_equal( a->right, b->right );
}

static void test( Tree * tree )
{
   fill_rand_bst( tree, -100, 100 );

   Array order = preorder( tree );
   Tree * copy = make( order );

   if( !is_equal( tree, copy ) )
   {
      print( tree );
      std::cout << order << std::endl;
      print( copy );
      abort();
   }

   delete copy;
}

int main()
{
   srand( time(0) );
   for_each_skel( &test, 16 );
}
