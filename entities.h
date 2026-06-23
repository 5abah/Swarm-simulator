//
// Created by CsDaBest on 4/26/2026.
//

#ifndef SWARMSIMULATION_ENTITIES_H
#define SWARMSIMULATION_ENTITIES_H
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Shape.hpp"

class Germ
{
	public:
	std::vector<sf::RectangleShape> germs;
		void spawnGerm(sf::Vector2f position, sf::Vector2f size)
		{
			sf::RectangleShape germShape;
			germShape.setFillColor(color);
			germShape.setPosition(position);
			germShape.setSize(size);
			germs.push_back(germShape);

		}
		void drawAll(sf::RenderWindow& renderWindow)
		{
			for (auto& curGerm : germs)
				renderWindow.draw(curGerm);
		}
		void clearAll()
		{
			germs.clear();
		}

	private:
		sf::Color color = sf::Color::Green;


};

#endif //SWARMSIMULATION_ENTITIES_H