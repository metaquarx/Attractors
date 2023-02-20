// SPDX-FileCopyrightText: 2023 metaquarx <metaquarx@protonmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include "Lorenz.hpp"

Lorenz::Lorenz()
: history(sf::PrimitiveType::LineStrip)
, speed_multiplier(1.)
, reng(std::random_device{}())
, rdist(-1, 1) {
	reset();
}

void Lorenz::reset() {
	location = {rdist(reng), rdist(reng), rdist(reng)};
	history.clear();
	accumulator = 0.f;
}

void Lorenz::speed_up() {
	speed_multiplier += .1;
}

void Lorenz::slow_down() {
	speed_multiplier -= .1;
}

void Lorenz::step(float dt) {
	accumulator += dt * speed_multiplier;

	float default_rate = 1./120.;
	while (accumulator > default_rate) {
		accumulator -= default_rate;

		double b = 8./3.;
		double s = 10.;
		double r = 30.;

		Vector3d newpos;
		newpos.x = s * (location.y - location.x);
		newpos.y = location.x * (r - location.z) - location.y;
		newpos.z = location.x * location.y - b * location.z;

		location.x += newpos.x * default_rate;
		location.y += newpos.y * default_rate;
		location.z += newpos.z * default_rate;

		history.append({sf::Vector2f(location.x, -location.z), sf::Color::Red});
	}
}

void Lorenz::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();

	sf::CircleShape point;
	point.setRadius(.5f);
	point.setOrigin(.25f, .25f);
	point.setFillColor(sf::Color::White);
	point.setPosition(location.x, -location.z);

	target.draw(history, states);
	target.draw(point, states);
}
