#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "GmOvLayer.h"
USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}
 //   CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
 //   CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

 //   /////////////////////////////
 //   // 2. add a menu item with "X" image, which is clicked to quit the program
 //   //    you may modify it.

 //   // add a "close" icon to exit the progress. it's an autorelease object
 //   CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
 //                                       "CloseNormal.png",
 //                                       "CloseSelected.png",
 //                                       this,
 //                                       menu_selector(HelloWorld::menuCloseCallback));

	//pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
 //                                origin.y + pCloseItem->getContentSize().height/2));
 //   // create menu, it's an autorelease object
 //   CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
 //   pMenu->setPosition(CCPointZero);
 //   this->addChild(pMenu, 1);

 //   /////////////////////////////
 //   // 3. add your codes below...

 //   // add a label shows "Hello World"
 //   // create and initialize a label
 //   
 //   CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
 //   
 //   // position the label on the center of the screen
 //   pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
 //                           origin.y + visibleSize.height - pLabel->getContentSize().height));

 //   // add the label as a child to this layer
 //   this->addChild(pLabel, 1);

 //   // add "HelloWorld" splash screen"
 //   CCSprite* pSprite = CCSprite::create("HelloWorld.png");

 //   // position the sprite on the center of the screen
 //   pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

 //   // add the sprite as a child to this layer
 //   this->addChild(pSprite, 0);
// on "init" you need to initialize your instance

	//CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
 //                                       "button2.png",
 //                                       "button2.png",
 //                                       this,
 //                                       menu_selector(HelloWorld::menuHandle));
	//pCloseItem->setPosition(50.0,50.0);
 //   CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
 //   this->addChild(pMenu, 1);	

HelloWorld::~HelloWorld()
{
	delete m_arrTar;
	delete m_arrPro;
}

bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayerColor::initWithColor(ccc4(255,255,255,255)))
    {
        return false;
    } 
	m_arrTar = new CCArray;
	m_arrPro = new CCArray;
	m_nSucessedCount = 0;

	CCSize screenSize = CCDirector::sharedDirector()->getVisibleSize();

	CCSprite *pSprite = CCSprite::create("Player.png");
	pSprite->setPosition(ccp(20.0,screenSize.height/2));
	this->addChild(pSprite);   

	this->schedule(schedule_selector(HelloWorld::time),2);
	this->schedule(schedule_selector(HelloWorld::update));
	this->setTouchEnabled(true);

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background-music-aac.wav",true);      

    return true;
}

void HelloWorld::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent) 
{
	CCTouch *touch = (CCTouch *)pTouches->anyObject();
	CCPoint locInVw = touch->getLocationInView();
	CCPoint locInGl = CCDirector::sharedDirector()->convertToGL(locInVw);

	CCSize screenSize = CCDirector::sharedDirector()->getVisibleSize();
	CCSprite *proj = CCSprite::create("Projectile.png");
	proj->setPosition(ccp(20.0,screenSize.height/2.0));
	this->addChild(proj);
	m_arrPro->addObject(proj);
	proj->setTag(2);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("pew-pew-lei.wav");      

	double dx = locInGl.x - 20;
	double dy = locInGl.y - screenSize.height/2.0;
	double d = sqrt(dx*dx + dy*dy);

	double D = sqrt(screenSize.width * screenSize.width + screenSize.height * screenSize.height);
	double ratio = D/d;
	double endx = ratio * dx + 20;
	double endy = ratio *dy + screenSize.height/2.0;

	CCMoveTo *move = CCMoveTo::create(D/320,ccp(endx,endy));
	CCCallFuncN *sd = CCCallFuncN::create(this,callfuncN_selector(HelloWorld::selfdefinedAc));
	CCSequence *actions = CCSequence::create(move,sd,NULL);
	proj->runAction(actions);
}	

void HelloWorld::switchScene(char* str)
{	
	CCScene *scene = GmOvLayer::scene();
	GmOvLayer *goLayer = (GmOvLayer *)scene->getChildByTag(100);
	goLayer->setLableCont(str);
	CCDirector::sharedDirector()->replaceScene(scene);
	m_nSucessedCount = 0;
}

void HelloWorld::update(float val)
{
	CCObject *tar,*pro;
	if(5 == m_nSucessedCount)
	{
		switchScene("success");
	}
	CCARRAY_FOREACH(m_arrTar,tar)
	{
		CCSprite *pTar = (CCSprite *)tar;
		CCRect rtTar = CCRectMake(pTar->getPosition().x,pTar->getPosition().y,pTar->getContentSize().width
			,pTar->getContentSize().height);

		CCARRAY_FOREACH(m_arrPro,pro)
		{
			CCSprite *pPro = (CCSprite *)pro;
			CCRect rtPro = CCRectMake(pPro->getPosition().x,pPro->getPosition().y,pPro->getContentSize().width
				,pPro->getContentSize().height);
			if(rtPro.intersectsRect(rtTar))
			{
				m_arrTar->removeObject(pTar);
				m_arrPro->removeObject(pPro);		
				pTar->removeFromParentAndCleanup(true);
				pPro->removeFromParentAndCleanup(true);
				m_nSucessedCount ++;
				break;
			}
		}
	}
}

void HelloWorld::time(float val)
{
	spriteAct();
}

void HelloWorld::spriteAct()
{
	CCSize screenSize = CCDirector::sharedDirector()->getVisibleSize();

	CCSprite *pSprite = CCSprite::create("Target.png");
	int y = rand()%(int)screenSize.height;
	pSprite->setPosition(ccp(screenSize.width-20,y));
	this->addChild(pSprite);   
	m_arrTar->addObject(pSprite);
	pSprite->setTag(1);

	CCMoveTo *move = CCMoveTo::create(3.0,ccp(0,y));
	CCCallFuncN *pSelfdefinedAc = CCCallFuncN::create(this,callfuncN_selector(HelloWorld::selfdefinedAc));
	CCSequence *actions = CCSequence::create(move,pSelfdefinedAc,NULL);
	pSprite->runAction(actions);
}

void HelloWorld::menuHandle(CCObject* pSende)
{
	//CCSize screenSize = CCDirector::sharedDirector()->getVisibleSize();
	//CCMoveTo *move = CCMoveTo::create(2.0,ccp(0,screenSize.height/2));


	//CCCallFuncN *pSelfdefinedAc = CCCallFuncN::create(this,callfuncN_selector(HelloWorld::selfdefinedAc));
	//CCSequence *actions = CCSequence::create(move,pSelfdefinedAc,NULL);
	//m_pSprite->runAction(actions);
}

void HelloWorld::selfdefinedAc(CCNode* pSender)
{
	pSender->removeFromParentAndCleanup(true);
	int tag = pSender->getTag();
	if(1 == tag)
	{
		m_arrTar->removeObject(pSender);
		switchScene("failed");
	}
	else if(2 == tag)
	{
		m_arrPro->removeObject(pSender);
	}
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
