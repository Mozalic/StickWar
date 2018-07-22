#include "Option.h"
#include "StartMenu.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "ui/UICheckBox.h"

USING_NS_CC;
using namespace cocos2d::ui;

extern int DIFFICULTY;

Scene* option::createScene()
{
	return option::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in optionScene.cpp\n");
}

// on "init" you need to initialize your instance
bool option::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto backItem = MenuItemImage::create(
		"BackNormal.png",
		"BackSelected.png",
		CC_CALLBACK_1(option::menubackCallback, this));

	if (backItem == nullptr ||
		backItem->getContentSize().width <= 0 ||
		backItem->getContentSize().height <= 0)
	{
		problemLoading("'BackNormal.png' and 'BackSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width / 2;
		float y = origin.y + backItem->getContentSize().height * 2;
		backItem->setPosition(Vec2(x, y));
	}

	// create menu, it's an autorelease object
	auto menu1 = Menu::create(backItem, NULL);
	menu1->setPosition(Vec2::ZERO);
	this->addChild(menu1, 1);

	/////////////////////////////
	// 3. add your codes below...



	// add a label shows "Option"
	// create and initialize a label

	auto label_option = Label::createWithTTF("Option", "fonts/Marker Felt.ttf", 48);
	if (label_option == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		// position the label on the center of the screen
		label_option->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - label_option->getContentSize().height));

		// add the label as a child to this layer
		this->addChild(label_option, 1);
	}

	// add a label shows "Difficulty"
	// create and initialize a label

	auto label_difficulty = Label::createWithTTF("Difficulty", "fonts/Marker Felt.ttf", 48);
	if (label_difficulty == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		// position the label on the center of the screen
		label_difficulty->setPosition(Vec2(480 - label_difficulty->getContentSize().width / 2 - 30,
			275));

		// add the label as a child to this layer
		this->addChild(label_difficulty, 2);
	}

	// add a checkbox to choose difficulty

	auto check1 = ui::RadioButton::create("check_box_normal.png",
		"check_box_active.png"
		);
	checkbox1 = check1;
	checkbox1->setPosition(Vec2(480, 300));


	this->addChild(checkbox1);

	// add a label shows "Normal"
	// create and initialize a label

	auto label_normal = Label::createWithTTF("Normal", "fonts/Marker Felt.ttf", 24);
	if (label_normal == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		// position the label on the center of the screen
		label_normal->setPosition(Vec2(520 + label_normal->getContentSize().width / 2 ,
			300));

		// add the label as a child to this layer
		this->addChild(label_normal, 2);
	}

	// add another checkbox to choose difficulty

	auto check2 = ui::RadioButton::create("check_box_normal.png",
		"check_box_active.png"
		);
	checkbox2 = check2;
	checkbox2->setPosition(Vec2(480, 250));

	this->addChild(checkbox2);
	//checkbox callback functions

	// add a label shows "Hard"
	// create and initialize a label
	if (DIFFICULTY == 1)
		checkbox1->setSelected(true);
	else
		checkbox2->setSelected(true);

	auto label_hard = Label::createWithTTF("Hard", "fonts/Marker Felt.ttf", 24);
	if (label_hard == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		// position the label on the center of the screen
		label_hard->setPosition(Vec2(520 + label_hard->getContentSize().width / 2,
			250));

		// add the label as a child to this layer
		this->addChild(label_hard, 2);
	}

	checkbox1->addEventListener(CC_CALLBACK_2(option::buttonchange1, this));
	checkbox2->addEventListener(CC_CALLBACK_2(option::buttonchange2, this));

	// add "StartMenu" splash screen"
	auto optionback = Sprite::create("scene1.png");
	optionback->setScale(1.1);
	//	sprite->setSkewX(20.0f);
	if (optionback == nullptr)
	{
		problemLoading("'scene1.png'");
	}
	else
	{
		// position the sprite on the center of the screen
		optionback->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

		// add the sprite as a child to this layer
		this->addChild(optionback, -1);
	}

	return true;
}


void option::menubackCallback(Ref* pSender)
{
	auto scene = StartMenu::createScene();
	Director::getInstance()->replaceScene(scene);
}

void option::buttonchange1(RadioButton* radioButton, RadioButton::EventType type)
{
	if (radioButton == nullptr) {
		return;
	}
	DIFFICULTY = 1;
	checkbox2->setSelected(false);
}

void option::buttonchange2(RadioButton* radioButton, RadioButton::EventType type)
{
	if (radioButton == nullptr) {
		return;
	}
	DIFFICULTY = 2;
	checkbox1->setSelected(false);
}
