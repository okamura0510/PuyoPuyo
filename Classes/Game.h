/**
 * ゲーム基本情報
 * @author m_okamura
 * @date   2015-08-20
 */
#ifndef __GAME_H__
#define __GAME_H__

#include "cocos2d.h"
#include "App.h"

USING_NS_CC;

class Game
{
//---------------------------------------------------------
// 定数
//---------------------------------------------------------
public:
	/** 向き */
	static const enum Dir : int { UP, RIGHT, DOWN, LEFT };
	/** 移動量 */
	static const int MOVE_VALUES[4][2];
	/** リトライラベル */
	static const char* RETRY_LABEL;
	/** キー横幅 */
	static const int KEY_WIDTH;
    /** キー横幅 */
    static const int KEY_HEIGHT;
	/** リトライフォントサイズ */
	static const int RETRY_FONT_SIZE;
	/** 連鎖ラベル */
	static const char* CHAIN_LABEL;
	/** 連鎖フォントサイズ */
	static const int CHAIN_FONT_SIZE;
	/** ステージ列 */
	static const int STAGE_COL;
	/** ステージ行 */
	static const int STAGE_ROW;
	/** ステージ横幅 */
	static const int STAGE_WIDTH;
	/** ステージ縦幅 */
	static const int STAGE_HEIGHT;
	/** セルサイズ */
	static const int CELL_SIZE;
	/** セル数 */
	static const int CELL_COUNT;
	/** ぷよタイプ */
	static const enum PuyoType : int { GREEN, RED, YELLOW, PURPLE, COUNT };
	/** ぷよ出現X座標 */
	static const int PUYO_APPEAR_X;
	/** ぷよ出現Y座標 */
	static const int PUYO_APPEAR_Y;
	/** ぷよX方向の移動時間 */
	static const float PUYO_MOVE_TIME_X;
	/** ぷよY方向の移動時間 */
	static const float PUYO_MOVE_TIME_Y;
	/** ぷよX方向の早送り率 */
	static const float PUYO_MOVE_FAST_X;
	/** ぷよX方向の早送り時間 */
	static const float PUYO_MOVE_FAST_X_TIME;
	/** ぷよY方向の早送り率 */
	static const float PUYO_MOVE_FAST_Y;
	/** ぷよ落下時間 */
	static const float PUYO_FALL_TIME;
	/** ぷよ落下バウンド時間 */
	static const float PUYO_FALL_BOUND_TIME;
	/** ぷよが消える数 */
	static const int PUYO_VANISH_COUNT;
	/** ぷよ消去フラッシュ時間 */
	static const float PUYO_VANISH_FLASH_TIME;
	/** ぷよ消去ウェイト時間 */
	static const float PUYO_VANISH_WAIT_TIME;
	/** ぷよ消去フェイド時間 */
	static const float PUYO_VANISH_FADE_TIME;
	/** ぷよ終了ウェイト時間 */
	static const float PUYO_LAST_WAIT;
	/** バタンキュ～ウェイト時間 */
	static const float BATANKYU_WAIT_TIME;
	/** バタンキュ～フェイド時間 */
	static const float BATANKYU_FADE_TIME;
	/** バタンキュ～フェイドウェイト時間 */
	static const float BATANKYU_FADE_WAIT_TIME;
	/** バタンキュ～スケールアップ時間 */
	static const float BATANKYU_SCALE_UP_TIME;
	/** バタンキュ～スケールアップ値 */
	static const float BATANKYU_SCALE_UP_VALUE;
	/** バタンキュ～スケールダウン時間 */
	static const float BATANKYU_SCALE_DOWN_TIME;
	/** バタンキュ～スケールダウン値 */
	static const float BATANKYU_SCALE_DOWN_VALUE;

//---------------------------------------------------------
// 変数
//---------------------------------------------------------
public:
	/** ステージベースポジション */
	Vec2 stageBasePos;
	/** リトライボタンベースポジション */
	Vec2 retryBasePos;
	/** 十字キーベースポジション */
	Vec2 crossKeyBasePos;
	/** 選択キーベースポジション */
	Vec2 selectKeyBasePos;
	/** ぷよぷよベースポジション */
	Vec2 puyopuyoBasePos;
	/** バタンキュ～ベースポジション */
	Vec2 batankyuBasePos;
	
//---------------------------------------------------------
// メソッド
//---------------------------------------------------------
public:
	/** インスタンス取得 */
	static Game* getInstance();

//---------------------------------------------------------
// Private
//---------------------------------------------------------
private:
	Game();
	static Game* instance;
};

#endif // __GAME_H__
