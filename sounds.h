#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

namespace sound {
	// where the sounds should be and how they should be called
	static const char* WAVE_TTI = "SoundFiles//TheTimeIs.wav";
	static const char* WAVE_1 = "SoundFiles//1.wav";
	static const char* WAVE_2 = "SoundFiles//2.wav";
	static const char* WAVE_3 = "SoundFiles//3.wav";
	static const char* WAVE_4 = "SoundFiles//4.wav";
	static const char* WAVE_5 = "SoundFiles//5.wav";
	static const char* WAVE_6 = "SoundFiles//6.wav";
	static const char* WAVE_7 = "SoundFiles//7.wav";
	static const char* WAVE_8 = "SoundFiles//8.wav";
	static const char* WAVE_9 = "SoundFiles//9.wav";
	static const char* WAVE_10 = "SoundFiles//10.wav";
	static const char* WAVE_11 = "SoundFiles//11.wav";
	static const char* WAVE_12 = "SoundFiles//12.wav";
	static const char* WAVE_13 = "SoundFiles//13.wav";
	static const char* WAVE_14 = "SoundFiles//14.wav";
	static const char* WAVE_15 = "SoundFiles//15.wav";
	static const char* WAVE_16 = "SoundFiles//16.wav";
	static const char* WAVE_17 = "SoundFiles//17.wav";
	static const char* WAVE_18 = "SoundFiles//18.wav";
	static const char* WAVE_19 = "SoundFiles//19.wav";
	static const char* WAVE_20 = "SoundFiles//20.wav";
	static const char* WAVE_30 = "SoundFiles//30.wav";
	static const char* WAVE_40 = "SoundFiles//40.wav";
	static const char* WAVE_50 = "SoundFiles//50.wav";
	static const char* WAVE_AM = "SoundFiles//AM.wav";
	static const char* WAVE_PM = "SoundFiles//PM.wav";
	static const char* WAVE_ALARM = "SoundFiles//AlarmTone.wav";
	static const char* WAVE_PERHOUR = "SoundFiles//PerHour.wav";

} // sounds ns

static auto ASSURE_SOUND = [](auto ideal_path, HINSTANCE hinstance_)
{

	return PlaySound(ideal_path, hinstance_, SND_NODEFAULT | SND_SYNC);
};