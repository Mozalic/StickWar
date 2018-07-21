#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <vector>

USING_NS_CC;

class BattleField : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	void FootmanButtonCallback(Ref *ref, ui::Widget::TouchEventType type);
	void FootmanGenrate();
	void update_soldier_move(float dt);
	void update_money(float dt);
	void enemy_soldier_generater(float dt);

	// implement the "static create()" method manually
	CREATE_FUNC(BattleField);
private:
	struct soldierItem {
		Sprite *soldier;
		float position;
		int type;//1 = Footman
	};
	int money;
	Label *moneyLabel;
	std::vector<soldierItem> soldiers;
	std::vector<soldierItem> enemy_soldiers;
	std::vector<SpriteFrame*> soldierFrames;
	float leftmost,rightmost;
	int time;
};

