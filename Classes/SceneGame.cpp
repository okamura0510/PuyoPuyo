/**
 * ゲームシーン
 * @author m_okamura
 * @date   2015-08-19
 */
#include "SceneGame.h"

/** 
 * 初期化処理
 * @return true：初期化成功、false：初期化失敗
 */
bool SceneGame::init()
{
	if (!SceneMother::init()) { return false; }
	
	this->scheduleUpdate();

	// 変数初期化
	app = App::getInstance();
	game = Game::getInstance();
	game->stageBasePos = Vec2(app->centerPos.x - 157, app->centerPos.y - 245);
	game->retryBasePos = Vec2(app->centerPos.x - 450, app->centerPos.y + 285);
	game->crossKeyBasePos = Vec2(app->centerPos.x - 400, app->centerPos.y - 120);
	game->selectKeyBasePos = Vec2(app->centerPos.x + 315, app->centerPos.y - 120);
	game->puyopuyoBasePos = Vec2(app->centerPos.x + 115, app->centerPos.y + 207);
	game->batankyuBasePos = Vec2(app->centerPos.x, app->centerPos.y + 50);

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	// キー入力
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto keyboard = EventListenerKeyboard::create();
	keyboard->onKeyPressed = [&](EventKeyboard::KeyCode key, Event* event) {
		this->keyPreb = this->key;
		this->key = key;
		if (key != EventKeyboard::KeyCode::KEY_NONE && key != this->keyPreb)
		{
			this->keyDown = key;
		}
	};
	keyboard->onKeyReleased = [&](EventKeyboard::KeyCode key, Event* event) {
		this->keyPreb = EventKeyboard::KeyCode::KEY_NONE;
		this->key = EventKeyboard::KeyCode::KEY_NONE;
		this->keyDown = EventKeyboard::KeyCode::KEY_NONE;
	};
	dispatcher->addEventListenerWithSceneGraphPriority(keyboard, this);
#else
	// タッチ入力
	auto touch = EventListenerTouchOneByOne::create();
	touch->setSwallowTouches(true);
	touch->onTouchBegan = [=](Touch* touch, Event* event){
		for (int i = 0; i < SIZE_OF_ARRAY(keySprites); i++)
		{
			Rect box = keySprites[i]->getBoundingBox();
			Vec2 pos = CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
			if (box.containsPoint(pos))
			{
				this->keyPreb = this->key;
				if (i == 0) { this->key = EventKeyboard::KeyCode::KEY_UP_ARROW; }
				else if (i == 1) { this->key = EventKeyboard::KeyCode::KEY_RIGHT_ARROW; }
				else if (i == 2) { this->key = EventKeyboard::KeyCode::KEY_DOWN_ARROW; }
				else if (i == 3) { this->key = EventKeyboard::KeyCode::KEY_LEFT_ARROW; }
				else if (i == 4) { this->key = EventKeyboard::KeyCode::KEY_Z; }
				else if (i == 5) { this->key = EventKeyboard::KeyCode::KEY_X; }
				if (key != EventKeyboard::KeyCode::KEY_NONE && key != this->keyPreb)
				{
					this->keyDown = key;
				}
				touchSprite = keySprites[i];
				touchSprite->setColor(Color3B::RED);
				return true;
			}
		}
		return true;
	};
	touch->onTouchEnded = [=](Touch* touch, Event* event){
		this->keyPreb = EventKeyboard::KeyCode::KEY_NONE;
		this->key = EventKeyboard::KeyCode::KEY_NONE;
		this->keyDown = EventKeyboard::KeyCode::KEY_NONE;
		if (touchSprite != nullptr) { touchSprite->setColor(Color3B::WHITE); }
		touchSprite = nullptr;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touch, this);
#endif

	// リトライボタン
	auto sprite0 = Sprite::create(StringUtils::format(App::PATH_BUTTON, 0));
	auto sprite1 = Sprite::create(StringUtils::format(App::PATH_BUTTON, 1));
	auto item = MenuItemSprite::create(sprite0, sprite1, [](Ref* sender){
		Director::getInstance()->replaceScene(SceneGame::createScene());
	});
	auto menu = Menu::create(item, NULL);
	menu->setPosition(game->retryBasePos);
	auto label = Label::createWithTTF(Game::RETRY_LABEL, App::PATH_SYSTEM_FONT, Game::RETRY_FONT_SIZE);
	label->setPosition(game->retryBasePos);
	label->setColor(Color3B::BLUE);
	this->addChild(menu, 1);
	this->addChild(label, 1);

	// 十字キー
	for (int i = 0; i < 4; i++)
	{
        keySprites[i] = Sprite::create(StringUtils::format(App::PATH_KEY, i));
        float x = game->crossKeyBasePos.x;
        float y = game->crossKeyBasePos.y;
        if(i == 1 || i == 3) { x += Game::MOVE_VALUES[i][0] * Game::KEY_WIDTH / 2; }
        else { y += Game::MOVE_VALUES[i][1] * Game::KEY_HEIGHT; }
		keySprites[i]->setPosition(Vec2(x, y));
        this->addChild(keySprites[i], 1);
	}

	// 選択キー
	for (int i = 0; i < 2; i++)
	{
		int idx = 4 + i;
		keySprites[idx] = Sprite::create(StringUtils::format(App::PATH_KEY, ((i == 0) ? 3 : 1)));
		keySprites[idx]->setPosition(Vec2(game->selectKeyBasePos.x + i * Game::KEY_WIDTH, game->selectKeyBasePos.y));
		this->addChild(keySprites[idx], 1);
	}

	// 連鎖数
	chainLabel = Label::createWithTTF(StringUtils::format(Game::CHAIN_LABEL, 0), App::PATH_SYSTEM_FONT, Game::CHAIN_FONT_SIZE);
	chainLabel->setPosition(app->centerPos);
	chainLabel->setColor(Color3B::YELLOW);
	chainLabel->enableOutline(Color4B(178, 85, 93, 255), 2);
	chainLabel->setVisible(false);
	this->addChild(chainLabel, 2);

	// ステージ
	stageSprite = Sprite::create(StringUtils::format(App::DIR_TEXTURE, App::FILE_STAGE));
	stageSprite->setPosition(app->centerPos);
	this->addChild(stageSprite, 0);

	// セル
	for (int x = 0; x < SIZE_OF_ARRAY(cells); x++)
	{
		for (int y = 0; y < SIZE_OF_ARRAY(cells[0]); y++)
		{
			auto cell = (Cell*)Cell::create();
			cell->x = x;
			cell->y = y;
			cell->setPosition(Vec2(game->stageBasePos.x + x * Game::CELL_SIZE, game->stageBasePos.y + y * Game::CELL_SIZE));
			this->addChild(cell, 0);
			cells[x][y] = cell;
		}
	}

	// ぷよぷよ
	for (int i = 0; i < 2; i++)
	{
		nextPuyopuyo[i] = createPuyo(Game::PUYO_APPEAR_X, Game::PUYO_APPEAR_Y - i, (Game::PuyoType)App::getRandom(0, Game::PuyoType::COUNT));
	}
	createPuyopuyo();

	// ユーザ入力へ
	sq = Sq::USER_INPUT;
    return true;
}

