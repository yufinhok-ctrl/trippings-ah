#include "String.h"
#include <iostream>

int main() {
    // Test basic construction
    String s1;
    String s2("Hello");
    String s3(42);
    String s4(s2);
    
    // Test assignment
    s1 = "World";
    s2 = 123;
    s3 = s1;
    
    // Test concatenation
    String s5 = s1 + " " + s2;
    String s6 = s3 + " is the answer";
    
    // Test comparison
    if (s2 == "123") {
        std::cout << "s2 equals 123" << std::endl;
    }
    
    if (s1 != s2) {
        std::cout << "s1 does not equal s2" << std::endl;
    }
    
    // Test output
    std::cout << "s1: " << s1.c_str() << std::endl;
    std::cout << "s2: " << s2.c_str() << std::endl;
    std::cout << "s3: " << s3.c_str() << std::endl;
    std::cout << "s4: " << s4.c_str() << std::endl;
    std::cout << "s5: " << s5.c_str() << std::endl;
    std::cout << "s6: " << s6.c_str() << std::endl;
    
    // Test substring
    String s7 = s5.substring(0, 5);
    std::cout << "s7 (substring of s5): " << s7.c_str() << std::endl;
    
    // Test trim
    String s8("   Hello World   ");
    s8.trim();
    std::cout << "s8 (trimmed): '" << s8.c_str() << "'" << std::endl;
    
    // Test numeric conversion
    String s9("42");
    int i = s9.toInt();
    std::cout << "s9 as int: " << i << std::endl;
    
    return 0;
}