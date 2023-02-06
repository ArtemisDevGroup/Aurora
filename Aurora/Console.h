#ifndef __AURORA_CONSOLE_H__
#define __AURORA_CONSOLE_H__

#include "Definitions.h"
#include "Interfaces.h"
#include "String.h"
#include "Exceptions.h"

#include <Windows.h>

namespace Aurora {
	class Console : public IDisposable {
	public:
		Console();
	};
}

#endif // !__AURORA_CONSOLE_H__