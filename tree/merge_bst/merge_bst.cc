#include "merge_bst.h"

void glue( Tree * left, Tree * right )
{
   left->right = right;
   right->left = left;
}

Tree * append( Tree * a, Tree * b )
{
   if( !a || !b )
      return a ? a : b;

   Tree * a_last = a->left;
   Tree * b_last = b->left;

   glue( a_last, b );
   glue( b_last, a );

   return a;
}

Tree * flatten( Tree * a )
{
   if( !a )
      return 0;

   Tree * head = flatten( a->left );
   Tree * tail = flatten( a->right );

   glue( a, a );

   head = append( head, a );
   head = append( head, tail );

   return head;
}

Tree * pop_front( Tree *& list )
{
   if( !list )
      return 0;

   Tree * ret = list;

   if( list == list->right )
   {
      list = 0;
   }
   else
   {
      list = list->right;
      glue( ret->left, list );
      glue( ret, ret );
   }

   return ret;
}

void push_back( Tree *& list, Tree * a )
{
   if( !list )
   {
      list = a;
      return;
   }

   Tree * last = list->left;
   glue( last, a );
   glue( a, list );
}

void push_back_uniq( Tree *& list, Tree * a )
{
   if( list && list->left->data == a->data )
   {
      a->left = a->right = 0;
      delete a;
   }
   else
   {
      push_back( list, a );
   }
}

Tree * merge_lists( Tree * a, Tree * b )
{
   Tree * ret = 0;

   while( a && b )
      push_back_uniq( ret, pop_front( a->data < b->data ? a : b ) );

   while( a )
      push_back_uniq( ret, pop_front( a ) );

   while( b )
      push_back_uniq( ret, pop_front( b ) );

   return ret;
}

int length( Tree * list )
{
   if( !list )
      return 0;

   int ret = 1;
   Tree * p = list;

   while( p->right != list )
   {
      p = p->right;
      ++ret;
   }

   return ret;
}

Tree * make_bst( Tree *& p, int lo, int hi )
{
   if( hi < lo )
      return 0;

   int mid = lo + (hi - lo) / 2;

   Tree * left = make_bst( p, lo, mid - 1 );
   Tree * root = pop_front( p );
   root->left = left;
   root->right = make_bst( p, mid + 1, hi );

   return root;
}

Tree * make_bst( Tree * list )
{
   if( !list )
      return 0;

   return make_bst( list, 0, length(list) - 1 );
}

Tree * merge_bst( Tree * a, Tree * b )
{
   return make_bst( merge_lists( flatten(a), flatten(b) ) );
}
