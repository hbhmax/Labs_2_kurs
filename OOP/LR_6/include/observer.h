#pragma once
#include <string>
#include <fstream>
#include <vector>

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const std::string& message) = 0;
};

class ConsoleObserver : public Observer {
public:
    ConsoleObserver() = default;
    void update(const std::string& message) override;
};

class FileObserver : public Observer {
public:
    explicit FileObserver(const std::string& filename);
    ~FileObserver();
    void update(const std::string& message) override;
    
private:
    std::string filename_;
    std::ofstream file_;
};
