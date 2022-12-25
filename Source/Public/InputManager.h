#pragma once

#include <Macro.h>

#include <unordered_map>


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
	NONE     = 0,
	PRESSED  = 1,
	RELEASED = 2,
	HELD     = 3
};


/**
 * �Է� ó�� Ű�� �����Դϴ�.
 */
enum class EKeyCode : int32_t
{
	TAB    = 0x09,
	ENTER  = 0x0D,
	ESCAPE = 0x1B,
	SPACE  = 0x20,
	LEFT   = 0x25,
	UP     = 0x26,
	RIGHT  = 0x27,
	DOWN   = 0x28,
};


/**
 * �Է� ó���� �����ϴ� Ŭ�����Դϴ�.
 * �̶�, �� Ŭ������ �̱����Դϴ�.
 */
class InputManager
{
public:
	/**
	 * ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(InputManager);


	/**
	 * InputManager�� �̱� �ν��Ͻ��� ����ϴ�.
	 * 
	 * @return InputManager�� �ν��Ͻ��� ��ȯ�մϴ�.
	 */
	static InputManager& Get()
	{
		static InputManager Instance;
		return Instance;
	}

	
	/**
	 * �Է� ó�� ���¸� ������Ʈ�մϴ�.
	 */
	void Tick();


	/**
	 * Ű�� �Է� ���¸� ����ϴ�.
	 *
	 * @param InKeyCode - �Է� ���¸� Ȯ���� Ű �ڵ��Դϴ�.
	 *
	 * @return Ű�� �Է� ���¸� ��ȯ�մϴ�.
	 */
	EPressState GetKeyPressState(const EKeyCode& InKeyCode) const;


private:
	/**
	 * InputManager�� �������Դϴ�.
	 */
	InputManager();


	/**
	 * InputManager�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~InputManager() = default;


	/**
	 * Ű�� ���ȴ��� Ȯ���մϴ�.
	 *
	 * @param InKeyCode - ���ȴ��� Ȯ���� Ű �ڵ��Դϴ�.
	 *
	 * @return Ű�� ���ȴٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	bool IsPressKey(const EKeyCode& InKeyCode) const;


private:
	/**
	 * Tick ȣ�� ������ Ű �����Դϴ�.
	 */
	std::unordered_map<EKeyCode, bool> PrevKeyState_;


	/**
	 * Tick ȣ�� ������ Ű �����Դϴ�.
	 */
	std::unordered_map<EKeyCode, bool> CurrKeyState_;
};