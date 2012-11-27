#include "list.h"
#include "tree.h"
#include <ctime>
#include <climits>
#include <cstdlib>
#include <iostream>

static Tree * make( List *& preorder, int cap )
{
   if( !preorder || preorder->data > cap )
      return 0;

   Tree * root = new Tree( preorder->data );
   List * p = preorder->next;

   root->left = make( p, preorder->data );
   root->right = make( p, cap );

   preorder = p;
   return root;
}

static Tree * make( List * preorder )
{
   return make( preorder, INT_MAX );
}

// -- TEST ---

static void preorder( Tree * root, List *& last )
{
   if( !root )
      return;

   last->next = new List( root->data );
   last = last->next;

   preorder( root->left, last );
   preorder( root->right, last );
}

static List * preorder( Tree * root )
{
   List base( 0 );
   List * p = &base;

   preorder( root, p );

   return base.next;
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

   List * p = preorder( tree );
   Tree * copy = make( p );

   if( !is_equal( tree, copy ) )
   {
      print( tree );
      std::cout << p << std::endl;
      print( copy );
      abort();
   }

   destroy( p );
   delete copy;
}

int main()
{
   srand( time(0) );
   for_each_skel( &test, 16 );
}
