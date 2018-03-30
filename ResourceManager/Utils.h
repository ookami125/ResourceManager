#pragma once
#include <stdint.h>

namespace Utils
{
#ifdef X64
	static inline bool is_ptr_aligned(const void *ptr) {
		uintptr_t p = (uintptr_t)ptr;
		return (p & 0x7) == 0;
	}
#elif defined X32
	static inline bool is_ptr_aligned(const void *ptr) {
		uintptr_t p = (uintptr_t)ptr;
		return (p & 0x3) == 0;
	}
#endif

	static uint64_t hash(const char* str)
	{
		uint64_t hash = 5381;

		if (!is_ptr_aligned(str)) {
			if (*str == '\0') return hash; else hash = ((hash << 5) + hash) + *str;
			str++;
		}
		if (!is_ptr_aligned(str)) {
			if (*str == '\0') return hash; else hash = ((hash << 5) + hash) + *str;
			str++;
		}
		if (!is_ptr_aligned(str)) {
			if (*str == '\0') return hash; else hash = ((hash << 5) + hash) + *str;
			str++;
		}
#ifdef X64
		if (!is_ptr_aligned(str)) {
			if (*str == '\0') return hash; else hash = ((hash << 5) + hash) + *str;
			str++;
		}
		if (!is_ptr_aligned(str)) {
			if (*str == '\0') return hash; else hash = ((hash << 5) + hash) + *str;
			str++;
		}
		if (!is_ptr_aligned(str)) {
			if (*str == '\0') return hash; else hash = ((hash << 5) + hash) + *str;
			str++;
		}
		if (!is_ptr_aligned(str)) {
			if (*str == '\0') return hash; else hash = ((hash << 5) + hash) + *str;
			str++;
		}
#endif
		while (true)
		{
			uint32_t v = *(uint32_t *)str;
			if (((v >>  0) & 0xff) == '\0') return hash; else hash = ((hash << 5) + hash) + ((v >>  0) & 0xff);
			if (((v >>  8) & 0xff) == '\0') return hash; else hash = ((hash << 5) + hash) + ((v >>  8) & 0xff);
			if (((v >> 16) & 0xff) == '\0') return hash; else hash = ((hash << 5) + hash) + ((v >> 16) & 0xff);
			if (((v >> 24) & 0xff) == '\0') return hash; else hash = ((hash << 5) + hash) + ((v >> 24) & 0xff);
			str += 4;
		}
	}

	uint64_t old_hash(const char *str)
	{
		uint64_t hash = 5381;
		int c;

		while (c = *str++)
			hash = ((hash << 5) + hash) + c;

		return hash;
	}
}

namespace std {

	template <>
	struct hash<const char*>
	{
		std::size_t operator()(const char*& k) const
		{
			return Utils::hash(k);
		}
	};

}