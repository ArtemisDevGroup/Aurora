#ifndef __AURORA_CONSOLE_H__
#define __AURORA_CONSOLE_H__

#include "Definitions.h"
#include "Interfaces.h"
#include "String.h"
#include "Exceptions.h"
#include "Color.h"
#include "Enumerations.h"

namespace Aurora {
	/// <summary>
	/// Creates a console window if the process does not already have one open.
	/// </summary>
	/// <exception cref="WindowsApiException"/>
	A_VOID AURORA_API CreateConsole();

	/// <summary>
	/// Releases the console window. If the console window was not manually created,
	/// calling this function is unnecessary.
	/// </summary>
	/// <exception cref="WindowsApiException"/>
	A_VOID AURORA_API ReleaseConsole();

	/// <summary>
	/// Opens the specified standard stream for being used in console in or out operations.
	/// </summary>
	/// <param name="Stream">- The stream to open.</param>
	/// <exception cref="ErrnoException"/>
	/// <exception cref="ParameterInvalidException"/>
	A_VOID AURORA_API OpenStream(_In_ StandardStream Stream);	

	/// <summary>
	/// <para>Closes the specified standard stream from being used in console in or out operations.</para>
	/// <para>If the standard stream was not manually opened, this function does nothing.</para>
	/// </summary>
	/// <param name="Stream">- The stream to close.</param>
	/// <exception cref="ErrnoException"/>
	/// <exception cref="ParameterInvalidException"/>
	A_VOID AURORA_API CloseStream(_In_ StandardStream Stream);

	/// <summary>
	/// <para>Closes all opened standard streams from being used in console in or out operations.</para>
	/// <para>If the standard stream was not manually opened, this function does nothing.</para>
	/// </summary>
	/// <exception cref="ErrnoException"/>
	/// <exception cref="ParameterInvalidException"/>
	A_VOID AURORA_API CloseAllStreams();

	/// <summary>
	/// <para>Sets the foreground color of the console. This function only works with applications ran in a TrueColor enabled terminal.</para>
	/// <para>For example: Windows Terminal is TrueColor enabled, whereas the Legacy Windows Command Prompt is not.</para>
	/// </summary>
	/// <param name="TrueColor">- The color to set the foreground to, in RGB.</param>
	A_VOID AURORA_API SetConsoleForegroundColor(_In_ const RGB& TrueColor);

	/// <summary>
	/// <para>Resets the foreground color of the console. This function only works with applications ran in a TrueColor enabled terminal.</para>
	/// <para>For example: Windows Terminal is TrueColor enabled, whereas the Legacy Windows Command Prompt is not.</para>
	/// </summary>
	A_VOID AURORA_API ResetConsoleForegroundColor();

	/// <summary>
	/// <para>Sets the background color of the console. This function only works with applications ran in a TrueColor enabled terminal.</para>
	/// <para>For example: Windows Terminal is TrueColor enabled, whereas the Legacy Windows Command Prompt is not.</para>
	/// </summary>
	/// <param name="TrueColor">- The color to set the foreground to, in RGB.</param>
	A_VOID AURORA_API SetConsoleBackgroundColor(_In_ const RGB& TrueColor);

	/// <summary>
	/// <para>Resets the background color of the console. This function only works with applications ran in a TrueColor enabled terminal.</para>
	/// <para>For example: Windows Terminal is TrueColor enabled, whereas the Legacy Windows Command Prompt is not.</para>
	/// </summary>
	A_VOID AURORA_API ResetConsoleBackgroundColor();

	/// <summary>
	/// Sets the foreground color of the console. Supports all windows terminals.
	/// </summary>
	/// <param name="wColorFlags">- The colors to set.</param>
	/// <exception cref="WindowsApiException"/>
	A_VOID AURORA_API SetConsoleForegroundColorLegacy(_In_ ConsoleColorLegacyFlags wColorFlags);

	/// <summary>
	/// Sets the background color of the console. Supports all windows terminals.
	/// </summary>
	/// <param name="wColorFlags">- The colors to set.</param>
	/// <exception cref="WindowsApiException"/>
	A_VOID AURORA_API SetConsoleBackgroundColorLegacy(_In_ ConsoleColorLegacyFlags wColorFlags);
}

#endif // !__AURORA_CONSOLE_H__