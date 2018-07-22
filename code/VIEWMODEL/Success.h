#pragma once
#include "cocos2d.h"
#include "ui/cocosGUI.h"
#include <cocostudio/CocoStudio.h>

using namespace cocos2d::ui;

class success : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// selector callback
	void menubackCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(success);
};
