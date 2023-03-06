#ifndef __AURORA_EVENTS_H__
#define __AURORA_EVENTS_H__

#include "Definitions.h"

namespace Aurora {
	template<class InstanceEventArgs = void>
	class AURORA_API Event {
	public:
		typedef A_VOID(__cdecl* InstanceEventHandler)(_In_opt_ A_LPVOID lpSender, _In_opt_ const InstanceEventArgs* pArgs);

	private:
		InstanceEventHandler lpszfnEventHandlers[MAX_INVOKE];

	public:
		constexpr Event() noexcept {
			for (A_I32 i = 0; i < MAX_INVOKE; i++) lpszfnEventHandlers[i] = nullptr;
		}

		constexpr A_VOID Invoke(_In_opt_ A_LPVOID lpSender, _In_opt_ const InstanceEventArgs* pArgs) const {
			for (A_I32 i = 0; i < MAX_INVOKE; i++)
				if (lpszfnEventHandlers[i])
					lpszfnEventHandlers[i](lpSender, pArgs);
		}

		constexpr A_VOID Clear() noexcept {
			for (A_I32 i = 0; i < MAX_INVOKE; i++) lpszfnEventHandlers[i] = nullptr;
		}

		constexpr A_VOID operator+=(_In_ InstanceEventHandler lpfnEventHandler) noexcept {
			for (A_I32 i = 0; i < MAX_INVOKE; i++)
				if (!lpszfnEventHandlers[i])
					lpszfnEventHandlers[i] = lpfnEventHandler;
		}

		constexpr A_VOID operator-=(_In_ InstanceEventHandler lpfnEventHandler) noexcept {
			for (A_I32 i = 0; i < MAX_INVOKE; i++)
				if (lpszfnEventHandlers[i] == lpfnEventHandler)
					lpszfnEventHandlers[i] = nullptr;
		}
	};

	template<>
	class AURORA_API Event<void> {
	public:
		typedef A_VOID(__cdecl* InstanceEventHandler)(_In_opt_ A_LPVOID lpSender);

	private:
		InstanceEventHandler lpszfnEventHandlers[MAX_INVOKE];

	public:
		constexpr Event() noexcept {
			for (A_I32 i = 0; i < MAX_INVOKE; i++) lpszfnEventHandlers[i] = nullptr;
		}

		constexpr A_VOID Invoke(_In_opt_ A_LPVOID lpSender) const {
			for (A_I32 i = 0; i < MAX_INVOKE; i++)
				if (lpszfnEventHandlers[i])
					lpszfnEventHandlers[i](lpSender);
		}

		constexpr A_VOID Clear() noexcept {
			for (A_I32 i = 0; i < MAX_INVOKE; i++) lpszfnEventHandlers[i] = nullptr;
		}

		constexpr A_VOID operator+=(_In_ InstanceEventHandler lpfnEventHandler) noexcept {
			for (A_I32 i = 0; i < MAX_INVOKE; i++)
				if (!lpszfnEventHandlers[i])
					lpszfnEventHandlers[i] = lpfnEventHandler;
		}

		constexpr A_VOID operator-=(_In_ InstanceEventHandler lpfnEventHandler) noexcept {
			for (A_I32 i = 0; i < MAX_INVOKE; i++)
				if (lpszfnEventHandlers[i] == lpfnEventHandler)
					lpszfnEventHandlers[i] = nullptr;
		}
	};
}

#endif // !__AURORA_EVENTS_H__