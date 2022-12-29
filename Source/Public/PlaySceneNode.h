#pragma once

#include <Vector.hpp>
#include <SceneNode.h>

#include <unordered_map>

class Board;
class Tetromino;


/**
 * 플레이 씬의 노드입니다.
 */
class PlaySceneNode : public SceneNode
{
public:
	/**
	 * 게임 플레이어의 레벨입니다.
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
	 * 플레이 씬 노드의 생성자입니다.
	 */
	explicit PlaySceneNode();


	/**
	 * 플레이 씬 노드의 가상 소멸자입니다.
	 */
	virtual ~PlaySceneNode();


	/**
	 * 복사 생성자와 대입 연산자를 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(PlaySceneNode);


	/**
	 * 플레이 씬의 모든 요소를 리셋합니다.
	 */
	void Reset();


	/**
	 * 플레이 시간을 얻습니다.
	 * 
	 * @return 플레이 시간을 반환합니다.
	 */
	float GetPlayTime() const { return PlayTime_; }


	/**
	 * 플레이어가 삭제한 라인 수를 얻습니다.
	 * 
	 * @return 플레이어가 삭제한 라인 수를 반환합니다.
	 */
	int32_t GetRemoveLine() const;


	/**
	 * 플레이어의 레벨을 얻습니다.
	 * 
	 * @return 플레이어의 레벨을 반환합니다.
	 */
	ELevel GetPlayerLevel() const { return Level_; }


	/**
	 * 플레이 씬을 업데이트합니다.
	 *
	 * @param InDeltaTime - 초단위 델타 시간값입니다.
	 */
	virtual void Update(float InDeltaSeconds) override;


	/**
	 * 플레이 씬을 화면에 그립니다.
	 */
	virtual void Render() override;


private:
	/**
	 * 플레이 씬의 모든 요소를 정리합니다.
	 */
	void CleanupAllProperties();


private:
	/**
	 * 게임 플레이 타임입니다.
	 */
	float PlayTime_ = 0.0f;


	/**
	 * 게임 플레이 타임의 콘솔 상 위치입니다.
	 */
	Vec2i PlayTimePosition_;


	/**
	 * 플레이어가 삭제한 라인 수의 콘솔 상 위치입니다.
	 */
	Vec2i RemoveLinePosition_;


	/**
	 * 플레이어의 레벨입니다.
	 */
	ELevel Level_ = ELevel::LEVEL1;


	/**
	 * 레벨 증가를 확인하기 위한 누적 시간 ㄴ값입니다.
	 */
	float AccruePlayTime_ = 0.0f;


	/**
	 * 플레이어 레벨의 콘솔 상 위치입니다.
	 */
	Vec2i PlayerLevelPosition_;


	/**
	 * 테트리스 보드의 위치입니다.
	 */
	Vec2i BoardPosition_;


	/**
	 * 테트로미노의 시작점입니다.
	 */
	Vec2i StartPosition_;


	/**
	 * 테트로미노의 대기점입니다.
	 */
	Vec2i WaitPosition_;


	/**
	 * 현재 테트로미노 입니다.
	 */
	std::shared_ptr<Tetromino> CurrTetromino_ = nullptr;


	/**
	 * 다음 테트로미노입니다.
	 */
	std::shared_ptr<Tetromino> NextTetromino_ = nullptr;


	/**
	 * 테트리스 보드입니다.
	 */
	std::unique_ptr<Board> Board_ = nullptr;


	/**
	 * 플레이어 레벨에 대응하는 최대 테트로미노 누적 시간입니다.
	 */
	static std::unordered_map<ELevel, const float> LevelToMaxAccrueTime_;
};