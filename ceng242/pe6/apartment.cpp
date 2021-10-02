#include <iostream>
#include "apartment.h"
#include "owner.h"

using namespace std;

Apartment::Apartment(const string &property_name, int area, Owner *owner, int floor, bool having_elevator)
{
    this->property_name = property_name;
    this->area = area;
    this->owner = owner;
    this->floor = floor;
    this->having_elevator = having_elevator;
    if(owner != NULL) owner->add_property(this);
}
float Apartment::valuate()
{
    float value = area * 10 * (((float) floor)/10);
    if(this->having_elevator) return value * 1.5;
    else return value;
}