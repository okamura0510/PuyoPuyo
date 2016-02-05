/**
 * ぷよ
 * @author m_okamura
 * @date   2015-08-20
 */
#include "Puyo.h"

/**
 * セル初期化
 */
void Puyo::initCell()
{
	cell->puyo = nullptr;
	cell = nullptr;
}

/**
 * セル更新
 * @param cell セル
 */
void Puyo::updateCell(Cell* cell)
{
	this->cell = cell;
	this->cell->puyo = this;
}