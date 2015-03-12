#include <cstdint>

namespace variadic {
	template <typename... T> uint32_t countArguments(T... t1) {
		return sizeof...(T);
	}
};
