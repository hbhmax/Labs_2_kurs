#include "../include/observer.h"
#include <iostream>
#include <fstream>
#include <ctime>

void ConsoleObserver::update(const std::string& message) {
    std::time_t now = std::time(0);
    char buffer[30];
    std::strftime(buffer, 30, "%H:%M:%S", std::localtime(&now));
    
    std::cout << "[" << buffer << "] EVENT: " << message << std::endl;
}

FileObserver::FileObserver(const std::string& filename)
    : filename_(filename) {
    file_.open(filename_, std::ios::app);
    if (!file_.is_open()) {
        std::cerr << "Error opening file for writing: " << filename_ << std::endl;
    }
}

FileObserver::~FileObserver() {
    if (file_.is_open()) {
        file_.close();
    }
}

void FileObserver::update(const std::string& message) {
    if (!file_.is_open()) {
        return;
    }
    
    std::time_t now = std::time(0);
    char buffer[30];
    std::strftime(buffer, 30, "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    
    file_ << "[" << buffer << "] EVENT: " << message << std::endl;
}