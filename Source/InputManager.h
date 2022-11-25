#pragma once


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
};