#include <iostream>
#include <string>
#include <vector>
#include "owner.h"

using namespace std;

Owner::Owner()
{
}

Owner::Owner(const string &name, float balance)
{
    this->name = name;
    this->balance = balance;
}

void Owner::print_info()
{
    this->print_info();
}

string &Owner::get_name()
{
    return this->name;
}

void Owner::add_property(Property *property)
{
    this->properties.push_back(property);
}

void Owner::buy(Property *property, Owner *seller)
{
    float value = property->valuate();
    std::cout << "[BUY] Property: " << property->get_name() << " Value: " << value << "$ " << seller->get_name() << "--->" << this->get_name() << std::endl;

    if(this->balance >= value){
        bool isOwner = false;
        for(unsigned int i = 0; i < seller->properties.size(); i++)
        {
            if((seller->properties)[i] == property)
            {
                (seller->properties).erase((seller->properties).begin()+i);
                isOwner = true;
                break;
            }
        }
        if(isOwner)
        {
            seller->balance += value;
            this->balance -= value;
            this->add_property(property);
        }
        else std::cout << "[ERROR] Transaction  on  unowned  property" << std::endl;
    }
    else std::cout << "[ERROR] Unaffordable  property" << std::endl;
}

void Owner::sell(Property *property, Owner *owner)
{
    float value = property->valuate();
    std::cout << "[SELL] Property: " << property->get_name() << " Value: " << value << "$ " << this->get_name() << "--->" << owner->get_name() << std::endl;
    if(owner->balance >= value){
        bool isOwner = false;
        for(unsigned int i = 0; i < this->properties.size(); i++)
        {
            if((this->properties)[i] == property)
            {
                (this->properties).erase((this->properties).begin()+i);
                isOwner = true;
                break;
            }
        }
        if(isOwner)
        {
            this->balance += value;
            owner->balance -= value;
            owner->add_property(property);
        }
        else std::cout << "[ERROR] Transaction  on  unowned  property" << std::endl;
    }
    else std::cout << "[ERROR] Unaffordable  property" << std::endl;
}

void Owner::list_properties()
{
    std::cout << "Properties of " << this->name << ":" << std::endl;
    std::cout << "Balance: " << this->balance << "$" << std::endl;
    
    for(unsigned int i = 0; i < this->properties.size(); i++)
    {
        std::cout << i+1 << ". " << (this->properties[i])->get_name() << std::endl;
    }
    
}


