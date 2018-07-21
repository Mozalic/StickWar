#pragma once
#include "cocos2d.h"
#include "ui/cocosGUI.h"
#include <cocostudio/CocoStudio.h>

using namespace cocos2d::ui;

class option : public cocos2d::Scene
{
private:
	RadioButton *checkbox1, *checkbox2;
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// selector callback
	void menubackCallback(cocos2d::Ref* pSender);

	void buttonchange1(RadioButton* radioButton, RadioButton::EventType type);
	void buttonchange2(RadioButton* radioButton, RadioButton::EventType type);

//	void checkBox1Callback(cocos2d::Ref * ref, cocos2d::ui::CheckBox::EventType type);
//	void checkBox2Callback(cocos2d::Ref * ref, cocos2d::ui::CheckBox::EventType type);
	
	/*void checkBox2Callback(cocos2d::Ref * ref, cocos2d::ui::CheckBox::EventType type);*/
	// implement the "static create()" method manually
	CREATE_FUNC(option);
};
