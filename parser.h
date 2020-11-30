#ifndef PARSER_H
#define PARSER_H

#include <QFile>
#include <vector>
#include<QString>
#include "frame.h"
#include "configboxes.h"


using FrameList = std::vector<std::shared_ptr<Frame>>;
class Parser : public QObject
{
    Q_OBJECT
public:
    Parser();
    std::optional<FrameList> readJson(QString text, ConfigBoxes* configuration);
private:
};

#endif // PARSER_H