/** 
 * 更新処理
 * @param delta 経過時間
 */
void SceneGame::update(float delta)
{
	if (sq == Sq::USER_INPUT)
	{
		// ユーザ入力
		bool isUpdate = false;
		float value = 0.0f;

		// ぷよぷよ回転
		if (keyDown == EventKeyboard::KeyCode::KEY_Z || keyDown == EventKeyboard::KeyCode::KEY_X || keyDown == EventKeyboard::KeyCode::KEY_UP_ARROW)
		{
			int sign = (keyDown == EventKeyboard::KeyCode::KEY_Z) ? -1 : 1;
			int dirValue = dir + sign;
			if (dirValue < 0) { dirValue = 3; }
			else if (dirValue > 3) { dirValue = 0; }
			auto dirNow = (Game::Dir)dirValue;

			// 次のセルへ移動可能か？
			bool isMove = true;
			auto base = puyopuyo[1];
			int mx = 0;
			int my = 0;
			for (int i = 0; i < 2; i++)
			{
				for (auto puyo : puyopuyo)
				{
					bool isBase = (puyo == base);
					int dx = ((isBase) ? 0 : Game::MOVE_VALUES[dirValue][0]) + mx;
					int dy = ((isBase) ? 0 : Game::MOVE_VALUES[dirValue][1]) + my;
					int x = base->cell->x + dx;
					int y = base->cell->y + dy;
					int x2 = x;
					int y2 = y - 1;
					if (i == 0)
					{
						// 移動判定
						if (isCollide(x, y) || isCollide(x2, y2))
						{
							isMove = false;
							if ((i == 0 && !isBase) && (dirNow == Game::Dir::RIGHT || dirNow == Game::Dir::LEFT || dirNow == Game::Dir::DOWN))
							{
								// はみ出しを考慮
								if (dirNow == Game::Dir::RIGHT) { mx = -1; }
								else if (dirNow == Game::Dir::LEFT) { mx = 1; }
								else if (dirNow == Game::Dir::DOWN) { my = -1; }

								// ずらしたら移動可能か？
								x += mx;
								y += my;
								x2 += mx;
								y2 += my;
								if (!(isCollide(x, y) || isCollide(x2, y2)))
								{
									isMove = true; 
								}
							}
							if (!isMove) { break; }
						}
					}
					else
					{
						// 移動設定
						float px = base->sprite->getPositionX() + dx * Game::CELL_SIZE;
						float py = base->sprite->getPositionY() + dy * Game::CELL_SIZE;
						puyo->x = x;
						puyo->y = y;
						puyo->sprite->setPosition(Vec2(px, py));
					}
				}
				if (!isMove) { break; }
			}
			if (isMove)
			{
				// セル更新
				dir = dirNow;
				updatePuyopuyoCell();
			}
		}

		// ぷよぷよ左右移動
		if (key == EventKeyboard::KeyCode::KEY_RIGHT_ARROW || key == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			// 早送り率上昇
			moveFastXTime += delta;
			if (moveFastXTime > Game::PUYO_MOVE_FAST_X_TIME) { isMoveFastX = true; }
		}
		else
		{
			// 早送り停止
			isMoveFastX = false;
			moveFastXTime = 0.0f;
		}
		auto keyRL = (isMoveFastX) ? key : keyDown;
		bool isKeyDownR = (keyRL == EventKeyboard::KeyCode::KEY_RIGHT_ARROW);
		bool isKeyDownL = (keyRL == EventKeyboard::KeyCode::KEY_LEFT_ARROW);
		if (isMoveR || isMoveL)
		{
			// 移動中
			moveTimeX += delta * ((isMoveFastX) ? Game::PUYO_MOVE_FAST_X : 1.0f);
			isUpdate = (moveTimeX > Game::PUYO_MOVE_TIME_X);
			value = (isUpdate) ? 1.0f : (moveTimeX / Game::PUYO_MOVE_TIME_X);
			int sign = (isMoveR) ? 1 : -1;
			for (auto puyo : puyopuyo)
			{
				puyo->sprite->setPositionX(puyo->cell->getPositionX() + sign * value * Game::CELL_SIZE);
				if (isUpdate) { puyo->x += sign; }
			}
			if (isUpdate)
			{
				// セル更新
				isMoveR = false;
				isMoveL = false;
				moveTimeX = 0.0f;
				updatePuyopuyoCell();
			}
		}
		if (!isMoveR && !isMoveL)
		{
			// 移動してない
			if (isKeyDownR || isKeyDownL)
			{
				// 次のセルへ移動可能か？
				bool isMove = true;
				int sign = (isKeyDownR) ? 1 : -1;
				for (auto puyo : puyopuyo)
				{
					int x = puyo->cell->x + sign;
					int y = puyo->cell->y;
					int x2 = x;
					int y2 = y - 1;
					if (isCollide(x, y) || isCollide(x2, y2))
					{
						isMove = false;
						break;
					}
				}
				if (isMove)
				{
					// 移動開始
					if (isKeyDownR) { isMoveR = true; } else { isMoveL = true; }
				}
			}
		}

		// ぷよぷよ下移動
		float fast = (key == EventKeyboard::KeyCode::KEY_DOWN_ARROW) ? Game::PUYO_MOVE_FAST_Y : 1.0f;
		moveTimeY += delta * fast;
		isUpdate = (moveTimeY > Game::PUYO_MOVE_TIME_Y);
		value = (isUpdate) ? 1.0f : (moveTimeY / Game::PUYO_MOVE_TIME_Y);
		for (auto puyo : puyopuyo)
		{
			puyo->sprite->setPositionY(puyo->cell->getPositionY() - value * Game::CELL_SIZE);
			if (isUpdate) { puyo->y--; }
		}
		if (isUpdate)
		{
			// セル更新
			moveTimeY = 0.0f;
			updatePuyopuyoCell();

			// 次のセルへ移動可能か？
			bool isMove = true;
			for (auto puyo : puyopuyo)
			{
				if (isCollide(puyo, Game::Dir::DOWN)) 
				{
					isMove = false;
					break;
				}
			}
			if (!isMove)
			{
				// 移動出来ない場合は次のシーケンスへ
				puyopuyo[0] = nullptr;
				puyopuyo[1] = nullptr;
				dir = Game::Dir::UP;
				chainCount = 0;
				if (isFall()) { sq = Sq::FALL_EXEC; }
				else if (isVanish()) { sq = Sq::VANISH_FLASH_OUT; }
				else { sq = Sq::LAST_WAIT; }
			}
		}
	}
	else if (sq == Sq::FALL_EXEC)
	{
		// ぷよ落下/実行
		time += delta;
		bool isUpdate = (time > Game::PUYO_FALL_TIME);
		float value = (isUpdate) ? 1.0f : (time / Game::PUYO_FALL_TIME);
		for (auto puyo : puyos)
		{
			// 落下中
			if (puyo->isFall)
			{
				int fallValue = puyo->y - puyo->fallCell->y;
				puyo->sprite->setPositionY(puyo->cell->getPositionY() - value * fallValue * Game::CELL_SIZE);
				if (isUpdate) { puyo->y -= fallValue; }
			}
		}
		if (isUpdate)
		{
			// セル更新
			for (int i = 0; i < 2; i++)
			{
				for (auto puyo : puyos)
				{
					if (!puyo->isFall) { continue; }

					if (i == 0)
					{
						// セル情報初期化
						puyo->initCell();
					}
					else if (i == 1)
					{
						// セル情報更新
						puyo->updateCell(cells[puyo->x][puyo->y]);
					}
				}
			}

			// 次のシーケンスへ
			time = 0.0f;
			sq = Sq::FALL_BOUND;
		}
	}
	else if (sq == Sq::FALL_BOUND)
	{
		// ぷよ落下/バウンド
		time += delta;
		bool isUpdate = (time > Game::PUYO_FALL_BOUND_TIME);
		float value = (isUpdate) ? 1.0f : time / Game::PUYO_FALL_BOUND_TIME;
		for (auto puyo : puyos)
		{
			if (puyo->isFall) 
			{
				// 指定回数バウンドさせる
				if ((boundCount % 2) == 0)
				{
					puyo->sprite->setScale(1.0f - 0.2f * value);
				}
				else
				{
					puyo->sprite->setScale(0.8f + 0.2f * value);
				}
				if (isUpdate && boundCount == 1)
				{
					// バウンド終了
					puyo->isFall = false;
					puyo->fallCell = nullptr;
				}
			}
		}
		if (isUpdate)
		{
			time = 0.0f;
			if (boundCount == 1)
			{
				// バウンド終了
				boundCount = 0;
				if (isVanish()) { sq = Sq::VANISH_FLASH_OUT; }
				else { sq = Sq::LAST_WAIT; }
			}
			else
			{
				// バウンド継続
				boundCount++;
			}
		}
	}
	else if (sq == Sq::VANISH_FLASH_OUT)
	{
		// ぷよ消去/フラッシュアウト
		time += delta;
		bool isUpdate = (time > Game::PUYO_VANISH_FLASH_TIME);
		float value = (isUpdate) ? 1.0f : time / Game::PUYO_VANISH_FLASH_TIME;
		for (auto puyo : puyos)
		{
			if (puyo->isVanish)
			{
				puyo->sprite->setOpacity((int)(255 - 128 * value));
			}
		}
		if (isUpdate) 
		{
			time = 0.0f;
			sq = Sq::VANISH_FLASH_IN;
		}
	}
	else if (sq == Sq::VANISH_FLASH_IN)
	{
		// ぷよ消去/フラッシュイン
		time += delta;
		bool isUpdate = (time > Game::PUYO_VANISH_FLASH_TIME);
		float value = (isUpdate) ? 1.0f : time / Game::PUYO_VANISH_FLASH_TIME;
		for (auto puyo : puyos)
		{
			if (puyo->isVanish)
			{
				puyo->sprite->setOpacity((int)(255 + 128 * value));
			}
		}
		if (isUpdate)
		{
			time = 0.0f;
			sq = Sq::VANISH_FLASH_OUT2;
		}
	}
	else if (sq == Sq::VANISH_FLASH_OUT2)
	{
		// ぷよ消去/フラッシュアウト2
		time += delta;
		bool isUpdate = (time > Game::PUYO_VANISH_FLASH_TIME);
		float value = (isUpdate) ? 1.0f : time / Game::PUYO_VANISH_FLASH_TIME;
		for (auto puyo : puyos)
		{
			if (puyo->isVanish)
			{
				puyo->sprite->setOpacity((int)(255 - 128 * value));
			}
		}
		if (isUpdate)
		{
			time = 0.0f;
			sq = Sq::VANISH_WAIT;
		}
	}
	else if (sq == Sq::VANISH_WAIT)
	{
		// ぷよ消去/ウェイト
		time += delta;
		if (time > Game::PUYO_VANISH_WAIT_TIME)
		{
			time = 0.0f;
			sq = Sq::VANISH_FADE;
		}
	}
	else if (sq == Sq::VANISH_FADE)
	{
		// ぷよ消去/フェイド
		time += delta;
		bool isUpdate = (time > Game::PUYO_VANISH_FLASH_TIME);
		float value = (isUpdate) ? 1.0f : time / Game::PUYO_VANISH_FLASH_TIME;
		for (auto puyo : puyos)
		{
			if (puyo->isVanish)
			{
				puyo->sprite->setOpacity((int)(255 - 255 * value));
			}
		}
		if (isUpdate)
		{
			time = 0.0f;

			// 連鎖演出
			chainCount++;
			chainLabel->setString(StringUtils::format(Game::CHAIN_LABEL, chainCount));
			chainLabel->setOpacity(255);

			Cell* lu = nullptr; // 左上セル
			Cell* rd = nullptr; // 右下セル
			Cell* cc = nullptr; // 中央セル
			for (auto puyo : puyos)
			{
				if (puyo->isVanish)
				{
					if (lu == nullptr || (puyo->cell->x < lu->x && puyo->cell->y > lu->y))
					{
						lu = puyo->cell;
					}
					if (rd == nullptr || (puyo->cell->x > rd->x && puyo->cell->y < rd->y))
					{
						rd = puyo->cell;
					}
				}
			}
			cc = cells[lu->x + (rd->x - lu->x) / 2][rd->y + (lu->y - rd->y) / 2];
			chainLabel->setPosition(cc->getPosition());

			auto moveTo = MoveTo::create(0.3f, Vec2(chainLabel->getPositionX(), chainLabel->getPositionY() + 100.0f));
			auto fadeOut = FadeOut::create(0.5f);
			auto seq = Sequence::create(moveTo, fadeOut, nullptr);
			chainLabel->runAction(seq);
			chainLabel->setVisible(true);

			// 消去ぷよを削除
			auto it = puyos.begin();
			while (it != puyos.end())
			{
				auto puyo = *it;
				if (puyo->isVanish)
				{
					removePuyo(puyo);
					it = puyos.erase(it);
				}
				else
				{
					++it;
				}
			}

			// 次のシーケンスへ
			if (isFall()) { sq = Sq::FALL_EXEC; }
			else if (isVanish()) { sq = Sq::VANISH_FLASH_OUT; }
			else { sq = Sq::LAST_WAIT; }
		}
	}
	else if (sq == Sq::LAST_WAIT)
	{
		// 最終ウェイト
		time += delta;
		if (time > Game::PUYO_LAST_WAIT)
		{
			time = 0.0f;

			// バタンキュ～か？
			bool isBatankyu = false;
			for (int i = 0; i < 2; i++)
			{
				auto cell = cells[Game::PUYO_APPEAR_X][Game::PUYO_APPEAR_Y - i];
				if (cell->puyo != nullptr)
				{
					isBatankyu = true;
					break;
				}
			}
			if (isBatankyu)
			{
				// バタンキュ～
				sq = Sq::BATANKYU_WAIT;
			}
			else
			{
				// 次のぷよぷよ
				createPuyopuyo();
				if (cells[puyopuyo[1]->x][puyopuyo[1]->y - 1]->puyo != nullptr)
				{
					// 移動出来ない場合バタンキュ～
					sq = Sq::BATANKYU_WAIT;
				}
				else
				{
					// ユーザ入力へ
					sq = Sq::USER_INPUT;
				}
			}
		}
	}
	else if (sq == Sq::BATANKYU_WAIT)
	{
		// バタンキュ～/ウェイト
		time += delta;
		if (time > Game::BATANKYU_WAIT_TIME)
		{
			time = 0.0f;
			sq = Sq::BATANKYU_FADE;
		}
	}
	else if (sq == Sq::BATANKYU_FADE)
	{
		// バタンキュ～/フェイド
		time += delta;
		bool isUpdate = (time > Game::BATANKYU_FADE_TIME);
		int value = (int)(255 - 135 * ((isUpdate) ? 1.0f : (time / Game::BATANKYU_FADE_TIME)));
		auto color = Color3B(value, value, value);
		stageSprite->setColor(color);
		for (auto puyo : puyos)
		{
			puyo->sprite->setColor(color);
		}
		if (isUpdate) 
		{
			time = 0.0f;
			sq = Sq::BATANKYU_FADE_WAIT; 
		}
	}
	else if (sq == Sq::BATANKYU_FADE_WAIT)
	{
		// バタンキュ～/フェイドウェイト
		time += delta;
		if (time > Game::BATANKYU_FADE_WAIT_TIME)
		{
			// バタンキュ～画像生成
			batankyuSprite = Sprite::create(App::PATH_BATANKYU);
			batankyuSprite->setPosition(game->batankyuBasePos);
			batankyuSprite->setScale(0.0f);
			this->addChild(batankyuSprite, 1);

			time = 0.0f;
			sq = Sq::BATANKYU_SCALE_UP;
		}
	}
	else if (sq == Sq::BATANKYU_SCALE_UP)
	{
		// バタンキュ～/スケールアップ
		time += delta;
		bool isUpdate = (time > Game::BATANKYU_SCALE_UP_TIME);
		float value = Game::BATANKYU_SCALE_UP_VALUE * ((isUpdate) ? 1.0f : (time / Game::BATANKYU_SCALE_UP_TIME));
		batankyuSprite->setScale(value);
		if (isUpdate)
		{
			time = 0.0f;
			sq = Sq::BATANKYU_SCALE_DOWN;
		}
	}
	else if (sq == Sq::BATANKYU_SCALE_DOWN)
	{
		// バタンキュ～/スケールダウン
		time += delta;
		bool isUpdate = (time > Game::BATANKYU_SCALE_DOWN_TIME);
		float value = Game::BATANKYU_SCALE_UP_VALUE - Game::BATANKYU_SCALE_DOWN_VALUE * ((isUpdate) ? 1.0f : (time / Game::BATANKYU_SCALE_DOWN_TIME));
		batankyuSprite->setScale(value);
		if (isUpdate)
		{
			time = 0.0f;
			sq = Sq::NONE;
		}
	}

	// キー初期化
	this->keyDown = EventKeyboard::KeyCode::KEY_NONE;
}

