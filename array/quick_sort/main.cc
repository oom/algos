#include <algorithm>

int partition(int a[], int len, int p)
{
   std::swap(a[p], a[len-1]);
   int s = 0;

   for (int i = 0; i < len - 1; ++i)
      if (a[i] < a[len-1])
         std::swap(a[s++], a[i]);

   std::swap(a[s], a[len-1]);
   return s;
}

void qsort(int a[], int len)
{
   if (len <= 1)
      return;

   int p = rand() % len;
   p = partition(a, len, p);

   qsort(a, p);
   qsort(a + p + 1, len - p - 1);
}

// -- TEST
#include "array.h"
#include <iostream>

bool is_sorted(int a[], int len)
{
   for (int i = 1; i < len; ++i)
      if (a[i - 1] > a[i] )
         return false;

   return true;
}

Array make(int len)
{
   Array a(len);

   for (int i = 0; i < len; ++i)
      a[i] = rand();

   return a;
}

void test(int len)
{
   Array a = make(len);
   Array b = a;

   qsort(a.data(), a.size());

   if (!is_sorted(a.data(), a.size()))
   {
      std::cout << b << '\n' << a << std::endl;
      abort();
   }
}

int main()
{
   srand(time(0));

   test(0);
   test(1);

   for (int len = 2; len < 20; ++len)
      for (int loop = 0; loop < 1000000; ++loop)
         test(len);
}
