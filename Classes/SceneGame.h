/**
 * ゲームシーン
 * @author m_okamura
 * @date   2015-08-19
 */
#ifndef __SCENE_GAME_H__
#define __SCENE_GAME_H__

#include "cocos2d.h"
#include "SceneMother.h"
#include "Game.h"
#include "Puyo.h"
#include "Cell.h"

USING_NS_CC;

class SceneGame : public SceneMother<SceneGame>
{
public:
	/** シーケンス */
	static const enum Sq : int 
	{
		// 何もしない
		NONE,
		// ユーザ入力
		USER_INPUT, 
		// ぷよ落下/実行
		FALL_EXEC, 
		// ぷよ落下/バウンド
		FALL_BOUND,
		// ぷよ消去/フラッシュアウト
		VANISH_FLASH_OUT, 
		// ぷよ消去/フラッシュイン
		VANISH_FLASH_IN,
		// ぷよ消去/フラッシュアウト2
		VANISH_FLASH_OUT2,
		// ぷよ消去/ウェイト
		VANISH_WAIT,
		// ぷよ消去/フェイド
		VANISH_FADE,
		// 最終ウェイト
		LAST_WAIT,
		// バタンキュ～/ウェイト
		BATANKYU_WAIT,
		// バタンキュ～/フェイド
		BATANKYU_FADE,
		// バタンキュ～/フェイドウェイト
		BATANKYU_FADE_WAIT,
		// バタンキュ～/スケールアップ
		BATANKYU_SCALE_UP,
		// バタンキュ～/スケールダウン
		BATANKYU_SCALE_DOWN,
	};
	/** 初期化処理 */
	virtual bool init() override;
	/** 更新処理 */
	virtual void update(float delta) override;

private:
	/** アプリ基本情報 */
	App* app = nullptr;
	/** ゲーム基本情報 */
	Game* game = nullptr;
	/** 押下キー */
	EventKeyboard::KeyCode key = EventKeyboard::KeyCode::KEY_NONE;
	/** 前回の押下キー */
	EventKeyboard::KeyCode keyPreb = EventKeyboard::KeyCode::KEY_NONE;
	/** クリックキー */
	EventKeyboard::KeyCode keyDown = EventKeyboard::KeyCode::KEY_NONE;
	/** タッチスプライト */
	Sprite* touchSprite = nullptr;
	/** キースプライトリスト */
	Sprite* keySprites[6];
	/** 連鎖ラベル */
	Label* chainLabel = nullptr;
	/** ステージスプライト */
	Sprite* stageSprite = nullptr;
	/** バタンキュ～スプライト */
	Sprite* batankyuSprite = nullptr;
	/** シーケンス */
	Sq sq = Sq::NONE;
	/** 判定時間 */
	float time = 0.0f;
	/** セルリスト */
	Cell* cells[6][12];
	/** ぷよリスト */
	std::list<Puyo*> puyos;
	/** ぷよぷよ */
	Puyo* puyopuyo[2];
	/** 次のぷよぷよ */
	Puyo* nextPuyopuyo[2];
	/** 向き */
	Game::Dir dir = Game::Dir::UP;
	/** X方向の移動時間 */
	float moveTimeX = 0.0f;
	/** Y方向の移動時間 */
	float moveTimeY = 0.0f;
	/** 右方向移動フラグ */
	bool isMoveR = false;
	/** 左方向移動フラグ */
	bool isMoveL = false;
	/** X方向の早送り実行フラグ */
	bool isMoveFastX = false;
	/** X方向の早送り判定時間 */
	float moveFastXTime = 0.0f;
	/** 連鎖数 */
	int chainCount = 0;
	/** 落下バウンド数 */
	int boundCount = 0;
	/** 消去判定カウンター */
	std::map<int, int> vanishCounter;
	/** 消去IDリスト */
	std::list<int> vanishIds;
	/** ぷよ作成 */
	Puyo* createPuyo(int x, int y, Game::PuyoType type);
	/** ぷよ削除 */
	void removePuyo(Puyo* puyo);
	/** ぷよぷよ作成 */
	void createPuyopuyo();
	/** ぷよぷよセル更新 */
	void updatePuyopuyoCell();
	/** 衝突判定 */
	bool isCollide(Puyo* puyo, Game::Dir dir);
	/** 衝突判定 */
	bool isCollide(int x, int y);
	/** 落下判定 */
	bool isFall();
	/** 消去判定 */
	bool isVanish();
	/** 消去チェック */
	void checkVanish(Puyo* puyo, int id);
	/** ぷよ繋がり判定 */
	bool isConnect(Puyo* puyo, int x, int y);
};

#endif // __SCENE_GAME_H__
