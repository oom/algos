#include <ctime>
#include <cstdlib>

#include <list>
#include <algorithm>

class StackMin
{
public:
   void push( int x )
   {
      m_stack.push_back( x );

      if( m_min.empty() || x <= m_min.back() )
         m_min.push_back( x );
   }

   void pop()
   {
      if( m_stack.back() == m_min.back() )
         m_min.pop_back();

      m_stack.pop_back();
   }

   bool empty()
   {
      return m_stack.empty();
   }

   size_t size() const
   {
      return m_stack.size();
   }

   int top() const
   {
      return m_stack.back();
   }

   int min() const
   {
      return m_min.back();
   }

   int xmin() const
   {
      return *std::min_element(m_stack.begin(), m_stack.end());
   }

private:
   std::list< int > m_stack;
   std::list< int > m_min;
};

bool rand_action(size_t sz)
{
   static size_t const MaxSize = 100;

   if(sz == 0)
   {
      return true;
   }

   if(sz >= MaxSize)
   {
      return false;
   }

   return rand() % 2;
}

int main()
{
   srand(time(0));

   StackMin stack;

   for(size_t i=0; i<10000000; ++i)
   {
      bool push = rand_action(stack.size());

      if( push )
      {
         stack.push( rand() % 100 );
      }
      else
      {
         stack.pop();
      }

      if( !stack.empty() && stack.min() != stack.xmin() )
      {
         abort();
      }
   }
}
