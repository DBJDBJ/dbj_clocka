#pragma once

#include <Windows.h>

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
			unsigned font_pitch_and_familly = FIXED_PITCH
		) {
			LOGFONT logfont{};
			strcpy_s(logfont.lfFaceName, font_name);
			logfont.lfHeight = font_height;
			logfont.lfPitchAndFamily = font_pitch_and_familly;
			return dbj::font(logfont);
		}
	};

	class pen final {
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


} // dbj
