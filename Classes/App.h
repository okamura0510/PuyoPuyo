/**
 * アプリ基本情報
 * @author m_okamura
 * @date   2015-08-19
 */
#ifndef __APP_H__
#define __APP_H__

#include "cocos2d.h"
#pragma execution_character_set("utf-8")

USING_NS_CC;

class App
{
//---------------------------------------------------------
// 定数
//---------------------------------------------------------
public:
	/** リリースフラグ */
	static const bool IS_RELEASE;
	/** デバッグフラグ */
	static const bool IS_DEBUG;
	/** ディレクトリ：フォント */
	static const char* DIR_FONT;
	/** ディレクトリ：テクスチャ */
	static const char* DIR_TEXTURE;
	/** ファイル：ステージ */
	static const char* FILE_STAGE;
	/** パス：システムフォント */
	static const char* PATH_SYSTEM_FONT;
	/** パス：ボタン */
	static const char* PATH_BUTTON;
	/** パス：キー */
	static const char* PATH_KEY;
	/** パス：ぷよ */
	static const char* PATH_PUYO;
	/** パス：パタンキュ～ */
	static const char* PATH_BATANKYU;

//---------------------------------------------------------
// 変数
//---------------------------------------------------------
public:
	/** 画面サイズ */
	Size visibleSize;
	/** ベースポジション */
	Vec2 visibleOrigin;
	/** 中央ポジション */
	Vec2 centerPos;

//---------------------------------------------------------
// Util
//---------------------------------------------------------
public:
	/** インスタンス取得 */
	static App* getInstance();
	/** 乱数取得 */
	static int getRandom(int min, int max);

//---------------------------------------------------------
// Private
//---------------------------------------------------------
private:
	App();
	static App* instance;
};

//---------------------------------------------------------
// マクロ
//---------------------------------------------------------
/** 配列長取得 */
#define SIZE_OF_ARRAY(ary) (sizeof(ary)/sizeof((ary)[0]))

#endif // __APP_H__
