#ifndef PROPERTY_H
#define PROPERTY_H

enum fontChange {
    boldStart,
    boldEnd,
    italicStart,
    italicEnd,
    newLine,
    itemize,
    teXStart,
    teXEnd,
    empty,
//    underline,
};

class TextProperty
{
public:
    TextProperty();
    TextProperty(int place, fontChange proberty);
    fontChange getProperty();
    int getPosition();
private:
    int mPlace;
    fontChange mProberty;
};

#endif // PROPERTY_H
