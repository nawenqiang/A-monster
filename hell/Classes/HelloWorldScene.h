#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld	 : public cocos2d::CCLayerColor
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();

    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
public:
	~HelloWorld();
    void selfdefinedAc(CCNode* pSender); 
	void menuHandle(CCObject* pSende);
	void HelloWorld::spriteAct();	
	void HelloWorld::time(float val);	
	void HelloWorld::update(float val);	
	void  ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent) ;
	void switchScene(char* str);
private:
	cocos2d::CCArray *m_arrTar;
	cocos2d::CCArray *m_arrPro;
	int m_nSucessedCount;
};

#endif // __HELLOWORLD_SCENE_H__
