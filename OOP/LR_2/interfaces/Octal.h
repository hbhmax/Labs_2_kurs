#ifndef OCTAL_H
#define OCTAL_H

#include <string>
#include <stdexcept>
#include <vector>

class Octal {
private:
    std::vector<unsigned char> digits;
    size_t size;

    void removeLeadingZeros();
    bool isValidOctalDigit(unsigned char c) const;

public:
    Octal();
    Octal(const size_t& n, unsigned char t = 0);
    Octal(const std::initializer_list<unsigned char>& t);
    Octal(const std::string& t);
    Octal(const Octal& other);
    Octal(Octal&& other) noexcept;
    
    virtual ~Octal() noexcept;

    size_t getSize() const;
    unsigned char getDigit(size_t index) const;

    bool equals(const Octal& other) const;
    bool lessThan(const Octal& other) const;
    bool greaterThan(const Octal& other) const;

    Octal add(const Octal& other) const;
    Octal subtract(const Octal& other) const;
    Octal copy() const;

    Octal& addAssign(const Octal& other);
    Octal& subtractAssign(const Octal& other);

    std::string toString() const;
};

#endif