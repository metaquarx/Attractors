// SPDX-FileCopyrightText: 2023 metaquarx <metaquarx@protonmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include "Lorenz.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
	sf::RenderWindow window({800, 800}, "Lorenz attractor", sf::Style::Titlebar | sf::Style::Close, sf::ContextSettings{0, 0, 8});
	window.setVerticalSyncEnabled(true);

	sf::View view;
	view.reset(sf::FloatRect{0, 0, 70, 70});
	window.setView(view);

	Lorenz attractor;
	attractor.setPosition(35, 65);

	sf::Clock clock;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			} else if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::R) {
					attractor.reset();
				} else if (event.key.code == sf::Keyboard::Up) {
					attractor.speed_up();
					std::cout << "Set simulation speed to " << attractor.speed_multiplier << std::endl;
				} else if (event.key.code == sf::Keyboard::Down) {
					attractor.slow_down();
					std::cout << "Set simulation speed to " << attractor.speed_multiplier << std::endl;
				}
			}
		}

		attractor.step(clock.restart().asSeconds());

		window.clear({30, 30, 30});
		window.draw(attractor);
		window.display();
	}
}
