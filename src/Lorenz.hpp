// SPDX-FileCopyrightText: 2023 metaquarx <metaquarx@protonmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include <SFML/Graphics.hpp>

#include <random>

using Vector3d = sf::Vector3<double>;

class Lorenz : public sf::Drawable, public sf::Transformable {
public:
	Lorenz();

	void reset();
	void speed_up();
	void slow_down();

	float speed_multiplier;
	float accumulator;
	void step(float dt);

	std::default_random_engine reng;
	std::uniform_real_distribution<double> rdist;

	Vector3d location;
	sf::VertexArray history;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
