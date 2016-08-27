#include <SFML/Graphics.hpp>

#include "default.hpp"
#include "../constants.hpp"

// public
DefaultView::DefaultView() : View(DEFAULT_VIEW_ID), particles(1000), mymap("tests.json")
{
    mymap.load();

    this->triangle = sf::VertexArray(sf::Triangles, 3);

    this->triangle[0].position = sf::Vector2f(200, 200);
    this->triangle[1].position = sf::Vector2f(300, 200);
    this->triangle[2].position = sf::Vector2f(300, 300);

    this->triangle[0].color = sf::Color::Red;
    this->triangle[1].color = sf::Color::Blue;
    this->triangle[2].color = sf::Color::Green;
}

void DefaultView::render(sf::RenderWindow& window)
{
    this->mymap.render(window);
    window.draw(this->triangle);
    window.draw(this->particles);
}

void DefaultView::update(sf::RenderWindow& window, sf::Time elapsed)
{
    sf::Vector2i mouse = sf::Mouse::getPosition(window);
    this->particles.setEmitter(window.mapPixelToCoords(mouse));
    particles.update(elapsed);
}

int DefaultView::process_event(sf::Event& event)
{
    switch(event.type)
    {
    case sf::Event::KeyPressed:
        switch(event.key.code)
        {
        default:
            break;
        }
        break;

    default:
        break;
    }

    return -1;
}