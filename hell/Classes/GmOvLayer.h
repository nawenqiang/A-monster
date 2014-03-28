#pragma once

#include "cocos2d.h"

class GmOvLayer : public cocos2d::CCLayerColor
{
public:
	GmOvLayer(void);
	virtual ~GmOvLayer(void);
	bool init();
	CREATE_FUNC(GmOvLayer);
	static cocos2d::CCScene* scene();
	void setLableCont(char *str);
	void menuHandle(CCObject* pSender);

private:
	cocos2d::CCLabelTTF *m_lb;
};

