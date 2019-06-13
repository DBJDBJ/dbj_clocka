#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <mmsystem.h>

#include <crtdbg.h>

namespace dbj {
	class brush final {
		mutable HBRUSH brush_{};
		brush() = delete;
	public:
		explicit brush(COLORREF color_)
			: brush_(CreateSolidBrush(color_))
		{}
		~brush() { DeleteObject(brush_); }
		operator HBRUSH& () const noexcept { return brush_; }
	};

	class font final {
		mutable HFONT font_{};
		font() = delete;
		font(LOGFONT& logfont) : font_(CreateFontIndirect(&logfont)) {}
	public:
		~font() { DeleteObject(font_); }
		operator HFONT& () const noexcept { return font_; }

		static font from_logfont(
			char* const font_name,
			unsigned font_height,
			unsigned font_pitch_and_familly /* = FIXED_PITCH */
		) {
			LOGFONT logfont{};
			strcpy_s(logfont.lfFaceName, font_name);
			logfont.lfHeight = font_height;
			logfont.lfPitchAndFamily = font_pitch_and_familly;
			return dbj::font(logfont);
		}
	};

	class pen final 
	{
		mutable HPEN pen_{};
		pen() = delete;
	public:
		// COLORREF x = RGB(1,2,3)
		// pen p(PS_SOLID, 2, RGB(220, 20, 60));
		pen(int style_, unsigned width_, COLORREF color_)
			: pen_(CreatePen(style_, width_, color_))
		{
		}
		~pen() { DeleteObject(pen_); }
		operator HPEN& () const noexcept { return pen_; }
	};

	class sound final {
	public:
		// system sounds
		static auto sys_sound( unsigned long snd_alias_id_ ) { 
			return ::PlaySound( (LPCTSTR)snd_alias_id_, NULL, SND_ALIAS_ID|SND_NODEFAULT );
		}

		static auto sys_asterisk()		{ return sys_sound(SND_ALIAS_SYSTEMASTERISK);	}
		static auto sys_question()		{ return sys_sound(SND_ALIAS_SYSTEMQUESTION);	}
		static auto sys_hand()			{ return sys_sound(SND_ALIAS_SYSTEMHAND);		}
		static auto sys_exit()			{ return sys_sound(SND_ALIAS_SYSTEMEXIT);		}
		static auto sys_start()			{ return sys_sound(SND_ALIAS_SYSTEMSTART);		}
		static auto sys_welcome()		{ return sys_sound(SND_ALIAS_SYSTEMWELCOME);	}
		static auto sys_exclamation()	{ return sys_sound(SND_ALIAS_SYSTEMEXCLAMATION);}
		static auto sys_default()		{ return sys_sound(SND_ALIAS_SYSTEMDEFAULT);	}
	};

#ifdef _DEBUG
	namespace test {
		inline auto sound() {

			_ASSERTE(
				::PlaySound(TEXT("SystemStart"), NULL, SND_ALIAS)
				);

			_ASSERTE(sound::sys_asterisk());
			_ASSERTE(sound::sys_exclamation());
			_ASSERTE(sound::sys_exit());
			_ASSERTE(sound::sys_hand());
			_ASSERTE(sound::sys_question());
			_ASSERTE(sound::sys_start());
			_ASSERTE(sound::sys_welcome());
			_ASSERTE(sound::sys_default());
		}
	} // test ns
#endif
} // dbj
