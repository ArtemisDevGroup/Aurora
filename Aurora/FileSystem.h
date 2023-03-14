#ifndef __AURORA_FILE_SYSTEM_H__
#define __AURORA_FILE_SYSTEM_H__

#include "Definitions.h"

namespace Aurora {
	enum class CreationDisposition {
		CreateNew = 1,
		CreateAlways = 2,
		OpenExisting = 3,
		OpenAlways = 4,
		TruncateExisting = 5
	};

	class AURORA_API File {

	};

	class AURORA_API TextFile : public File {

	};
}

#endif // !__AURORA_FILE_SYSTEM_H__