/**
 * ぷよ作成
 * @param x X座標
 * @param y Y座標
 * @param type ぷよタイプ
 * @retrun ぷよ
 */
Puyo* SceneGame::createPuyo(int x, int y, Game::PuyoType type)
{
	auto puyo = (Puyo*)Puyo::create();
	puyo->x = x;
	puyo->y = y;
	puyo->type = type;
	puyo->sprite = Sprite::create(StringUtils::format(App::PATH_PUYO, type));
	this->addChild(puyo, 1);
	this->addChild(puyo->sprite, 1);
	puyos.push_back(puyo);
	return puyo;
}

/**
 * ぷよ削除
 * @param puyo ぷよ
 */
void SceneGame::removePuyo(Puyo* puyo)
{
	puyo->cell->puyo = nullptr;
	puyo->cell = nullptr;
	puyo->sprite->removeFromParentAndCleanup(true);
	puyo->removeFromParentAndCleanup(true);
}

/** 
 * ぷよぷよ作成
 */
void SceneGame::createPuyopuyo()
{
	for (int i = 0; i < 2; i++)
	{
		puyopuyo[i] = nextPuyopuyo[i];
		puyopuyo[i]->cell = cells[puyopuyo[i]->x][puyopuyo[i]->y];
		puyopuyo[i]->cell->puyo = puyopuyo[i];
		puyopuyo[i]->sprite->setPosition(puyopuyo[i]->cell->getPosition());

		nextPuyopuyo[i] = createPuyo(Game::PUYO_APPEAR_X, Game::PUYO_APPEAR_Y - i, (Game::PuyoType)App::getRandom(0, Game::PuyoType::COUNT));
		nextPuyopuyo[i]->sprite->setPosition(Vec2(game->puyopuyoBasePos.x + Game::CELL_SIZE, game->puyopuyoBasePos.y - (i + 1) * Game::CELL_SIZE));
	}
}

