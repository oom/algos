#include <ctime>
#include <cstdlib>

#include <list>
#include <algorithm>

class QueueMin
{
public:
   void push( int x )
   {
      while( !m_min.empty() && m_min.back() > x )
      {
         m_min.pop_back();
      }

      m_queue.push_back( x );
      m_min.push_back( x );
   }

   void pop()
   {
      if( m_min.front() == m_queue.front() )
      {
         m_min.pop_front();
      }

      m_queue.pop_front();
   }

   bool empty()
   {
      return m_queue.empty();
   }

   size_t size() const
   {
      return m_queue.size();
   }

   int front() const
   {
      return m_queue.front();
   }

   int min() const
   {
      return m_min.front();
   }

   int xmin() const
   {
      return *std::min_element(m_queue.begin(), m_queue.end());
   }

private:
   std::list< int > m_queue;
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

   QueueMin queue;

   for(size_t i=0; i<10000000; ++i)
   {
      bool push = rand_action(queue.size());

      if( push )
      {
         queue.push( rand() % 100 );
      }
      else
      {
         queue.pop();
      }

      if( !queue.empty() && queue.min() != queue.xmin() )
      {
         abort();
      }
   }
}
