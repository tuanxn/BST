// Student ID: 20274909

#include "BST.h"
#include "Lazy_BST.h"
#include <iostream>

using namespace std;

int main()
{


   Lazy_BST<int> test = Lazy_BST<int>();
   test.insert(20);
   test.insert(16);
   test.insert(5);
   test.insert(3);
   test.insert(8);
   test.insert(10);
   test.insert(15);
   test.insert(11);
   test.remove(5);
   test.remove(3);
   test.remove(8);
   test.remove(10);

   cout << std::to_string(test.get_min());
}

