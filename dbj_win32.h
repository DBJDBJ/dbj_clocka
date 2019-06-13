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
		static auto sys_sound( unsigned long snd_alias_id_ , HINSTANCE hinstance_) {
			return ::PlaySound( (LPCTSTR)snd_alias_id_, hinstance_, SND_ALIAS_ID|SND_NODEFAULT );
		}

		static auto sys_asterisk(HINSTANCE hinstance_)		{ return sys_sound(SND_ALIAS_SYSTEMASTERISK, hinstance_ );	}
		static auto sys_question(HINSTANCE hinstance_)		{ return sys_sound(SND_ALIAS_SYSTEMQUESTION, hinstance_);	}
		static auto sys_hand(HINSTANCE hinstance_)			{ return sys_sound(SND_ALIAS_SYSTEMHAND, hinstance_);		}
		static auto sys_exit(HINSTANCE hinstance_)			{ return sys_sound(SND_ALIAS_SYSTEMEXIT, hinstance_);		}
		static auto sys_start(HINSTANCE hinstance_)			{ return sys_sound(SND_ALIAS_SYSTEMSTART, hinstance_);		}
		static auto sys_welcome(HINSTANCE hinstance_)		{ return sys_sound(SND_ALIAS_SYSTEMWELCOME, hinstance_);	}
		static auto sys_exclamation(HINSTANCE hinstance_)	{ return sys_sound(SND_ALIAS_SYSTEMEXCLAMATION, hinstance_);}
		static auto sys_default(HINSTANCE hinstance_)		{ return sys_sound(SND_ALIAS_SYSTEMDEFAULT, hinstance_);	}
	};

#ifdef _DEBUG
	namespace test {
		inline auto sound(HINSTANCE hinstance_) {

			_ASSERTE(
				::PlaySound(TEXT("SystemStart"), hinstance_, SND_ALIAS)
				);

			_ASSERTE(sound::sys_asterisk(hinstance_));
			_ASSERTE(sound::sys_exclamation(hinstance_));
			_ASSERTE(sound::sys_exit(hinstance_));
			_ASSERTE(sound::sys_hand(hinstance_));
			_ASSERTE(sound::sys_question(hinstance_));
			_ASSERTE(sound::sys_start(hinstance_));
			_ASSERTE(sound::sys_welcome(hinstance_));
			_ASSERTE(sound::sys_default(hinstance_));
		}
	} // test ns
#endif
} // dbj
