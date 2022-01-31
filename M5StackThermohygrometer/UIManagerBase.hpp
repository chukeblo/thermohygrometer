#pragma once

#include "UIType.hpp"

class UIManagerBase
{
public:
    static UIManagerBase* GetInstance(UIType type);

public:
    UIManagerBase();
    virtual ~UIManagerBase();
    
private:

};
