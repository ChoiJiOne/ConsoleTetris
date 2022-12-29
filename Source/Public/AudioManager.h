#pragma once

#include <Macro.h>

typedef struct ma_engine ma_engine;
typedef struct ma_sound  ma_sound;


/**
 * 오디오 관련 처리를 수행하는 클래스입니다.
 * 이때, 이 클래스는 싱글턴입니다.
 */
class AudioManager
{
public:
	/**
	 * 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(AudioManager);


	/**
	 * AudioManager의 싱글 인스턴스를 얻습니다.
	 * 
	 * @return AudioManager의 인스턴스를 얻습니다.
	 */
	static AudioManager& Get()
	{
		static AudioManager Instance;
		return Instance;
	}


	/**
	 * AudioManager 에서 사용하는 miniaudio의 엔진 포인터를 얻습니다.
	 * 
	 * @return miniaudio의 포인터를 반환합니다.
	 */
	ma_engine* GetMiniaudioEngine();


private:
	/**
	 * AudioManager의 생성자입니다.
	 */
	AudioManager();


	/**
	 * AudioManager의 가상 소멸자입니다.
	 */
	virtual ~AudioManager();
};