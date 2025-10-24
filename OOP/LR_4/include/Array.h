#ifndef ARRAY_H
#define ARRAY_H

#include <memory>

template<typename T>
class Array {
private:
    std::shared_ptr<T[]> data;
    size_t size_;
    size_t capacity_;
    
public:
    Array() : size_(0), capacity_(0), data(nullptr) {}
    
    void push_back(const T& value) {
        if (size_ >= capacity_) {
            size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
            std::shared_ptr<T[]> new_data(new T[new_capacity]);
            
            for (size_t i = 0; i < size_; ++i) {
                new_data[i] = std::move(data[i]);
            }
            
            data = new_data;
            capacity_ = new_capacity;
        }
        data[size_++] = value;
    }
    
    void erase(size_t index) {
        if (index >= size_) return;
        
        for (size_t i = index; i < size_ - 1; ++i) {
            data[i] = std::move(data[i + 1]);
        }
        --size_;
    }
    
    T& operator[](size_t index) {
        return data[index];
    }
    
    const T& operator[](size_t index) const {
        return data[index];
    }
    
    size_t size() const {
        return size_;
    }
};

#endif