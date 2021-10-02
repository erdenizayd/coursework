#include <iostream>
#include "office.h"
#include "owner.h"

using namespace std;

Office::Office(const string &property_name, int area, Owner *owner, bool having_wifi, bool having_reception)
{
    this->property_name = property_name;
    this->area = area;
    this->owner = owner;
    this->having_wifi = having_wifi;
    this->having_reception = having_reception;
    if(owner != NULL) owner->add_property(this);
}

float Office::valuate()
{
    float value = this->area * 5;
    
    if(this->having_wifi && this->having_reception) return value * 1.3 * 1.5;
    else if (this->having_wifi) return value * 1.3;
    else if (this->having_reception) return value * 1.5;
    else return value;
    
}