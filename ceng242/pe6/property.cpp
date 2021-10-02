#include <iostream>
#include "property.h"
#include "owner.h"

using namespace std;

Property::Property()
{
    owner = NULL;
}

Property::Property(const string &property_name, int area, Owner *owner)
{
    this->property_name = property_name;
    this->area = area;
    this->owner = owner;
}

void Property::set_owner(Owner *owner)
{
    this->owner = owner;
}

float Property::valuate()
{
    return this->valuate();
}

string &Property::get_name()
{
    return this->property_name;
}

void Property::print_info()
{
    if(owner != NULL) 
    {
        std::cout << this->property_name << " (" << this->area << " m2) Owner: " << this->owner->get_name() << std::endl;
    }
    else 
    {
        std::cout << this->property_name << " (" << this->area << " m2) Owner: No owner" << std::endl;
    }
}