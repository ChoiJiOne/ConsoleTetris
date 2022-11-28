#pragma once

#include <cstdint>


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


    /**
     * 콘솔 창의 커서가 시야에 보일지 설정합니다.
     * 
     * @param bIsVisible true면 콘솔 창의 커서사 시야에 보이고, 그렇지 않으면 보이지 않습니다.
     */
    void SetCursorVisible(bool bIsVisible);


    /**
     * 콘솔 창의 커서를 이동시킵니다.
     * 
     * @param InPositionX - 커서가 이동할 x좌표입니다.
     * @param InPositionY - 커서가 이동할 y좌표입니다.
     */
    void MoveCursor(const int32_t& InPositionX, const int32_t& InPositionY);


    /**
     * 콘솔 창을 업데이트합니다.
     */
    void Refresh();


    /**
     * 콘솔 창을 초기화합니다.
     */
    void Clear();

    
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