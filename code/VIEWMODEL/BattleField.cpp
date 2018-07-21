
#include "BattleField.h"
#include "SimpleAudioEngine.h"
#include <iostream>

USING_NS_CC;

Scene* BattleField::createScene()
{
	return BattleField::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool BattleField::init() {
	if (!Scene::init())return false;

	leftmost = 0;
	rightmost = 850;
	money = 0;
	time = 0;

	auto dirs = Director::getInstance();
	Size visibleSize = dirs->getVisibleSize();

	auto spritecache = SpriteFrameCache::getInstance()->getSpriteFrameByName("Footman-1.png");
	soldierFrames.push_back(spritecache);
	
	auto backGround = Sprite::create("BattleField_BG.png");
	backGround->setPosition(Vec2(
		visibleSize.width / 2,
		visibleSize.height / 2
	));
	backGround->setScale(1.1);
	this->addChild(backGround);
	
	auto label1 = Label::createWithTTF(std::to_string(money), "fonts/arial.ttf", 24);
	label1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height-label1->getContentSize().height));
	label1->setColor(Color3B(0, 0, 0));
	moneyLabel = label1;
	this->addChild(label1);

	auto MinerButton = ui::Button::create(
		"Miner_btn_normal.png", "Miner_btn_selected.png", "Miner_btn_selected.png");
	MinerButton->setPosition(Vec2(
		MinerButton->getContentSize().width*0.5,
		visibleSize.height - MinerButton->getContentSize().height / 2));
	//FootmanButton->getContentSize();
	MinerButton->addTouchEventListener(CC_CALLBACK_2(
		BattleField::MinerButtonCallback,
		this));
	this->addChild(MinerButton,1);

	auto FootmanButton = ui::Button::create(
		"footman_btn_normal.png", "footman_btn_selected.png", "footman_btn_selected.png");
	FootmanButton->setPosition(Vec2(
		FootmanButton->getContentSize().width*1.5,
		visibleSize.height - FootmanButton->getContentSize().height / 2));
	//FootmanButton->getContentSize();
	FootmanButton->addTouchEventListener(CC_CALLBACK_2(
		BattleField::FootmanButtonCallback,
		this));
	this->addChild(FootmanButton);
	/*
	auto LM1 = Label::createWithTTF(std::to_string(leftmost), "fonts/arial.ttf", 24);
	auto RM1 = Label::createWithTTF(std::to_string(rightmost), "fonts/arial.ttf", 24);
	LM = LM1;
	RM = RM1;
	LM->setPosition(Vec2(visibleSize.width / 2, 400));
	RM->setPosition(Vec2(visibleSize.width / 2, 300));
	LM->setColor(Color3B(0, 0, 0));
	RM->setColor(Color3B(0, 0, 0));
	this->addChild(LM);
	this->addChild(RM);
	*/
	this->schedule(schedule_selector(BattleField::update_soldier_move), 0.1);
	this->schedule(schedule_selector(BattleField::update_money), 1);
	this->schedule(schedule_selector(BattleField::enemy_soldier_generater), 1);
}


void BattleField::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}

void BattleField::FootmanButtonCallback(Ref * ref, ui::Widget::TouchEventType type)
{
	switch (type) {
	case ui::Widget::TouchEventType::BEGAN:
		break;
	case ui::Widget::TouchEventType::ENDED:
		FootmanGenrate();
		break;
		default:
			break;
	}
}

void BattleField::MinerButtonCallback(Ref * ref, ui::Widget::TouchEventType type)
{
	if (money < 5)return;
}

void BattleField::FootmanGenrate()
{
	if (money < 10)return;
	money -= 10;
	auto Footman = Sprite::create("Footman.png");
	Footman->setAnchorPoint(Vec2(0, 0));
	Footman->setPosition(Vec2(0, 30* CCRANDOM_0_1()));
	soldierItem* tmp=soldierItem::getInstance(Footman,0,FootmanHP,1);
	soldiers.push_back(tmp);
	this->addChild(Footman);
}

