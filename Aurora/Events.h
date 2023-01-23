#ifndef __AURORA_EVENTS_H__
#define __AURORA_EVENTS_H__

#include "Definitions.h"

namespace Aurora {
	template<class InstanceEventArgs>
	class AURORA_API Event {
	public:
		typedef void(__cdecl* InstanceEventHandler)(_In_opt_ void* pSender, _In_opt_ const InstanceEventArgs* pArgs);

	private:
		InstanceEventHandler lpszfnEventHandlers[MAX_INVOKE];

	public:
		constexpr Event() {
			for (int i = 0; i < MAX_INVOKE; i++) lpszfnEventHandlers[i] = nullptr;
		}

		constexpr void Invoke(_In_opt_ void* pSender, _In_opt_ const InstanceEventArgs* pArgs) const {
			for (int i = 0; i < MAX_INVOKE; i++)
				if (lpszfnEventHandlers[i])
					lpszfnEventHandlers[i](pSender, pArgs);
		}

		constexpr void operator+=(_In_ InstanceEventHandler lpfnEventHandler) {
			for (int i = 0; i < MAX_INVOKE; i++)
				if (!lpszfnEventHandlers[i])
					lpszfnEventHandlers[i] = lpfnEventHandler;
		}

		constexpr void operator-=(_In_ InstanceEventHandler lpfnEventHandler) {
			for (int i = 0; i < MAX_INVOKE; i++)
				if (lpszfnEventHandlers[i] == lpfnEventHandler)
					lpszfnEventHandlers[i] = nullptr;
		}
	};
}

#endif // !__AURORA_EVENTS_H__