/**
 * ぷよ
 * @author m_okamura
 * @date   2015-08-20
 */
#ifndef __PUYO_H__
#define __PUYO_H__

#include "SceneGame.h"

USING_NS_CC;

class Cell;

class Puyo : public Node
{
public:
	/** X座標 */
	int x = 0;
	/** Y座標 */
	int y = 0;
	/** ぷよタイプ */
	Game::PuyoType type = Game::PuyoType::GREEN;
	/** スプライト */
	Sprite* sprite = nullptr;
	/** セル */
	Cell* cell = nullptr;
	/** 落下フラグ */
	bool isFall = false;
	/** 落下セル */
	Cell* fallCell = nullptr;
	/** 消去フラグ */
	bool isVanish = false;
	/** 消去ID */
	int vanishId = 0;
	/** セル初期化 */
	void initCell();
	/** セル更新 */
	void updateCell(Cell* cell);
	///** CREATE_FUNC */
	CREATE_FUNC(Puyo);
};

#endif // __PUYO_H__
