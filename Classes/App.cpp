/**
 * アプリ基本情報
 * @author m_okamura
 * @date   2015-08-19
 */
#include "App.h"

//---------------------------------------------------------
// 定数
//---------------------------------------------------------
/** リリースフラグ */
const bool App::IS_RELEASE = false;
/** デバッグフラグ */
const bool App::IS_DEBUG = !App::IS_RELEASE;
/** ディレクトリ：フォント */
const char* App::DIR_FONT = "%s";
/** ディレクトリ：テクスチャ */
const char* App::DIR_TEXTURE = "%s";
/** ファイル：ステージ */
const char* App::FILE_STAGE = "stage.png";
/** パス：システムフォント */
const char* App::PATH_SYSTEM_FONT = "font.ttf";
/** パス：ボタン */
const char* App::PATH_BUTTON = "button_%d.png";
/** パス：キー */
const char* App::PATH_KEY = "key_%d.png";
/** パス：ぷよ */
const char* App::PATH_PUYO = "p_%d.png";
/** パス：パタンキュ～ */
const char* App::PATH_BATANKYU = "batankyu.png";

//---------------------------------------------------------
// Util
//---------------------------------------------------------
/** 
 * 乱数取得
 * @param  min 最小値
 * @param  max 最大値
 * @return 乱数
 */
int App::getRandom(int min, int max)
{
	return RandomHelper::random_int(min, max - 1);
}

//---------------------------------------------------------
// インスタンス
//---------------------------------------------------------
App* App::instance = nullptr;
App::App(){}
App* App::getInstance()
{
	if (instance == nullptr) { instance = new App(); }
	return instance;
}