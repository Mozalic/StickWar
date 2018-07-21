#include "StartMenu.h"
#include "SimpleAudioEngine.h"
#include "Option.h"

USING_NS_CC;

Scene* StartMenu::createScene()
{
    return StartMenu::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in StartMenuScene.cpp\n");
}

// on "init" you need to initialize your instance
bool StartMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(StartMenu::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width/2 ;
		float y = origin.y + closeItem->getContentSize().height *  2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu1 = Menu::create(closeItem, NULL);
    menu1->setPosition(Vec2::ZERO);
    this->addChild(menu1, 1);

	// add an 'option' icon
	auto optionItem = MenuItemImage::create(
		"OptionNormal.png",
		"OptionSelected.png",
		CC_CALLBACK_1(StartMenu::menuOptionCallback, this));

	if (optionItem == nullptr ||
		optionItem->getContentSize().width <= 0 ||
		optionItem->getContentSize().height <= 0)
	{
		problemLoading("'OptionNormal.png' and 'OptionSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width / 2;
		float y = origin.y + optionItem->getContentSize().height * 7 / 2;
		optionItem->setPosition(Vec2(x, y));
	}

	// create menu, it's an autorelease object
	auto menu2 = Menu::create(optionItem, NULL);
	menu2->setPosition(Vec2::ZERO);
	this->addChild(menu2, 2);

	// add a 'start' icon
	auto startItem = MenuItemImage::create(
		"StartNormal.png",
		"StartSelected.png",
		CC_CALLBACK_1(StartMenu::menuStartCallback, this));

	if (startItem == nullptr ||
		startItem->getContentSize().width <= 0 ||
		startItem->getContentSize().height <= 0)
	{
		problemLoading("'StartNormal.png' and 'StartSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width / 2;
		float y = origin.y + startItem->getContentSize().height *5;
		startItem->setPosition(Vec2(x, y));
	}

	// create menu, it's an autorelease object
	auto menu3 = Menu::create(startItem, NULL);
	menu3->setPosition(Vec2::ZERO);
	this->addChild(menu3, 3);

    /////////////////////////////
    // 3. add your codes below...

    // add "StartMenu" splash screen"
    auto sprite = Sprite::create("background.jpg");
//	sprite->setSkewX(20.0f);
    if (sprite == nullptr)
    {
        problemLoading("'background.jpg'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }
    return true;
}


void StartMenu::menuCloseCallback(Ref* pSender)
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

void StartMenu::menuOptionCallback(Ref* pSender)
{
	auto director = Director::getInstance();
	Size visibleSize = director->getVisibleSize();

	auto optionScene = option::createScene();

	Director::getInstance()->replaceScene(optionScene); 

}

void StartMenu::menuStartCallback(Ref* pSender)
{
	auto director = Director::getInstance();
	Size visibleSize = director->getVisibleSize();

	auto optionScene = option::createScene();

	Director::getInstance()->replaceScene(optionScene);

}