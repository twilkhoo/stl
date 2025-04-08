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


  tjs::vector<int> obj2({3, 4, 5, 6, 7});
  std::cout << "size: " << obj2.size() << ", capacity: " << obj2.capacity() << std::endl;

  std::cout << obj2[3] << std::endl;

  std::cout << obj2 << std::endl;

  tjs::vector<int> obj3 = obj2;
  std::cout << obj3 << std::endl;

  tjs::vector<int> obj4 = std::move(obj3);
  std::cout << obj4 << std::endl;

  std::cout << obj3 << std::endl;

}
