#ifndef STRING_H
#define STRING_H

#include <cstring>
#include <cstdio>

class String {
private:
    char* buffer;
    int length_;
    int capacity_;

    void init(int capacity) {
        capacity_ = capacity;
        buffer = new char[capacity_];
        buffer[0] = '\0';
        length_ = 0;
    }

    void resize(int new_capacity) {
        if (new_capacity <= capacity_) return;
        
        char* new_buffer = new char[new_capacity];
        std::strcpy(new_buffer, buffer);
        delete[] buffer;
        buffer = new_buffer;
        capacity_ = new_capacity;
    }

public:
    // Constructors
    String() {
        init(16);
    }

    String(const char* cstr) {
        length_ = std::strlen(cstr);
        init(length_ > 0 ? length_ * 2 : 16);
        std::strcpy(buffer, cstr);
    }

    String(int num) {
        char temp[32];
        std::sprintf(temp, "%d", num);
        length_ = std::strlen(temp);
        init(length_ > 0 ? length_ * 2 : 16);
        std::strcpy(buffer, temp);
    }

    String(const String& other) {
        length_ = other.length_;
        init(length_ > 0 ? length_ * 2 : 16);
        std::strcpy(buffer, other.buffer);
    }

    // Destructor
    ~String() {
        delete[] buffer;
    }

    // Assignment operators
    String& operator=(const char* cstr) {
        length_ = std::strlen(cstr);
        if (length_ >= capacity_) {
            resize(length_ * 2);
        }
        std::strcpy(buffer, cstr);
        return *this;
    }

    String& operator=(int num) {
        char temp[32];
        std::sprintf(temp, "%d", num);
        length_ = std::strlen(temp);
        if (length_ >= capacity_) {
            resize(length_ * 2);
        }
        std::strcpy(buffer, temp);
        return *this;
    }

    String& operator=(const String& other) {
        if (this != &other) {
            length_ = other.length_;
            if (length_ >= capacity_) {
                resize(length_ * 2);
            }
            std::strcpy(buffer, other.buffer);
        }
        return *this;
    }

    // Concatenation
    String operator+(const String& other) const {
        String result;
        result.length_ = length_ + other.length_;
        if (result.length_ >= result.capacity_) {
            result.resize(result.length_ * 2);
        }
        std::strcpy(result.buffer, buffer);
        std::strcat(result.buffer, other.buffer);
        return result;
    }

    String operator+(const char* cstr) const {
        int cstr_len = std::strlen(cstr);
        String result;
        result.length_ = length_ + cstr_len;
        if (result.length_ >= result.capacity_) {
            result.resize(result.length_ * 2);
        }
        std::strcpy(result.buffer, buffer);
        std::strcat(result.buffer, cstr);
        return result;
    }

    String operator+(int num) const {
        char temp[32];
        std::sprintf(temp, "%d", num);
        int num_len = std::strlen(temp);
        String result;
        result.length_ = length_ + num_len;
        if (result.length_ >= result.capacity_) {
            result.resize(result.length_ * 2);
        }
        std::strcpy(result.buffer, buffer);
        std::strcat(result.buffer, temp);
        return result;
    }

    // Compound assignment
    String& operator+=(const String& other) {
        *this = *this + other;
        return *this;
    }

    String& operator+=(const char* cstr) {
        *this = *this + cstr;
        return *this;
    }

    String& operator+=(int num) {
        *this = *this + num;
        return *this;
    }

    // Comparison
    bool operator==(const String& other) const {
        if (length_ != other.length_) return false;
        return std::strcmp(buffer, other.buffer) == 0;
    }

    bool operator==(const char* cstr) const {
        return std::strcmp(buffer, cstr) == 0;
    }

    bool operator!=(const String& other) const {
        return !(*this == other);
    }

    // Access
    const char* c_str() const { return buffer; }
    int length() const { return length_; }
    bool isEmpty() const { return length_ == 0; }

    // Utility methods
    String substring(int start) const {
        if (start < 0) start = 0;
        if (start >= length_) return String("");
        
        int sub_len = length_ - start;
        String result;
        result.length_ = sub_len;
        if (result.length_ >= result.capacity_) {
            result.resize(result.length_ * 2);
        }
        std::strncpy(result.buffer, buffer + start, sub_len);
        result.buffer[sub_len] = '\0';
        return result;
    }
    
    String substring(int start, int end) const {
        if (start < 0) start = 0;
        if (end > length_) end = length_;
        if (start >= end) return String("");
        
        int sub_len = end - start;
        String result;
        result.length_ = sub_len;
        if (result.length_ >= result.capacity_) {
            result.resize(result.length_ * 2);
        }
        std::strncpy(result.buffer, buffer + start, sub_len);
        result.buffer[sub_len] = '\0';
        return result;
    }
    
    void trim() {
        // Find first non-whitespace
        int start = 0;
        while (start < length_ && std::isspace(buffer[start])) {
            start++;
        }
        
        // Find last non-whitespace
        int end = length_ - 1;
        while (end >= start && std::isspace(buffer[end])) {
            end--;
        }
        
        // If we found valid content
        if (start <= end) {
            int new_len = end - start + 1;
            std::memmove(buffer, buffer + start, new_len);
            buffer[new_len] = '\0';
            length_ = new_len;
        } else {
            // All whitespace or empty
            buffer[0] = '\0';
            length_ = 0;
        }
    }
    
    int toInt() const {
        return std::atoi(buffer);
    }
    
    long toLong() const {
        return std::atol(buffer);
    }
    
    float toFloat() const {
        return std::atof(buffer);
    }
};

// Mock Serial class for testing
class SerialMock {
public:
    static void begin(int baud) {}
    static void print(const char* str) { 
        // In real implementation, this would send to serial
        // For testing, we'll just ignore or could print to stdout
        // std::cout << str;
    }
    static void println(const char* str) { 
        // In real implementation, this would send to serial with newline
        // For testing, we'll just ignore or could print to stdout with newline
        // std::cout << str << std::endl;
    }
};

// Define Serial as our mock for testing
#define Serial SerialMock

#endif // STRING_H