#pragma once
#include <string>
#include <memory>

class Visitor;

class NPC {
public:
    virtual ~NPC() = default;
    
    virtual void accept(Visitor& visitor) = 0;
    virtual bool canAttack(const NPC& other) const = 0;
    virtual std::string getType() const = 0; // Добавлен метод
    
    int getX() const { return x_; }
    int getY() const { return y_; }
    const std::string& getName() const { return name_; }
    
    void setPosition(int x, int y) {
        x_ = x;
        y_ = y;
    }
    
protected:
    NPC(const std::string& name, int x, int y) : name_(name), x_(x), y_(y) {}
    
private:
    std::string name_;
    int x_;
    int y_;
};

class Knight : public NPC {
public:
    Knight(const std::string& name, int x, int y) : NPC(name, x, y) {}
    
    void accept(Visitor& visitor) override;
    bool canAttack(const NPC& other) const override;
    std::string getType() const override { return "Knight"; }
};

class Squirrel : public NPC {
public:
    Squirrel(const std::string& name, int x, int y) : NPC(name, x, y) {}
    
    void accept(Visitor& visitor) override;
    bool canAttack(const NPC& other) const override;
    std::string getType() const override { return "Squirrel"; }
};

class Pegasus : public NPC {
public:
    Pegasus(const std::string& name, int x, int y) : NPC(name, x, y) {}
    
    void accept(Visitor& visitor) override;
    bool canAttack(const NPC& other) const override;
    std::string getType() const override { return "Pegasus"; }
};