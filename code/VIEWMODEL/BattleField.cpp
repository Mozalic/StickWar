
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
	this->addChild(backGround);
	
	auto label1 = Label::createWithTTF(std::to_string(money), "fonts/arial.ttf", 24);
	label1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height-label1->getContentSize().height));
	label1->setColor(Color3B(0, 0, 0));
	moneyLabel = label1;
	this->addChild(label1);

	auto FootmanButton = ui::Button::create(
		"footman_btn_normal.png", "footman_btn_selected.png", "footman_btn_selected.png");
	FootmanButton->setPosition(Vec2(
		FootmanButton->getContentSize().width/2,
		visibleSize.height-FootmanButton->getContentSize().height/2));
	//FootmanButton->getContentSize();
	FootmanButton->addTouchEventListener(CC_CALLBACK_2(
		BattleField::FootmanButtonCallback,
		this));

	this->addChild(FootmanButton);

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

void BattleField::FootmanGenrate()
{
	if (money < 10)return;
	money -= 10;
	auto Footman = Sprite::create("Footman.png");
	Footman->setAnchorPoint(Vec2(0, 0));
	Footman->setPosition(Vec2(0, 10* CCRANDOM_0_1()));
	soldierItem tmp;
	tmp.soldier = Footman;
	tmp.type = 1;
	tmp.position = 0;
	soldiers.push_back(tmp);
	this->addChild(Footman);
}

void BattleField::update_soldier_move(float dt) {
	const int step = 10;
	std::cout << leftmost << " " << rightmost << std::endl;
	moneyLabel->setString(std::to_string(money));
	auto moveleft = MoveBy::create(0.1, Vec2(step, 0));
	auto moveright = MoveBy::create(0.1, Vec2(-1*step, 0));
	for (int i = 0; i < soldiers.size(); i++) {
		if (soldiers[i].position+soldiers[i].soldier->getContentSize().width < rightmost) {
			soldiers[i].soldier->runAction(MoveBy::create(0.1, Vec2(step, 0)));
			soldiers[i].position += step;
			if (soldiers[i].position > leftmost) {
				leftmost = soldiers[i].position;
			}
		}
	}
	for (int i = 0; i < enemy_soldiers.size(); i++) {
		//enemy_soldiers[i].soldier->runAction(MoveBy::create(0.1, Vec2(-1 * step, 0)));
		if (enemy_soldiers[i].position > leftmost + enemy_soldiers[i].soldier->getContentSize().width) {
			enemy_soldiers[i].soldier->runAction(MoveBy::create(0.1, Vec2(-1 * step, 0)));
			enemy_soldiers[i].position -= step;
			if (enemy_soldiers[i].position < rightmost) {
				rightmost = enemy_soldiers[i].position;
			}
		}
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
	Footman->setPosition(Vec2(860, 10* CCRANDOM_0_1()));
	soldierItem tmp;
	tmp.soldier = Footman;
	tmp.type = 1;
	tmp.position = 860;
	enemy_soldiers.push_back(tmp);
	this->addChild(Footman);
}
