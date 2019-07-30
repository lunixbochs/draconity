#pragma once
#include <string>

class SymbolLoad {
public:
    SymbolLoad(const std::string name) {
        this->name = name;
        this->loaded = false;
    }

    virtual void setAddr(uintptr_t addr);
    std::string name;
    bool loaded;
private:
};

template <typename F>
class TypedSymbolLoad : public SymbolLoad {
public:
    TypedSymbolLoad(std::string name, F *ptr) : SymbolLoad(name) {
        this->ptr = ptr;
    }

    void setAddr(uintptr_t addr) override {
        *this->ptr = reinterpret_cast<F>(addr);
        this->loaded = true;
    };
private:
    F *ptr;
};

template <typename F>
SymbolLoad makeSymbolLoad(std::string name, F *ptr) {
    return TypedSymbolLoad<F>(name, ptr);
}
