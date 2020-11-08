#ifndef PARSER_H
#define PARSER_H

#include <QFile>
#include <vector>
#include<QString>
#include "frame.h"
#include "configboxes.h"


class Parser : public QObject
{
    Q_OBJECT
public:
    Parser();
    std::vector<std::shared_ptr<Frame>> readJson(QString text, ConfigBoxes* configuration);
private:
};

#endif // PARSER_H
