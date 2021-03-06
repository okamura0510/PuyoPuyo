/**
 * ゲーム基本情報
 * @author m_okamura
 * @date   2015-08-20
 */
#include "Game.h"

//---------------------------------------------------------
// 定数
//---------------------------------------------------------
/** ぷよ方向毎の移動量 */
const int Game::MOVE_VALUES[4][2] = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };
/** リトライラベル */
const char* Game::RETRY_LABEL = "Retry!";
/** リトライフォントサイズ */
const int Game::RETRY_FONT_SIZE = 23;
/** キー横幅 */
const int Game::KEY_WIDTH = 170;
/** キー横幅 */
const int Game::KEY_HEIGHT = 140;
/** 連鎖ラベル */
const char* Game::CHAIN_LABEL = "%dれんさ";
/** 連鎖フォントサイズ */
const int Game::CHAIN_FONT_SIZE = 30;
/** ステージ列 */
const int Game::STAGE_COL = 6;
/** ステージ行 */
const int Game::STAGE_ROW = 12;
/** ステージ横幅 */
const int Game::STAGE_WIDTH = 460;
/** ステージ縦幅 */
const int Game::STAGE_HEIGHT = 640;
/** セルサイズ */
const int Game::CELL_SIZE = 45;
/** セル数 */
const int Game::CELL_COUNT = Game::STAGE_COL * Game::STAGE_ROW;
/** ぷよ出現X座標 */
const int Game::PUYO_APPEAR_X = 2;
/** ぷよ出現Y座標 */
const int Game::PUYO_APPEAR_Y = Game::STAGE_ROW - 1;
/** ぷよX方向の移動時間 */
const float Game::PUYO_MOVE_TIME_X = 0.05f;
/** ぷよY方向の移動時間 */
const float Game::PUYO_MOVE_TIME_Y = 1.0f;
/** ぷよX方向の早送り率 */
const float Game::PUYO_MOVE_FAST_X = 4.0f;
/** ぷよX方向の早送り時間 */
const float Game::PUYO_MOVE_FAST_X_TIME = 0.07f;
/** ぷよY方向の早送り率 */
const float Game::PUYO_MOVE_FAST_Y = 40.0f;
/** ぷよ落下時間 */
const float Game::PUYO_FALL_TIME = 0.1f;
/** ぷよ落下バウンド時間 */
const float Game::PUYO_FALL_BOUND_TIME = 0.05f;
/** ぷよが消える数 */
const int Game::PUYO_VANISH_COUNT = 4;
/** ぷよ消去フラッシュ時間 */
const float Game::PUYO_VANISH_FLASH_TIME = 0.1f;
/** ぷよ消去ウェイト時間 */
const float Game::PUYO_VANISH_WAIT_TIME = 0.3f;
/** ぷよ消去フェイド時間 */
const float Game::PUYO_VANISH_FADE_TIME = 0.3f;
/** ぷよ終了ウェイト時間 */
const float Game::PUYO_LAST_WAIT = 0.5f;
/** バタンキュ～ウェイト時間 */
const float Game::BATANKYU_WAIT_TIME = 0.5f;
/** バタンキュ～フェイド時間 */
const float Game::BATANKYU_FADE_TIME = 0.7f;
/** バタンキュ～フェイドウェイト時間 */
const float Game::BATANKYU_FADE_WAIT_TIME = 0.2f;
/** バタンキュ～スケールアップ時間 */
const float Game::BATANKYU_SCALE_UP_TIME = 0.2f;
/** バタンキュ～スケールアップ値 */
const float Game::BATANKYU_SCALE_UP_VALUE = 1.2f;
/** バタンキュ～スケールダウン時間 */
const float Game::BATANKYU_SCALE_DOWN_TIME = 0.15f;
/** バタンキュ～スケールダウン値 */
const float Game::BATANKYU_SCALE_DOWN_VALUE = 0.2f;

//---------------------------------------------------------
// インスタンス
//---------------------------------------------------------
Game* Game::instance = nullptr;
Game::Game(){}
Game* Game::getInstance()
{
	if (instance == nullptr) { instance = new Game(); }
	return instance;
}