#pragma once

#include <Macro.h>

typedef struct ma_engine ma_engine;
typedef struct ma_sound  ma_sound;


/**
 * ����� ���� ó���� �����ϴ� Ŭ�����Դϴ�.
 * �̶�, �� Ŭ������ �̱����Դϴ�.
 */
class AudioManager
{
public:
	/**
	 * ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(AudioManager);


	/**
	 * AudioManager�� �̱� �ν��Ͻ��� ����ϴ�.
	 * 
	 * @return AudioManager�� �ν��Ͻ��� ����ϴ�.
	 */
	static AudioManager& Get()
	{
		static AudioManager Instance;
		return Instance;
	}


	/**
	 * AudioManager ���� ����ϴ� miniaudio�� ���� �����͸� ����ϴ�.
	 * 
	 * @return miniaudio�� �����͸� ��ȯ�մϴ�.
	 */
	ma_engine* GetMiniaudioEngine();


private:
	/**
	 * AudioManager�� �������Դϴ�.
	 */
	AudioManager();


	/**
	 * AudioManager�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~AudioManager();
};