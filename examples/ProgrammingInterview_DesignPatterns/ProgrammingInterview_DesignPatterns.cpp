// see https://refactoring.guru/design-patterns/abstract-factory/cpp/example
#include <iostream>

class Pizza
{
public:
    Pizza() = default;
     ~Pizza() { std::cout << "Pizza - Destructor" << std::endl; };
    virtual void prepare() = 0;
    virtual void bake() = 0;
};


class NYStylePizza : public Pizza
{
public:
    NYStylePizza() = default;
    virtual ~NYStylePizza() { std::cout << "NYStylePizza - Destructor" << std::endl; };
    void prepare() override {
        std::cout << "NYStylePizze - prepare" << std::endl;} ;
    void bake() override {
        std::cout << "NYStylePizze - bake" << std::endl;
    };
};


class PizzaStore
{
public:
    virtual Pizza* createPizza() = 0;
    virtual ~PizzaStore() { std::cout << "PizzaStore - Destructor" << std::endl; };
    void orderPizza() {
        std::cout << "Pizza Store - order" << std::endl;
    };
};


class NYPizzaStore : public PizzaStore
{
public:
    Pizza* createPizza() override {
        return new NYStylePizza();
    };

};


int main()
{
    NYPizzaStore nyps;
    Pizza* p = nyps.createPizza();  //creates NY style pizza
    p->prepare();
    p->bake();
    delete p;
}



