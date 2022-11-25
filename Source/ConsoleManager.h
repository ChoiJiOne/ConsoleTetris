#pragma once

/**
 * 콘솔 관련 처리를 수행하는 클래스입니다.
 * 이때, 이 콘솔 메니저 클래스는 싱글턴이고 
 * ncurses 라이브러리를 기반 구현되었습니다. 
 */
class ConsoleManager
{
public:
    /**
     * ConsoleManager의 인스턴스를 얻습니다.
     * 
     * @return ConsoleManager의 인스턴스를 반환합니다. 
     */
    static ConsoleManager& Get() { return ConsoleManager_; }

    
private:
    /**
     * ConsoleManager의 생성자입니다.
     */
    ConsoleManager();


    /**
     * ConsoleManager의 가상 소멸자입니다.
     */
    virtual ~ConsoleManager();


private:
    /**
     * ConsoleManager의 인스턴스입니다.
     * 이 인스턴스는 하나만 존재합니다.
     */
    static ConsoleManager ConsoleManager_;
};