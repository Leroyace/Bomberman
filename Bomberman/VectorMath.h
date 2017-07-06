#pragma once

#include <SFML/System/Vector2.hpp>

namespace vm
{
	//Get the magnitude of a vector

	template <class T>
	float inline magnitude(const sf::Vector2<T> &vec)
	{
		return std::sqrtf(vec.x * vec.x + vec.y * vec.y);
	};

	template <class T>
	sf::Vector2<T> inline setAngle(const sf::Vector2<T> &vec, float angle)
	{
		float mag = magnitude(vec);

		sf::Vector2f vector;

		vector.x = std::cos(angle) * mag;
		vector.y = std::sin(angle) * mag;
		return vector;
	};

	template <class T>
	float inline getAngle(const sf::Vector2<T> &vec)
	{
		return std::atan2f(vec.y,vec.x);
	};

	template <class T>
	sf::Vector2<T> setMagnitude(const sf::Vector2<T> &vec, float magnitude)
	{
		float angle = getAngle(vec);

		sf::Vector2f vector;

		vector.x = std::cos(angle) * magnitude;
		vector.y = std::sin(angle) * magnitude;

		return vector;
	};

	template <class T>
	sf::Vector2<T> normalize(const sf::Vector2<T> &vec)
	{
		float m = magnitude(vec);

		return vec / m;
	};
}