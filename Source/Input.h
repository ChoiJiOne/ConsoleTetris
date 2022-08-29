#pragma once

#include <windows.h>
#include <unordered_map>


/**
 * 입력 처리 클래스입니다.
 * 이때, 이 클래스는 키보드 입력만 처리합니다.
 */
class Input
{
public:
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
		None     = 0,
		Pressed  = 1,
		Released = 2,
		Held     = 3
	};


	/**
	 * 입력 처리 클래스에서 지원하는 키의 종류입니다.
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
	 * 입력 처리 클래스의 생성자입니다.
	 */
	Input();


	/**
	 * 입력 처리 클래스의 복사 생성자입니다.
	 * 
	 * @param InInstance - 복사를 수행할 객체입니다.
	 */
	Input(Input&& InInstance) noexcept;
	

	/**
	 * 입력 처리 클래스의 복사 생성자입니다.
	 * 
	 * @param InInstance - 복사를 수행할 객체입니다.
	 */
	Input(const Input& InInstance) noexcept;


	/**
	 * 입력 처리 클래스의 가상 소멸자입니다.
	 */
	virtual ~Input();


	/**
	 * 입력 처리 클래스의 대입 연산자입니다.
	 * 
	 * @param InInstance - 복사를 수행할 객체입니다.
	 * 
	 * @return 복사를 수행한 객체의 참조자를 반환합니다.
	 */
	Input& operator=(Input&& InInstance) noexcept;
	

	/**
	 * 입력 처리 클래스의 대입 연산자입니다.
	 * 
	 * @param InInstance - 복사를 수행할 객체입니다.
	 *
	 * @return 복사를 수행한 객체의 참조자를 반환합니다.
	 */
	Input& operator=(const Input& InInstance) noexcept;


	/**
	 * 입력 상태를 업데이트합니다.
	 */
	void Update();


	/**
	 * 키의 입력 상태를 얻습니다.
	 * 
	 * @param InKeyType - 입력 상태를 확인할 키 타입입니다.
	 * 
	 * @return 키의 입력 상태를 반환합니다.
	 */
	EPressState GetKeyPressState(const EKeyType& InKeyType);


private:
	/**
	 * 키가 눌렸는지 확인합니다.
	 * 
	 * @param InKeyType - 눌렸는지 확인할 키 타입입니다.
	 * 
	 * @return 키가 눌렸다면 true, 그렇지 않다면 false를 반환합니다.
	 */
	bool IsPressKey(const EKeyType& InKeyType);


private:
	/**
	 * 업데이트 이전의 키 상태입니다.
	 */
	std::unordered_map<EKeyType, bool> PrevKeyState;


	/**
	 * 업데이트 이후의 키 상태입니다.
	 */
	std::unordered_map<EKeyType, bool> CurrKeyState;
};