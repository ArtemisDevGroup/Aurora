#ifndef __AURORA_CONSOLE_H__
#define __AURORA_CONSOLE_H__

#include "Definitions.h"
#include "Interfaces.h"
#include "Exceptions.h"
#include "Color.h"

namespace Aurora {
	/// <summary>
	/// Represents a standard data stream.
	/// </summary>
	enum class StandardStream {
		Out,	// The stdout stream.
		In		// The stdin stream.
	};

	/// <summary>
	/// A set of constants representing a color from the 16-color console standard.
	/// </summary>
	enum class ConsoleColorLegacy : A_WORD {
		Black = 0x0000,

		DarkRed = 0x0004,
		DarkGreen = 0x0002,
		DarkBlue = 0x0001,
		DarkGray = 0x0008,

		DarkCyan = DarkBlue | DarkGreen,
		DarkMagenta = DarkRed | DarkBlue,
		DarkYellow = DarkRed | DarkGreen,

		Gray = DarkRed | DarkGreen | DarkBlue,
		Red = DarkRed | DarkGray,
		Green = DarkGreen | DarkGray,
		Blue = DarkBlue | DarkGray,

		Cyan = DarkCyan | DarkGray,
		Magenta = DarkMagenta | DarkGray,
		Yellow = DarkYellow | DarkGray,
		White = DarkRed | DarkGreen | DarkBlue | DarkGray
	};

	/// <summary>
	/// A set of flags representing a color from the 16-color console standard.
	/// </summary>
	struct ConsoleColorLegacyFlags : EnumFlags<ConsoleColorLegacy, A_WORD> {
		using EnumFlags::EnumFlags;
		using enum ConsoleColorLegacy;

		/// <summary>
		/// Gets a WORD representation of the color assigned to this instance to pass to SetConsoleTextAttribute to set the foreground.
		/// </summary>
		/// <returns>A WORD representing the foreground color.</returns>
		constexpr A_WORD GetForegroundLiteral() const noexcept { return nValue; }

		/// <summary>
		/// Gets a WORD representation of the color assigned to this instace to pass to SetConsoleTextAttribute to set the background.
		/// </summary>
		/// <returns>A WORD representing the background color.</returns>
		constexpr A_WORD GetBackgroundLiteral() const noexcept { return nValue << 4; }
	};

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