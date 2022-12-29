#include <AudioManager.h>

#include <miniaudio/miniaudio.h>

ma_engine MiniaudioEngine;

ma_engine* AudioManager::GetMiniaudioEngine()
{
	return &MiniaudioEngine;
}

AudioManager::AudioManager()
{
	CHECK((ma_engine_init(nullptr, &MiniaudioEngine) == MA_SUCCESS), "failed to initialize miniaudio engine");
}

AudioManager::~AudioManager()
{
	ma_engine_uninit(&MiniaudioEngine);
}
