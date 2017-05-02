#pragma once

#include <exception>
#include <vector>

template <typename T>
bool IsBetween(const T& value, const T& lowerBound, const T& upperBound)
{
	return (value >= lowerBound) && (value <= upperBound);
}

void CheckIndex(size_t index, size_t max);

template<typename T>
inline void DeleteLastElement(std::vector<T>& vector)
{
	if (vector.size() == 0)
	{
		throw std::runtime_error("Index out range");
	}
	vector.erase(vector.begin() + vector.size() - 1);
}

