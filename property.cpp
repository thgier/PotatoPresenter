#include "property.h"

Property::Property()
{
}

Property::Property(int place, fontChange proberty)
    :mPlace{place}
    , mProberty{proberty}
{
}

int Property::getPosition(){
    return mPlace;
}

fontChange Property::getProperty() {
    return mProberty;
}

