//
// Created by HORIA on 24.05.2024.
//

#ifndef IMAGEBANANA_OSOBJECT_H
#define IMAGEBANANA_OSOBJECT_H

#include <string>

// This class shall describe the os functions that the application will need
// The implementation shall be os specific

class OsObject {
public:
    virtual std::string getFileLocation() = 0;
    virtual ~OsObject() = default;
};

#endif //IMAGEBANANA_OSOBJECT_H
