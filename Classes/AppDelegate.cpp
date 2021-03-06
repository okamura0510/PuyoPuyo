/**
* アプリのメインエントリポイント
* @author m_okamura
* @date   2015-08-19
*/
#include "AppDelegate.h"
#include "App.h"
#include "SceneStart.h"

/** 
 * アプリ起動
 * @return true：起動成功、false：起動失敗
 */
bool AppDelegate::applicationDidFinishLaunching() 
{
	// Director初期化
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) 
	{
        glview = GLViewImpl::create("PuyoPuyo");
        director->setOpenGLView(glview);
    }

	// シーン初期化
    director->setDisplayStats(false);
    director->setAnimationInterval(1.0 / 60);

	// シーン遷移
	director->runWithScene(SceneStart::createScene());
    return true;
}

/**
 * アプリ停止
 */
void AppDelegate::applicationDidEnterBackground()
{
	Director::getInstance()->stopAnimation();
}

/** 
 * アプリ復帰
 */
void AppDelegate::applicationWillEnterForeground()
{
	Director::getInstance()->startAnimation();
}
