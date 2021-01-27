#include "textproperty.h"

TextProperty::TextProperty()
{
}

TextProperty::TextProperty(int place, fontChange proberty)
    :mPlace{place}
    , mProberty{proberty}
{
}

int TextProperty::getPosition(){
    return mPlace;
}

fontChange TextProperty::getProperty() {
    return mProberty;
}