/**
 * ぷよぷよセル更新
 */
void SceneGame::updatePuyopuyoCell()
{
	for (int i = 0; i < 2; i++)
	{
		for (auto puyo : puyopuyo)
		{
			if (i == 0)
			{
				// セル情報初期化
				puyo->initCell();
			}
			else if (i == 1)
			{
				// セル情報更新
				puyo->updateCell(cells[puyo->x][puyo->y]);
			}
		}
	}
}

/** 
 * 衝突判定
 * @param puyo 判定ぷよ
 * @param dir 判定向き
 * @return 衝突する場合 true
 */
bool SceneGame::isCollide(Puyo* puyo, Game::Dir dir)
{
	int x = puyo->x + Game::MOVE_VALUES[dir][0];
	int y = puyo->y + Game::MOVE_VALUES[dir][1];
	return isCollide(x, y);
}

/**
 * 衝突判定
 * @param x X座標
 * @param y Y座標
 * @retrun 衝突する場合 true
 */
bool SceneGame::isCollide(int x, int y)
{
	if (x < 0 || x > Game::STAGE_COL - 1) { return true; }
	if (y < 0 || y > Game::STAGE_ROW - 1) { return true; }

	auto cell = cells[x][y];
	if (cell->puyo != nullptr && cell->puyo != puyopuyo[0] && cell->puyo != puyopuyo[1])
	{
		return true;
	}
	return false;
}

