#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    //this->addChild(menu, 1);
	
	auto player  = CCSprite::create();
	player->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(player);
	// ��������
	int numOfFrame = 12;
	auto playerTextrue = CCTextureCache::sharedTextureCache()->addImage("player.png");
	float w = playerTextrue->getContentSize().width;
	float h = playerTextrue->getContentSize().height / numOfFrame;

	// ���ɶ���CCSpriteFrame����
	auto playerSprites = CCArray::create();
	for(int i = 0; i < numOfFrame; i++)
	{
		playerSprites->insertObject(CCSpriteFrame::createWithTexture(playerTextrue, CCRectMake(0, h * i, w, h)), 
									i );
	}

	// ����animate
	auto animation = CCAnimation::create();
	animation->setDelayPerUnit(1);
	for(int i = 0; i < numOfFrame; i++)
	{
		animation->addSpriteFrame(static_cast<CCSpriteFrame*>(playerSprites->getObjectAtIndex(i)));
	}
	auto animate = CCAnimate::create(animation);
	player->runAction(CCRepeatForever::create(animate));
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
