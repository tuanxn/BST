// Student ID: 20274909

#include "BST.h"
#include "Lazy_BST.h"
#include <iostream>

using namespace std;

int main()
{


   Lazy_BST<int> test = Lazy_BST<int>();
   test.insert(6);
   test.insert(3);
   test.insert(1);
   test.insert(5);
   test.insert(8);
   test.insert(7);
   test.insert(9);




   test.remove(6);

   cout << test.to_string();

   test.collect_garbage();

   cout << test.to_string();


}

