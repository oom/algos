#include "postorder.h"
#include <stack>

Array postorder( Tree const * tree )
{
   Array ret;
   Tree const * previous = 0;
   std::stack< Tree const * > s;

   if( !tree )
      return ret;

   s.push( tree );

   while( !s.empty() )
   {
      Tree const * current = s.top();

      if( previous == 0 || previous->left == current || previous->right == current ) // previous is a parent of current
      {
         if( current->left )
            s.push( current->left );
         else if( current->right )
            s.push( current->right );
      }
      else if( current->left == previous )
      {
         if( current->right )
            s.push( current->right );
      }
      else
      {
         s.pop();
         ret.push_back( current->data );
      }

      previous = current;
   }

   return ret;
}
