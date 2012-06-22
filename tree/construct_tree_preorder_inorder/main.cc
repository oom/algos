#include "construct.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>

static void make_preorder( Tree const * x, Array & out )
{
   if( !x )
      return;

   out.push_back( x->data );
   make_preorder( x->left, out );
   make_preorder( x->right, out );
}

static void make_inorder( Tree const * x, Array & out )
{
   if( !x )
      return;

   make_inorder( x->left, out );
   out.push_back( x->data );
   make_inorder( x->right, out );
}

bool is_equal( Tree const * x, Tree const * y )
{
   if( !x )
      return !y;

   if( !y )
      return false;

   return
      x->data == y->data &&
      is_equal( x->left, y->left ) &&
      is_equal( x->right, y->right );
}

void test( Tree * tree )
{
   Array preorder;
   Array inorder;

   fill_rand_uniq( tree, -10, 10 );

   make_preorder( tree, preorder );
   make_inorder( tree, inorder );

   Tree * copy = construct( preorder, inorder );

   if( !is_equal( tree, copy ) )
   {
      print( tree );
      puts( "---" );
      print( copy );
      puts( "---" );
      std::cout << "PREORDER: " << preorder << '\n';
      std::cout << "INORDER:  " << inorder  << '\n';
      abort();
   }

   delete copy;
}

int main()
{
   srand( time(0) );
   for_each_skel( &test, 16 );
}
