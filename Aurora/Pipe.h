#ifndef __AURORA_PIPE_H__
#define __AURORA_PIPE_H__

#include "Definitions.h"

#include <Windows.h>

namespace Aurora {
	enum class PipeOpenMode {
		Inbound = PIPE_ACCESS_INBOUND,
		Outbound = PIPE_ACCESS_OUTBOUND,
		Duplex = PIPE_ACCESS_DUPLEX
	};

	class NamedPipeServer {
	public:
		NamedPipeServer();
	};

	class NamedPipeClient {

	};

	class AnonymousPipe {

	};
}

#endif // !__AURORA_PIPE_H__