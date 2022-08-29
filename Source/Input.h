#pragma once

#include <windows.h>
#include <unordered_map>


/**
 * �Է� ó�� Ŭ�����Դϴ�.
 * �̶�, �� Ŭ������ Ű���� �Է¸� ó���մϴ�.
 */
class Input
{
public:
	/**
	 * �Է� ���¸� ��Ÿ���ϴ�.
	 * --------------------------------------
	 * | ���� ������ | ���� ������ | �Է� ���� |
	 * --------------------------------------
	 * |     0      |     0      | None     |
	 * |     0      |     1      | Pressed  |
	 * |     1      |     0      | Released |
	 * |     1      |     1      | Held     |
	 * --------------------------------------
	 */
	enum class EPressState : int32_t
	{
		None     = 0,
		Pressed  = 1,
		Released = 2,
		Held     = 3
	};


	/**
	 * �Է� ó�� Ŭ�������� �����ϴ� Ű�� �����Դϴ�.
	 */
	enum class EKeyType : int32_t
	{
		Up     = VK_UP,
		Down   = VK_DOWN,
		Left   = VK_LEFT,
		Right  = VK_RIGHT,
		Escape = VK_ESCAPE,
		Space  = VK_SPACE,
		Enter  = VK_RETURN,
	};


public:
	/**
	 * �Է� ó�� Ŭ������ �������Դϴ�.
	 */
	Input();


	/**
	 * �Է� ó�� Ŭ������ ���� �������Դϴ�.
	 * 
	 * @param InInstance - ���縦 ������ ��ü�Դϴ�.
	 */
	Input(Input&& InInstance) noexcept;
	

	/**
	 * �Է� ó�� Ŭ������ ���� �������Դϴ�.
	 * 
	 * @param InInstance - ���縦 ������ ��ü�Դϴ�.
	 */
	Input(const Input& InInstance) noexcept;


	/**
	 * �Է� ó�� Ŭ������ ���� �Ҹ����Դϴ�.
	 */
	virtual ~Input();


	/**
	 * �Է� ó�� Ŭ������ ���� �������Դϴ�.
	 * 
	 * @param InInstance - ���縦 ������ ��ü�Դϴ�.
	 * 
	 * @return ���縦 ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	Input& operator=(Input&& InInstance) noexcept;
	

	/**
	 * �Է� ó�� Ŭ������ ���� �������Դϴ�.
	 * 
	 * @param InInstance - ���縦 ������ ��ü�Դϴ�.
	 *
	 * @return ���縦 ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	Input& operator=(const Input& InInstance) noexcept;


	/**
	 * �Է� ���¸� ������Ʈ�մϴ�.
	 */
	void Update();


	/**
	 * Ű�� �Է� ���¸� ����ϴ�.
	 * 
	 * @param InKeyType - �Է� ���¸� Ȯ���� Ű Ÿ���Դϴ�.
	 * 
	 * @return Ű�� �Է� ���¸� ��ȯ�մϴ�.
	 */
	EPressState GetKeyPressState(const EKeyType& InKeyType);


private:
	/**
	 * Ű�� ���ȴ��� Ȯ���մϴ�.
	 * 
	 * @param InKeyType - ���ȴ��� Ȯ���� Ű Ÿ���Դϴ�.
	 * 
	 * @return Ű�� ���ȴٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	bool IsPressKey(const EKeyType& InKeyType);


private:
	/**
	 * ������Ʈ ������ Ű �����Դϴ�.
	 */
	std::unordered_map<EKeyType, bool> PrevKeyState;


	/**
	 * ������Ʈ ������ Ű �����Դϴ�.
	 */
	std::unordered_map<EKeyType, bool> CurrKeyState;
};