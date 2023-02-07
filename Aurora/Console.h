#ifndef __AURORA_CONSOLE_H__
#define __AURORA_CONSOLE_H__

#include "Definitions.h"
#include "Interfaces.h"
#include "String.h"
#include "Exceptions.h"
#include "Color.h"

#include <Windows.h>

namespace Aurora {
	class Console : public IDisposable {
	public:
		Console();
	};

	/// <summary>
	/// <para>Sets the foreground color of the console. This function only works with applications ran in a TrueColor enabled terminal.</para>
	/// <para>For example: Windows Terminal is TrueColor enabled, whereas the Legacy Windows Command Prompt is not.</para>
	/// </summary>
	/// <param name="TrueColor">- The color to set the foreground to, in RGB.</param>
	A_VOID SetConsoleForegroundColor(_In_ const RGB& TrueColor);
	A_VOID ResetConsoleForegroundColor();

	A_VOID SetConsoleBackgroundColor(_In_ const RGB& TrueColor);
	A_VOID ResetConsoleBackgroundColor();

	A_VOID SetConsoleColorLegacy(_In_ A_WORD wColor);
}

#endif // !__AURORA_CONSOLE_H__