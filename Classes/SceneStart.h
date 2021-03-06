/**
 * スタートシーン
 * @author m_okamura
 * @date   2015-08-19
 */
#ifndef __SCENE_START_H__
#define __SCENE_START_H__

#include "cocos2d.h"
#include "SceneMother.h"

USING_NS_CC;

class SceneStart : public SceneMother<SceneStart>
{
public:
	/** 初期化処理 */
    virtual bool init() override;
};

#endif // __SCENE_START_H__
