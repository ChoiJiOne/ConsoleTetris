#pragma once

#include <Vector.hpp>
#include <SceneNode.h>

class Board;
class Tetromino;


/**
 * �÷��� ���� ����Դϴ�.
 */
class PlaySceneNode : public SceneNode
{
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
};