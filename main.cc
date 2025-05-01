#include <iostream>
#include "ref_ptr.hh"


class TestClass {
    public:
        TestClass() { std::cout << "Test Class created\n"; }
        ~TestClass() { std::cout << "Test Class Destroyed\n"; }

        void print() {
            std::cout << "Test class printed something!\n"; 
        }
};


int main() {
    RefPtr<TestClass> primaryPtr(new TestClass());
    primaryPtr->print();

    {
        RefPtr<TestClass> copyPtr = primaryPtr;
        copyPtr->print();
        std::cout << "Inside scope, use count: " << copyPtr.use_count() << std::endl;
    }

    std::cout << "Outside scope, use count: " << primaryPtr.use_count() << std::endl;

    return 0;
}