/** 
 * 落下判定
 * @retrun 落下する場合 true
 */
bool SceneGame::isFall()
{
	bool isSuccess = false;
	for (int x = 0; x < SIZE_OF_ARRAY(cells); x++)
	{
		for (int y = 0; y < SIZE_OF_ARRAY(cells[0]); y++)
		{
			int dy = y - 1;
			if (dy < 0) { continue; }

			auto cell = cells[x][y];
			auto dcell = cells[x][dy];
			auto puyo = cell->puyo;
			if (puyo == nullptr) { continue; }

			bool isNoPuyo = !isCollide(x, dy); // 下にぷよがない
			bool isConnectDown = (dcell->puyo != nullptr && dcell->puyo->isFall); // 落下ぷよで繋がってる
			if (isNoPuyo || isConnectDown)
			{
				// 落下ぷよ確定
				isSuccess = true;
				puyo->isFall = true;
				if (isConnectDown)
				{
					// 下が落下ぷよのものは下のぷよの落下セルの1つ上
					puyo->fallCell = cells[dcell->puyo->fallCell->x][dcell->puyo->fallCell->y + 1];
				}
				else
				{
					// 下にぷよがないものは落下セルを検索
					int fx = x;
					int fy = dy;
					while (true)
					{
						if (isCollide(x, fy))
						{
							// 衝突したセルの1つ上が落下セル
							puyo->fallCell = cells[fx][fy + 1];
							break;
						}
						fy--;
					}
				}
			}
		}
	}
	return isSuccess;
}

