#pragma once

#include <cstdint>

class UIManagerBase
{
public:
    static const uint8_t kCuiBit = 1;
    static const uint8_t kGuiBit = 2;

public:
    static UIManagerBase* GetInstance(uint8_t ui_type);

public:
    UIManagerBase();
    virtual ~UIManagerBase();
    
private:

};
