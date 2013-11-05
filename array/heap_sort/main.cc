#include <algorithm>

int left(int p)
{
   // (p + 1) * 2 - 1 = 2 * p + 2 - 1 = 2 * p + 1
   return 2 * p + 1;
}

int right(int p)
{
   return left(p) + 1;
}

void sift_down(int a[], int len)
{
   int p = 0;
   int l = left(p);
   int r = right(p);
   int max = p;

   for (;;)
   {
      if (l < len && a[l] > a[max])
         max = l;

      if (r < len && a[r] > a[max])
         max = r;

      if (p == max)
         break;

      std::swap(a[p], a[max]);
      p = max;
   }
}

void build_heap(int a[], int len)
{
   if (len <= 1)
      return;

   for (int i = len / 2; i >= 0; --i)
      sift_down(a + i, len - i);
}

void hsort(int a[], int len)
{
   if (len < 2)
      return;

   build_heap(a, len);

   for (int i = len - 1; i > 0; --i) {
      std::swap(a[i], a[0]);
      sift_down(a, i);
   }
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
   Array b(2);
   b[0] = 0;
   b[1] = 1;
   return b;

   Array a(len);

   for (int i = 0; i < len; ++i)
      a[i] = rand();

   return a;
}

void test(int len)
{
   Array a = make(len);
   Array b = a;

   hsort(a.data(), a.size());

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
