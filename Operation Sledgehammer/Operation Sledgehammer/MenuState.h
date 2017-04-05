#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "GameState.h"

class MenuState : public GameState
{
public:
    
    virtual ~MenuState() {}
    
protected:
    
    typedef void(*Callback)();
    virtual void setCallbacks(const std::vector<Callback>& callbacks) = 0;
    
    std::vector<Callback> m_callbacks;
};


#endif//DEFINED MENU_STATE_H
