#include <SFML/Graphics.hpp>
#include "QuickSort.h"
#include <future>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1200, 800), "Quick Sort Visualization SFML", sf::Style::Close);

	QuickSort* qSort = new QuickSort(1200, 800);

	auto future = std::async(&QuickSort::sortArray, qSort ,&qSort->arr, 0, (int)qSort->arr.size() - 1);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Resized)
				qSort->setViewSize(event.size.width, event.size.height);
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Black);

		qSort->generateVisualSort(&window);

		window.display();
	}

	return 0;
}