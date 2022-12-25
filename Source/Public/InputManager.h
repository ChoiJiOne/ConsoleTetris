#pragma once

#include <Macro.h>

#include <unordered_map>


/**
 * 입력 상태를 나타냅니다.
 * --------------------------------------
 * | 이전 프레임 | 현재 프레임 | 입력 상태 |
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
 * 입력 처리 키의 종류입니다.
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
 * 입력 처리를 수행하는 클래스입니다.
 * 이때, 이 클래스는 싱글턴입니다.
 */
class InputManager
{
public:
	/**
	 * 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(InputManager);


	/**
	 * InputManager의 싱글 인스턴스를 얻습니다.
	 * 
	 * @return InputManager의 인스턴스를 반환합니다.
	 */
	static InputManager& Get()
	{
		static InputManager Instance;
		return Instance;
	}

	
	/**
	 * 입력 처리 상태를 업데이트합니다.
	 */
	void Tick();


	/**
	 * 키의 입력 상태를 얻습니다.
	 *
	 * @param InKeyCode - 입력 상태를 확인할 키 코드입니다.
	 *
	 * @return 키의 입력 상태를 반환합니다.
	 */
	EPressState GetKeyPressState(const EKeyCode& InKeyCode) const;


private:
	/**
	 * InputManager의 생성자입니다.
	 */
	InputManager();


	/**
	 * InputManager의 가상 소멸자입니다.
	 */
	virtual ~InputManager() = default;


	/**
	 * 키가 눌렸는지 확인합니다.
	 *
	 * @param InKeyCode - 눌렸는지 확인할 키 코드입니다.
	 *
	 * @return 키가 눌렸다면 true, 그렇지 않다면 false를 반환합니다.
	 */
	bool IsPressKey(const EKeyCode& InKeyCode) const;


private:
	/**
	 * Tick 호출 이전의 키 상태입니다.
	 */
	std::unordered_map<EKeyCode, bool> PrevKeyState_;


	/**
	 * Tick 호출 이후의 키 상태입니다.
	 */
	std::unordered_map<EKeyCode, bool> CurrKeyState_;
};