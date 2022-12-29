#pragma once

#include <Vector.hpp>
#include <SceneNode.h>

#include <unordered_map>

class Board;
class Tetromino;


/**
 * �÷��� ���� ����Դϴ�.
 */
class PlaySceneNode : public SceneNode
{
public:
	/**
	 * ���� �÷��̾��� �����Դϴ�.
	 */
	enum class ELevel : int32_t
	{
		LEVEL1 = 1,
		LEVEL2 = 2,
		LEVEL3 = 3,
		LEVEL4 = 4,
		LEVEL5 = 5,
		LEVEL6 = 6,
	};


public:
	/**
	 * �÷��� �� ����� �������Դϴ�.
	 */
	explicit PlaySceneNode();


	/**
	 * �÷��� �� ����� ���� �Ҹ����Դϴ�.
	 */
	virtual ~PlaySceneNode();


	/**
	 * ���� �����ڿ� ���� �����ڸ� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(PlaySceneNode);


	/**
	 * �÷��� ���� ��� ��Ҹ� �����մϴ�.
	 */
	void Reset();


	/**
	 * �÷��� �ð��� ����ϴ�.
	 * 
	 * @return �÷��� �ð��� ��ȯ�մϴ�.
	 */
	float GetPlayTime() const { return PlayTime_; }


	/**
	 * �÷��̾ ������ ���� ���� ����ϴ�.
	 * 
	 * @return �÷��̾ ������ ���� ���� ��ȯ�մϴ�.
	 */
	int32_t GetRemoveLine() const;


	/**
	 * �÷��̾��� ������ ����ϴ�.
	 * 
	 * @return �÷��̾��� ������ ��ȯ�մϴ�.
	 */
	ELevel GetPlayerLevel() const { return Level_; }


	/**
	 * �÷��� ���� ������Ʈ�մϴ�.
	 *
	 * @param InDeltaTime - �ʴ��� ��Ÿ �ð����Դϴ�.
	 */
	virtual void Update(float InDeltaSeconds) override;


	/**
	 * �÷��� ���� ȭ�鿡 �׸��ϴ�.
	 */
	virtual void Render() override;


private:
	/**
	 * �÷��� ���� ��� ��Ҹ� �����մϴ�.
	 */
	void CleanupAllProperties();


private:
	/**
	 * ���� �÷��� Ÿ���Դϴ�.
	 */
	float PlayTime_ = 0.0f;


	/**
	 * ���� �÷��� Ÿ���� �ܼ� �� ��ġ�Դϴ�.
	 */
	Vec2i PlayTimePosition_;


	/**
	 * �÷��̾ ������ ���� ���� �ܼ� �� ��ġ�Դϴ�.
	 */
	Vec2i RemoveLinePosition_;


	/**
	 * �÷��̾��� �����Դϴ�.
	 */
	ELevel Level_ = ELevel::LEVEL1;


	/**
	 * ���� ������ Ȯ���ϱ� ���� ���� �ð� �����Դϴ�.
	 */
	float AccruePlayTime_ = 0.0f;


	/**
	 * �÷��̾� ������ �ܼ� �� ��ġ�Դϴ�.
	 */
	Vec2i PlayerLevelPosition_;


	/**
	 * ��Ʈ���� ������ ��ġ�Դϴ�.
	 */
	Vec2i BoardPosition_;


	/**
	 * ��Ʈ�ι̳��� �������Դϴ�.
	 */
	Vec2i StartPosition_;


	/**
	 * ��Ʈ�ι̳��� ������Դϴ�.
	 */
	Vec2i WaitPosition_;


	/**
	 * ���� ��Ʈ�ι̳� �Դϴ�.
	 */
	std::shared_ptr<Tetromino> CurrTetromino_ = nullptr;


	/**
	 * ���� ��Ʈ�ι̳��Դϴ�.
	 */
	std::shared_ptr<Tetromino> NextTetromino_ = nullptr;


	/**
	 * ��Ʈ���� �����Դϴ�.
	 */
	std::unique_ptr<Board> Board_ = nullptr;


	/**
	 * �÷��̾� ������ �����ϴ� �ִ� ��Ʈ�ι̳� ���� �ð��Դϴ�.
	 */
	static std::unordered_map<ELevel, const float> LevelToMaxAccrueTime_;
};