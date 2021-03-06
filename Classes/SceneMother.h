/**
 * シーンの基底クラス。全てのシーンに継承すること。
 * @author m_okamura
 * @date   2015-08-19
 */
#ifndef __SCENE_MOTHER_H__
#define __SCENE_MOTHER_H__

#include "cocos2d.h"

USING_NS_CC;

template <class T> class SceneMother : public Layer
{
public:
	/**
	 * シーン作成
	 * @return cocos2d::Scene
	 */
	static Scene* createScene()
	{
		auto scene = Scene::create();
		auto layer = T::create();
		scene->addChild(layer);
		return scene;
	}

	/**
	 * 初期化処理
	 * @return true：初期化成功、false：初期化失敗
	 */
	virtual bool init() override
	{
		if (!Layer::init()) { return false; }
		return true;
	}

	/** 
	 * 更新処理
	 * @param delta 経過時間
	 */
	virtual void update(float delta) override
	{

	}

	/** CREATE_FUNC */
	CREATE_FUNC(T);
};

#endif // __SCENE_MOTHER_H__
