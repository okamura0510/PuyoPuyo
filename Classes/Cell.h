/**
 * セル
 * @author m_okamura
 * @date   2015-08-20
 */
#ifndef __CELL_H__
#define __CELL_H__

#include "SceneGame.h"

USING_NS_CC;

class Puyo;

class Cell : public Node
{
public:
	/** X座標 */
	int x = 0;
	/** Y座標 */
	int y = 0;
	/** ぷよ */
	Puyo* puyo = nullptr;
	/** CREATE_FUNC */
	CREATE_FUNC(Cell);
};

#endif // __CELL_H__
