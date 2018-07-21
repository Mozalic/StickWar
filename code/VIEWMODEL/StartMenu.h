#ifndef __STARTMENU__
#define __STARTMENU__

#include "cocos2d.h"

class StartMenu : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	void menuOptionCallback(cocos2d::Ref* pSender);
	void menuStartCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(StartMenu);
};

#endif // __STARTMENU__
