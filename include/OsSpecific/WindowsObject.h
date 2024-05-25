//
// Created by HORIA on 24.05.2024.
//

#ifndef IMAGEBANANA_WINDOWSOBJECT_H
#define IMAGEBANANA_WINDOWSOBJECT_H

#include "OsObject.h"
#include <string>

//Here lies the OS specific implementation of functions we need

class WindowsObject : public OsObject {
public:
    std::string getFileLocation() override;
    ~WindowsObject() override;

private:
};

#endif //IMAGEBANANA_WINDOWSOBJECT_H