/** 
 * 消去判定
 * @retrun 消去する場合 true
 */
bool SceneGame::isVanish()
{
	bool isSuccess = false;

	// 消去チェック
	int id = 1;
	for (auto puyo : puyos)
	{
		checkVanish(puyo, id);
		id++;
	}

	// 消去可能なIDを抽出
	vanishIds.clear();
	std::map<int, int>::iterator it = vanishCounter.begin();
	while (it != vanishCounter.end())
	{
		int id = (*it).first;
		int count = (*it).second;
		if (count >= Game::PUYO_VANISH_COUNT)
		{
			vanishIds.push_back(id);
		}
		++it;
	}

	// 消去ぷよが存在するか？
	isSuccess = (!vanishIds.empty());
	if (isSuccess)
	{
		// 消去設定
		for (auto puyo : puyos)
		{
			puyo->isVanish = false;
			for (int id : vanishIds)
			{
				if (id == puyo->vanishId)
				{
					puyo->isVanish = true;
					break;
				}
			}
		}
	}

	// 後始末
	vanishCounter.clear();
	vanishIds.clear();
	for (auto puyo : puyos)
	{
		puyo->vanishId = 0;
	}
	return isSuccess;
}

/** 
 * 消去チェック
 * @param puyo ぷよ
 * @param id 消去ID
 */
