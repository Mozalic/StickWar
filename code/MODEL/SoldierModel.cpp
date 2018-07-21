#include "SoldierModel.h"

soldierItem::soldierItem()
{
	soldier = NULL;
	position = 0;
	hp = type = 0;
}

soldierItem::soldierItem(Sprite * so, float pos, int HP, int Type)
{
	soldier = so;
	position = pos;
	hp = HP;
	type = Type;
}

soldierItem * soldierItem::getInstance()
{
	soldierItem* tmp;
	tmp = new soldierItem;
	return tmp;
}

soldierItem * soldierItem::getInstance(Sprite * so, float pos, int HP, int Type)
{
	soldierItem* tmp;
	tmp = new soldierItem;
	tmp->soldier = so;
	tmp->position = pos;
	tmp->hp = HP;
	tmp->type = Type;
	return tmp;
}

int soldierItem::getHp()
{
	return hp;
}

void soldierItem::setHp(int x)
{
	hp = x;
}

int soldierItem::getType()
{
	return type;
}

void soldierItem::setType(int x)
{
	type = x;
}

Sprite * soldierItem::getSoldier()
{
	return soldier;
}

float soldierItem::getPosition()
{
	return position;
}

void soldierItem::setPosition(float x)
{
	position = x;
}
