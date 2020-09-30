#ifndef PROPERTY_H
#define PROPERTY_H

enum fontChange {
    boldStart,
    boldEnd,
    italicStart,
    italicEnd,
    newLine,
    itemize,
    empty,
//    underline,
};

class Property
{
public:
    Property();
    Property(int place, fontChange proberty);
    fontChange getProperty();
    int getPosition();
private:
    int mPlace;
    fontChange mProberty;
};

#endif // PROPERTY_H
