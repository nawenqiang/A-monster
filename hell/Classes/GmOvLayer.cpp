#include "GmOvLayer.h"
#include "HelloWorldScene.h"

USING_NS_CC;

GmOvLayer::GmOvLayer(void)
{
}


GmOvLayer::~GmOvLayer(void)
{
	if(m_lb)
	{
		m_lb->release();
	}
}

CCScene* GmOvLayer::scene()
{
	CCScene *scene = CCScene::create();
	GmOvLayer *layer = GmOvLayer::create();
	layer->setTag(100);
	scene->addChild(layer);

	return scene;
}

bool GmOvLayer::init()
{
	if(!CCLayerColor::initWithColor(ccc4(255,0,0,255)))
	{
		return false;
	}

	CCSize size = CCDirector::sharedDirector()->getVisibleSize();

	CCMenuItemImage *pBackItem = CCMenuItemImage::create(
                                        "button2.png",
                                        "button2.png",
                                        this,
                                        menu_selector(GmOvLayer::menuHandle));
	pBackItem->setPosition(pBackItem->getContentSize().width/2,pBackItem->getContentSize().height/2);
    CCMenu* pMenu = CCMenu::create(pBackItem, NULL);
	pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);	
		
	m_lb = CCLabelTTF::create("word","artial",40);
	m_lb->setPosition(ccp(size.width/2,size.height/2));
	this->addChild(m_lb);
	m_lb->retain();//保证m_lb跟类对象有相同生命周期

	return true;
}

void GmOvLayer::menuHandle(CCObject* pSender)
{
	CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
}

void GmOvLayer::setLableCont(char *str)
{
	m_lb->setString(str);
}
