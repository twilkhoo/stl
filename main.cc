#include <iostream>

#include "vector/vector.h"  // your own library

int main() {
  tjs::vector<int> obj;
  std::cout << "size: " << obj.size() << ", capacity: " << obj.capacity() << std::endl;

  obj.push_back(3);
  std::cout << "size: " << obj.size() << ", capacity: " << obj.capacity() << std::endl;


  obj.push_back(1);
  std::cout << "size: " << obj.size() << ", capacity: " << obj.capacity() << std::endl;

  obj.push_back(1);
  std::cout << "size: " << obj.size() << ", capacity: " << obj.capacity() << std::endl;

}
