#pragma once

#include <cstdint>
#include <unordered_map>


/**
 * 입력 상태를 나타냅니다.
 * --------------------------------------
 * | 이전 프레임 | 현재 프레임 | 입력 상태 |
 * --------------------------------------
 * |     0      |     0      | NONE     |
 * |     0      |     1      | PRESSED  |
 * |     1      |     0      | RELEASED |
 * |     1      |     1      | HELD     |
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
 * 키 코드값입니다.
 */
enum class EKeyCode : int32_t
{
    ENTER = 10,
    ESC   = 27,
    SPACE = 32,
    DOWN  = 258,
    UP    = 259,
    LEFT  = 260,
    RIGHT = 261
};


/**
 * 입력 처리를 수행하는 클래스입니다.
 * 이때, 이 입력 처리 클래스는 싱글턴입니다.
 */
class InputManager 
{
public:
    /**
     * ConsoleManager의 인스턴스를 얻습니다.
     * 
     * @return ConsoleManager의 인스턴스를 반환합니다. 
     */
    static InputManager& Get() { return InputManager_; }


    /**
     * 입력 처리 상태를 업데이트합니다. 
     */
    void Tick();


    /**
     * 키의 입력 상태를 얻습니다.
     * 
     * @param InKeyCode - 검사할 키 코드값입니다.
     * 
     * @return 키 코드에 대응하는 키의 상태를 얻습니다.
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
    virtual ~InputManager();


private:
    /**
     * InputManager의 인스턴스입니다.
     * 이 인스턴스는 하나만 존재합니다.
     */
    static InputManager InputManager_;


    /**
     * Tick 호출 이전의 키 상태입니다.
     */
    std::unordered_map<EKeyCode, bool> PrevKeyState_;


    /**
     * Tick 호출 이후의 키 상태입니다.
     */
    std::unordered_map<EKeyCode, bool> CurrKeyState_;
};