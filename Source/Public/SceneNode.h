#pragma once

#include <Macro.h>

#include <string>
#include <list>
#include <functional>


/**
 * 게임 내의 씬을 나타내는 노드입니다.
 * 이때, 이 각각의 노드들은 서로 연결이 가능합니다.
 * 단, 같은 노드를 두 번 이상 연결할 수는 없습니다.
 */
class SceneNode
{
public:
	/**
	 * 씬 노드의 생성자입니다.
	 * 
	 * @param InSignature - 씬 노드의 시그니처입니다.
	 */
	explicit SceneNode(const std::string& InSignature)
		: Signature_(InSignature) {}


	/**
	 * 씬 노드의 가상 소멸자입니다.
	 */
	virtual ~SceneNode() {}


	/**
	 * 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(SceneNode);


	/**
	 * 씬 노드의 시그니처 값을 얻습니다.
	 * 
	 * @return 씬 노드의 시그니처 값을 반환합니다.
	 */
	const std::string& GetSignature() const { return Signature_; }


	/**
	 * 노드에 전환이 발생했을 때, 실행할 이벤트를 설정합니다.
	 * 
	 * @param InSwitchEvent - 노드의 전활이 발생했을 때 실행할 이벤트입니다.
	 */
	void SetSwitchEvent(const std::function<void()>& InSwitchEvent) { SwitchEvent_ = InSwitchEvent; }


	/**
	 * 노드에 전환이 발생했을 때, 실행할 이벤트를 실행합니다.
	 */
	void RunSwitchEvent()
	{
		if (SwitchEvent_) SwitchEvent_();
	}


	/**
	 * 현재 씬 노드에 다른 씬 노드를 연결합니다.
	 * 이때, 노드는 양방향으로 연결됩니다.
	 * 단, 자기 자신을 연결하거나 이미 연결이 되어 있다면 아무런 동작도 하지 않습니다.
	 *
	 * @param InSceneNode - 연결할 씬 노드입니다.
	 */
	void LinkNode(SceneNode* InSceneNode);


	/**
	 * 현재 씬 노드에 연결된 다른 씬 노드의 연결을 해제합니다.
	 * 이때, 연결된 다른 노드도 연결 해제합니다.
	 * 단, 연결 해제할 대상이 존재하지 않으면 아무런 동작도 수행하지 않습니다.
	 *
	 * @param InSceneNode - 연결 해제할 씬 노드입니다.
	 */
	void UnlinkNode(SceneNode* InSceneNode);


	/**
	 * 현재 씬 노드에 연결된 특정 노드를 찾습니다.
	 * 
	 * @param InSignature - 찾을 노드의 시그니처 값입니다.
	 * 
	 * @return 원하는 노드를 찾았다면 해당 노드의 포인터를, 그렇지 않다면 nullptr를 반환합니다.
	 */
	SceneNode* FindLinkNode(const std::string& InSignature);


	/**
	 * 현재 씬 노드와 연결된 노드 목록을 얻습니다.
	 *
	 * @return 현재 씬 노드와 연결된 노드 목록을 얻습니다.
	 */
	const std::list<SceneNode*>& GetLinkNodes() const { return LinkNodes_; }


	/**
	 * 현재 씬을 업데이트합니다.
	 * 
	 * @param InDeltaTime - 초단위 델타 시간값입니다.
	 */
	virtual void Update(float InDeltaSeconds) = 0;


	/**
	 * 현재 씬을 화면에 그립니다.
	 */
	virtual void Render() = 0;


private:
	/**
	 * 씬 그래프 노드의 시그니처 값입니다.
	 */
	std::string Signature_;


	/**
	 * 노드의 전환이 발생했을 때, 처리할 이벤트입니다.
	 */
	std::function<void()> SwitchEvent_;


	/**
	 * 현재 씬 노드와 연결된 노드 목록입니다.
	 */
	std::list<SceneNode*> LinkNodes_;

};