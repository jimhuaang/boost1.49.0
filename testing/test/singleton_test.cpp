
#include <iostream>

#include "Singleton.hpp"

class MyClass : public Singleton<MyClass> {
public:
  void MyMethod();
private:
  MyClass() : Singleton<MyClass>() {}
 // ~MyClass() { }

friend class Singleton<MyClass>;
};

void MyClass::MyMethod() {
  std::cout << "My singleton class" << std::endl;
}

int main() {
  MyClass::Instance().MyMethod();
  //MyClass a;
}