void SceneGame::checkVanish(Puyo* puyo, int id)
{
	if (puyo->vanishId != 0) { return; }

	puyo->vanishId = id;
	vanishCounter[id] = (vanishCounter.find(id) == vanishCounter.end()) ? 1 : (vanishCounter[id] + 1);

	int  x = puyo->x;
	int  y = puyo->y;
	int rx = x + 1;
	int lx = x - 1;
	int uy = y + 1;
	int dy = y - 1;
	if (isConnect(puyo, rx, y)) { checkVanish(cells[rx][y]->puyo, id); }
	if (isConnect(puyo, lx, y)) { checkVanish(cells[lx][y]->puyo, id); }
	if (isConnect(puyo, x, uy)) { checkVanish(cells[x][uy]->puyo, id); }
	if (isConnect(puyo, x, dy)) { checkVanish(cells[x][dy]->puyo, id); }
}

/** 
 * ぷよ繋がり判定
 * @param puyo ぷよ
 * @param x X座標
 * @param y Y座標
 * @retrun 繋がってたら true
 */
bool SceneGame::isConnect(Puyo* puyo, int x, int y)
{
	if (x < 0 || x > Game::STAGE_COL - 1) { return false; }
	if (y < 0 || y > Game::STAGE_ROW - 1) { return false; }

	Puyo* toPuyo = cells[x][y]->puyo;
	return (toPuyo != nullptr && puyo->type == toPuyo->type);
}