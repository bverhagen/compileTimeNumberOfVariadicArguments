#include <cstdlib>

namespace variadic {
	template <typename... T> 
	constexpr size_t countArguments(const T&... t1) {
		return sizeof...(T);
	}
};
