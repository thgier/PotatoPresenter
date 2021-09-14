/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#ifndef PARSER_H
#define PARSER_H

#include "presentation.h"
#include "potatoformatvisitor.h"

#include <QFile>
#include <QString>


struct ParserOutput {
    std::optional<ParserError> mParserError;
    std::optional<SlideList> mSlideList;
    std::optional<Preamble> mPreamble;

    ParserOutput(ParserError error) {
        mParserError = error;
    }
    ParserOutput(SlideList slideList, Preamble preamble) {
        mSlideList = slideList;
        mPreamble = preamble;
    }

    bool successfull() const {
        return !mParserError.has_value();
    }
    ParserError parserError() const {
        return mParserError.value_or(ParserError{"", 0});
    }
    SlideList slideList() const {
        return mSlideList.value_or(SlideList());
    }
    Preamble preamble() const {
        return mPreamble.value_or(Preamble{""});
    }
};


ParserOutput generateSlides(std::string text, QString directory, bool isTemplate=false);


#endif // PARSER_H
