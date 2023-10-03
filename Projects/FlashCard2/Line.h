#pragma once
#ifndef LINE_H
#define LINE_H

#endif // LINE_H
#include <string>

struct Line {
    std::string english;
    std::string italian;
    int count;
    int id;

    bool operator == (const Line& l) {
        return l.english == english && l.italian == italian && l.count == count;
    }

};
