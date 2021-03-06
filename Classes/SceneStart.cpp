/**
 * スタートシーン
 * @author m_okamura
 * @date   2015-08-19
 */
#include "SceneStart.h"
#include "SceneGame.h"

/** 
 * 初期化処理
 * @return true：初期化成功、false：初期化失敗
 */
bool SceneStart::init()
{
	if (!SceneMother::init()) { return false; }

	// 変数初期化
	App* app = App::getInstance();
	app->visibleSize = Director::getInstance()->getVisibleSize();
	app->visibleOrigin = Director::getInstance()->getVisibleOrigin();
	app->centerPos = Vec2(app->visibleSize.width / 2 + app->visibleOrigin.x, app->visibleSize.height / 2 + app->visibleOrigin.y);

	// 次のシーンへ
	this->runAction(CallFunc::create([](){
		Director::getInstance()->replaceScene(SceneGame::createScene());
	}));
    return true;
}