void BattleField::update_soldier_move(float dt) {
	const int step = 10;
	//LM->setString(std::to_string(leftmost));
	//RM->setString(std::to_string(rightmost));
	moneyLabel->setString(std::to_string(money));
	auto moveleft = MoveBy::create(0.1, Vec2(step, 0));
	auto moveright = MoveBy::create(0.1, Vec2(-1*step, 0));
	int maxn = 0;
	for (int i = 0; i < soldiers.size(); i++) {
		if (soldiers[i]->getPosition()+soldiers[i]->getSoldier()->getContentSize().width < rightmost) {
			soldiers[i]->getSoldier()->runAction(MoveBy::create(0.1, Vec2(step, 0)));
			soldiers[i]->setPosition(soldiers[i]->getPosition() + step);
			if (soldiers[i]->getPosition() > leftmost) {
				leftmost = soldiers[i]->getPosition();
			}
		}
		maxn = max(maxn, soldiers[i]->getPosition());
	}
	leftmost = maxn;
	maxn = 960;
	for (int i = 0; i < enemy_soldiers.size(); i++) {
		//enemy_soldiers[i].soldier->runAction(MoveBy::create(0.1, Vec2(-1 * step, 0)));
		if (enemy_soldiers[i]->getPosition() > leftmost + enemy_soldiers[i]->getSoldier()->getContentSize().width) {
			enemy_soldiers[i]->getSoldier()->runAction(MoveBy::create(0.1, Vec2(-1 * step, 0)));
			enemy_soldiers[i]->setPosition(enemy_soldiers[i]->getPosition() - step);
			if (enemy_soldiers[i]->getPosition() < rightmost) {
				rightmost = enemy_soldiers[i]->getPosition();
			}
		}
		maxn = min(maxn, enemy_soldiers[i]->getPosition());
	}
	rightmost = maxn;
	int scnt = 0, sdmg = 0;
	for (int i = 0; i < soldiers.size(); i++) {
		if (soldiers[i]->getPosition() + soldiers[i]->getSoldier()->getContentSize().width < rightmost)continue;
		scnt++; sdmg += getDMG(soldiers[i]->getType());
	}
	int dmgtoe = sdmg / (scnt==0?1:scnt);
	int ecnt = 0, edmg = 0;
	for (int i = 0; i < enemy_soldiers.size(); i++) {
		if (enemy_soldiers[i]->getPosition() > leftmost + enemy_soldiers[i]->getSoldier()->getContentSize().width)continue;
		ecnt++; edmg += getDMG(enemy_soldiers[i]->getType());
	}
	int dmgtos = edmg / (ecnt==0?1:ecnt);
	for (int i = 0; i < soldiers.size(); i++) {
		if (soldiers[i]->getPosition() + soldiers[i]->getSoldier()->getContentSize().width < rightmost)continue;
		if (soldiers[i]->getHp() < dmgtos) {
			this->removeChild(soldiers[i]->getSoldier());
			delete soldiers[i];
			soldiers.erase(soldiers.begin() + i);
			i--;
		}
		else soldiers[i]->setHp(soldiers[i]->getHp() - dmgtos);
	}
	for (int i = 0; i < enemy_soldiers.size(); i++) {
		if (enemy_soldiers[i]->getPosition() > leftmost + enemy_soldiers[i]->getSoldier()->getContentSize().width)continue;
		if (enemy_soldiers[i]->getHp() < dmgtos) {
			this->removeChild(enemy_soldiers[i]->getSoldier());
			delete enemy_soldiers[i];
			enemy_soldiers.erase(enemy_soldiers.begin() + i);
			i--;
		}
		else enemy_soldiers[i]->setHp(enemy_soldiers[i]->getHp() - dmgtos);
	}
}

void BattleField::update_money(float dt)
{
	money += 1;
}

void BattleField::enemy_soldier_generater(float dt)
{
	time++;
	if (time % 5 != 0)return;
	if (CCRANDOM_0_1() > 0.5)return;

	auto Footman = Sprite::create("Footman_enemy.png");
	Footman->setAnchorPoint(Vec2(0, 0));
	Footman->setPosition(Vec2(860, 30* CCRANDOM_0_1()));
	soldierItem* tmp=soldierItem::getInstance(Footman, 860, FootmanHP, 1);
	//tmp.soldier = Footman;
	//tmp.type = 1;
	//tmp.position = 860;
	enemy_soldiers.push_back(tmp);
	this->addChild(Footman);
}
