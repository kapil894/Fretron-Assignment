#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

// Define a FlightPath type
typedef std::vector<sf::Vector2f> FlightPath;

// Function to draw the flight paths
void drawFlightPaths(sf::RenderWindow& window, const std::vector<FlightPath>& flightPaths) {
    sf::Color colors[] = {sf::Color::Red, sf::Color::Green, sf::Color::Blue};

    for (size_t i = 0; i < flightPaths.size(); ++i) {
        sf::VertexArray lines(sf::LinesStrip, flightPaths[i].size());
        for (size_t j = 0; j < flightPaths[i].size(); ++j) {
            lines[j].position = flightPaths[i][j];
            lines[j].color = colors[i % 3];
        }
        window.draw(lines);
    }
}

int main() {
    // Define flight paths
    FlightPath flight1 = { {100, 100}, {200, 200}, {300, 300} };
    FlightPath flight2 = { {100, 100}, {200, 400}, {300, 200} };
    FlightPath flight3 = { {100, 100}, {400, 200}, {300, 400} };

    std::vector<FlightPath> flightPaths = { flight1, flight2, flight3 };

    // Create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Flight Paths");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        drawFlightPaths(window, flightPaths);
        window.display();
    }

    return 0;
}
