#pragma once

#include "UIType.hpp"

class UIManagerBase
{
public:
    UIManagerBase();
    virtual ~UIManagerBase();
    static UIManagerBase* GetInstance(UIType type);
    
private:

};
