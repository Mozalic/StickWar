#include "Success.h"
#include "StartMenu.h"
#include "SimpleAudioEngine.h"
#include "ui/UICheckBox.h"

USING_NS_CC;
using namespace cocos2d::ui;

Scene* success::createScene()
{
	return success::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in successScene.cpp\n");
}

// on "init" you need to initialize your instance
bool success::init()
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
		CC_CALLBACK_1(success::menubackCallback, this));

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

	auto label_option = Label::createWithTTF("You Win!", "fonts/Marker Felt.ttf", 48);
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

	// add "StartMenu" splash screen"
	auto startback = Sprite::create("success.jpg");
	startback->setScale(1.1);
	if (startback == nullptr)
	{
		problemLoading("'success.jpg'");
	}
	else
	{
		// position the sprite on the center of the screen
		startback->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

		// add the sprite as a child to this layer
		this->addChild(startback, -1);
	}

	return true;
}


void success::menubackCallback(Ref* pSender)
{
	auto scene = StartMenu::createScene();
	Director::getInstance()->replaceScene(scene);
}

