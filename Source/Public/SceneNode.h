#pragma once

#include <Macro.h>

#include <string>
#include <list>
#include <functional>


/**
 * ���� ���� ���� ��Ÿ���� ����Դϴ�.
 * �̶�, �� ������ ������ ���� ������ �����մϴ�.
 * ��, ���� ��带 �� �� �̻� ������ ���� �����ϴ�.
 */
class SceneNode
{
public:
	/**
	 * �� ����� �������Դϴ�.
	 * 
	 * @param InSignature - �� ����� �ñ״�ó�Դϴ�.
	 */
	explicit SceneNode(const std::string& InSignature)
		: Signature_(InSignature) {}


	/**
	 * �� ����� ���� �Ҹ����Դϴ�.
	 */
	virtual ~SceneNode() {}


	/**
	 * ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(SceneNode);


	/**
	 * �� ����� �ñ״�ó ���� ����ϴ�.
	 * 
	 * @return �� ����� �ñ״�ó ���� ��ȯ�մϴ�.
	 */
	const std::string& GetSignature() const { return Signature_; }


	/**
	 * ��忡 ��ȯ�� �߻����� ��, ������ �̺�Ʈ�� �����մϴ�.
	 * 
	 * @param InSwitchEvent - ����� ��Ȱ�� �߻����� �� ������ �̺�Ʈ�Դϴ�.
	 */
	void SetSwitchEvent(const std::function<void()>& InSwitchEvent) { SwitchEvent_ = InSwitchEvent; }


	/**
	 * ��忡 ��ȯ�� �߻����� ��, ������ �̺�Ʈ�� �����մϴ�.
	 */
	void RunSwitchEvent()
	{
		if (SwitchEvent_) SwitchEvent_();
	}


	/**
	 * ���� �� ��忡 �ٸ� �� ��带 �����մϴ�.
	 * �̶�, ���� ��������� ����˴ϴ�.
	 * ��, �ڱ� �ڽ��� �����ϰų� �̹� ������ �Ǿ� �ִٸ� �ƹ��� ���۵� ���� �ʽ��ϴ�.
	 *
	 * @param InSceneNode - ������ �� ����Դϴ�.
	 */
	void LinkNode(SceneNode* InSceneNode);


	/**
	 * ���� �� ��忡 ����� �ٸ� �� ����� ������ �����մϴ�.
	 * �̶�, ����� �ٸ� ��嵵 ���� �����մϴ�.
	 * ��, ���� ������ ����� �������� ������ �ƹ��� ���۵� �������� �ʽ��ϴ�.
	 *
	 * @param InSceneNode - ���� ������ �� ����Դϴ�.
	 */
	void UnlinkNode(SceneNode* InSceneNode);


	/**
	 * ���� �� ��忡 ����� Ư�� ��带 ã���ϴ�.
	 * 
	 * @param InSignature - ã�� ����� �ñ״�ó ���Դϴ�.
	 * 
	 * @return ���ϴ� ��带 ã�Ҵٸ� �ش� ����� �����͸�, �׷��� �ʴٸ� nullptr�� ��ȯ�մϴ�.
	 */
	SceneNode* FindLinkNode(const std::string& InSignature);


	/**
	 * ���� �� ���� ����� ��� ����� ����ϴ�.
	 *
	 * @return ���� �� ���� ����� ��� ����� ����ϴ�.
	 */
	const std::list<SceneNode*>& GetLinkNodes() const { return LinkNodes_; }


	/**
	 * ���� ���� ������Ʈ�մϴ�.
	 * 
	 * @param InDeltaTime - �ʴ��� ��Ÿ �ð����Դϴ�.
	 */
	virtual void Update(float InDeltaSeconds) = 0;


	/**
	 * ���� ���� ȭ�鿡 �׸��ϴ�.
	 */
	virtual void Render() = 0;


private:
	/**
	 * �� �׷��� ����� �ñ״�ó ���Դϴ�.
	 */
	std::string Signature_;


	/**
	 * ����� ��ȯ�� �߻����� ��, ó���� �̺�Ʈ�Դϴ�.
	 */
	std::function<void()> SwitchEvent_;


	/**
	 * ���� �� ���� ����� ��� ����Դϴ�.
	 */
	std::list<SceneNode*> LinkNodes_;

};