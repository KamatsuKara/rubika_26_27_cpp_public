#pragma once

namespace Tags {
	enum Tag
	{
		None = 0,
		Static = 1,
		Dynamic = 2,
		Neutral = 4,
		Enemy = 8,
		Player = 16
	};
}

inline Tags::Tag operator|(const Tags::Tag& a, const Tags::Tag& b)
{
	return static_cast<Tags::Tag>(static_cast<int>(a) | static_cast<int>(b));
}

inline Tags::Tag operator&(const Tags::Tag& a, const Tags::Tag& b)
{
	return static_cast<Tags::Tag>(static_cast<int>(a) & static_cast<int>(b));
}

inline Tags::Tag operator^(const Tags::Tag& a, const Tags::Tag& b)
{
	return static_cast<Tags::Tag>(static_cast<int>(a) ^ static_cast<int>(b));
}

inline Tags::Tag operator~(const Tags::Tag& a)
{
	return static_cast<Tags::Tag>(~static_cast<int>(a));
}


inline Tags::Tag operator|=(const Tags::Tag& a, const Tags::Tag& b)
{
	return static_cast<Tags::Tag>(static_cast<int>(a) | static_cast<int>(b));
}

inline Tags::Tag operator&=(const Tags::Tag& a, const Tags::Tag& b)
{
	return static_cast<Tags::Tag>(static_cast<int>(a) & static_cast<int>(b));
}

inline Tags::Tag operator^=(const Tags::Tag& a, const Tags::Tag& b)
{
	return static_cast<Tags::Tag>(static_cast<int>(a) ^ static_cast<int>(b));
}