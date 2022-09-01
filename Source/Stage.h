#pragma once

class Input;

/**
 * 게임 내의 스테이지 클래스입니다.
 * 이때, 이 클래스는 추상 클래스입니다.
 */
class Stage
{
public:
	/**
	 * 게임 내의 스테이지 클래스의 생성자입니다.
	 */
	Stage() = default;


	/**
	 * 게임 내의 스테이지 클래스의 가상 소멸자입니다.
	 */
	virtual ~Stage();


	/**
	 * 스테이지의 입력 처리를 수행합니다.
	 * 
	 * @param InInput - 입력 상태를 관리하는 객체의 인스턴스입니다.
	 */
	virtual void ProcessInput(const Input& InInput) = 0;


	/**
	 * 스테이지를 업데이트합니다.
	 */
	virtual void Update() = 0;


	/**
	 * 스테이지를 콘솔 화면에 그립니다.
	 */
	virtual void Draw() = 0;
};