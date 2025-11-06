#include "../interfaces/Octal.h"
#include <algorithm>
#include <sstream>

using namespace std;

void Octal::removeLeadingZeros() {
    while (digits.size() > 1 && digits.back() == 0) {
        digits.pop_back();
    }
    size = digits.size();
}

bool Octal::isValidOctalDigit(unsigned char c) const {
    return c >= 0 && c <= 7;
}

Octal::Octal() {
    size = 1;
    digits.push_back(0);
}

Octal::Octal(const size_t& n, unsigned char t) {
    if (n == 0) throw invalid_argument("Size must be positive");
    if (!isValidOctalDigit(t)) throw invalid_argument("Invalid octal digit");
    
    size = n;
    digits = vector<unsigned char>(n, t);
    removeLeadingZeros();
}

Octal::Octal(const initializer_list<unsigned char>& t) {
    if (t.size() == 0) throw invalid_argument("Initializer list is empty");
    
    for (initializer_list<unsigned char>::iterator it = t.begin(); it != t.end(); it++) {
        unsigned char digit = *it;
        if (!isValidOctalDigit(digit)) throw invalid_argument("Invalid octal digit");
        digits.push_back(digit);
    }
    size = digits.size();
    reverse(digits.begin(), digits.end());
    removeLeadingZeros();
}

Octal::Octal(const string& t) {
    if (t.empty()) throw invalid_argument("String is empty");
    
    for (string::const_reverse_iterator it = t.rbegin(); it != t.rend(); it++) {
        unsigned char digit = *it - '0';
        if (!isValidOctalDigit(digit)) throw invalid_argument("Invalid octal digit in string");
        digits.push_back(digit);
    }
    size = digits.size();
    removeLeadingZeros();
}

Octal::Octal(const Octal& other) {
    digits = other.digits;
    size = other.size;
}

Octal::Octal(Octal&& other) noexcept {
    digits = move(other.digits);
    size = other.size;
    other.size = 0;
    other.digits.clear();
}

Octal::~Octal() noexcept {}

size_t Octal::getSize() const { 
    return size; 
}

unsigned char Octal::getDigit(size_t index) const {
    if (index >= size) throw out_of_range("Index out of range");
    return digits[index];
}

bool Octal::equals(const Octal& other) const {
    if (size != other.size) return false;
    for (size_t i = 0; i < size; i++) {
        if (digits[i] != other.digits[i]) return false;
    }
    return true;
}

bool Octal::lessThan(const Octal& other) const {
    if (size != other.size) return size < other.size;
    
    for (int i = size - 1; i >= 0; i--) {
        if (digits[i] != other.digits[i]) 
            return digits[i] < other.digits[i];
    }
    return false;
}

bool Octal::greaterThan(const Octal& other) const {
    if (size != other.size) return size > other.size;
    
    for (int i = size - 1; i >= 0; i--) {
        if (digits[i] != other.digits[i]) 
            return digits[i] > other.digits[i];
    }
    return false;
}

Octal Octal::add(const Octal& other) const {
    vector<unsigned char> result;
    unsigned char carry = 0;
    size_t maxSize = max(size, other.size);
    
    for (size_t i = 0; i < maxSize || carry != 0; i++) {
        unsigned char sum = carry;
        if (i < size) sum += digits[i];
        if (i < other.size) sum += other.digits[i];
        
        result.push_back(sum % 8);
        carry = sum / 8;
    }
    
    Octal res;
    res.digits = result;
    res.size = result.size();
    return res;
}

Octal Octal::subtract(const Octal& other) const {
    if (lessThan(other)) throw invalid_argument("Result would be negative");
    
    vector<unsigned char> result;
    unsigned char borrow = 0;
    
    for (size_t i = 0; i < size; i++) {
        int current = digits[i] - borrow;
        int otherDigit = (i < other.size) ? other.digits[i] : 0;
        
        if (current < otherDigit) {
            current += 8;
            borrow = 1;
        } else {
            borrow = 0;
        }
        
        result.push_back(current - otherDigit);
    }
    
    Octal res;
    res.digits = result;
    res.size = result.size();
    res.removeLeadingZeros();
    return res;
}

Octal Octal::copy() const {
    return Octal(*this);
}

Octal& Octal::addAssign(const Octal& other) {
    Octal temp = this->add(other);
    this->digits = move(temp.digits);
    this->size = temp.size;
    
    return *this;
}

Octal& Octal::subtractAssign(const Octal& other) {
    Octal temp = this->subtract(other);
    this->digits = move(temp.digits);
    this->size = temp.size;
    
    return *this;
}


string Octal::toString() const {
    if (size == 0) return "0";
    
    stringstream ss;
    for (int i = size - 1; i >= 0; i--) {
        ss << (int)digits[i];
    }
    return ss.str();
}