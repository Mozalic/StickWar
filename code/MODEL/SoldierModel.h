#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

#define FootmanHP 100

class soldierItem {
private:
	Sprite *soldier;
	float position;
	int hp;
	int type;//1 = Footman
public:
	soldierItem();
	soldierItem(Sprite* so,float pos,int HP, int Type);

	static soldierItem* getInstance();
	static soldierItem* getInstance(Sprite* so, float pos, int HP, int Type);
	int getHp();
	void setHp(int x);
	int getType();
	void setType(int x);
	Sprite* getSoldier();
	float getPosition();
	void setPosition(float x);
};