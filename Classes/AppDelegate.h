/**
* アプリのメインエントリポイント
* @author m_okamura
* @date   2015-08-19
*/
#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"

USING_NS_CC;

class  AppDelegate : private Application
{
public:
	/** アプリ起動 */
    virtual bool applicationDidFinishLaunching();
	/** アプリ停止 */
	virtual void applicationDidEnterBackground();
	/** アプリ復帰 */
	virtual void applicationWillEnterForeground();
};

#endif // _APP_DELEGATE_H_

