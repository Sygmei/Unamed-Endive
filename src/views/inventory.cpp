#include <iostream>

#include "inventory.hpp"

#define __X event.mouseButton.x
#define __Y event.mouseButton.y

// public
InventView::InventView() :
    View(INVENTORY_VIEW_ID)
    , current(0)
{

}

bool InventView::load()
{
    // loading textures
    sf::Texture background;
    if (!background.loadFromFile("assets/gui/fd_inventaire.png"))
        return false;
    this->textures.addTexture("background", background);

    sf::Texture larrow;
    if (!larrow.loadFromFile("assets/gui/fd_bouton_previous.png"))
        return false;
    this->textures.addTexture("larrow", larrow);

    sf::Texture rarrow;
    if (!rarrow.loadFromFile("assets/gui/fd_bouton_next.png"))
        return false;
    this->textures.addTexture("rarrow", rarrow);

    sf::Texture p1;
    if (!p1.loadFromFile("assets/inventory/pockets/0.png"))
        return false;
    this->textures.addTexture("pocket1", p1);

    sf::Texture p2;
    if (!p2.loadFromFile("assets/inventory/pockets/1.png"))
        return false;
    this->textures.addTexture("pocket2", p2);

    sf::Texture p3;
    if (!p3.loadFromFile("assets/inventory/pockets/2.png"))
        return false;
    this->textures.addTexture("pocket3", p3);

    sf::Texture p4;
    if (!p4.loadFromFile("assets/inventory/pockets/3.png"))
        return false;
    this->textures.addTexture("pocket4", p4);

    sf::Texture p5;
    if (!p5.loadFromFile("assets/inventory/pockets/4.png"))
        return false;
    this->textures.addTexture("pocket5", p5);

    sf::Texture drop;
    if (!drop.loadFromFile("assets/gui/fd_bouton_jeter.png"))
        return false;
    this->textures.addTexture("btn_drop", drop);

    sf::Texture vid;
    if (!vid.loadFromFile("assets/gui/fd_bouton_vider.png"))
        return false;
    this->textures.addTexture("btn_vide", vid);

    sf::Texture use;
    if (!use.loadFromFile("assets/gui/fd_bouton_utiliser.png"))
        return false;
    this->textures.addTexture("btn_use", use);

    // setting sprites
    this->sprites[this->BCKG] = sf::Sprite(this->textures.getTexture("background"));
    this->sprites[this->LARROW] = sf::Sprite(this->textures.getTexture("larrow"));
    this->sprites[this->RARROW] = sf::Sprite(this->textures.getTexture("rarrow"));
    this->sprites[this->POCKET1] = sf::Sprite(this->textures.getTexture("pocket1"));
    this->sprites[this->POCKET2] = sf::Sprite(this->textures.getTexture("pocket2"));
    this->sprites[this->POCKET3] = sf::Sprite(this->textures.getTexture("pocket3"));
    this->sprites[this->POCKET4] = sf::Sprite(this->textures.getTexture("pocket4"));
    this->sprites[this->POCKET5] = sf::Sprite(this->textures.getTexture("pocket5"));
    this->sprites[this->DROP] = sf::Sprite(this->textures.getTexture("btn_drop"));
    this->sprites[this->VID] = sf::Sprite(this->textures.getTexture("btn_vide"));
    this->sprites[this->USE] = sf::Sprite(this->textures.getTexture("btn_use"));

    // setting pos
    this->sprites[this->BCKG].setPosition(20.0f, 20.0f);
    this->sprites[this->LARROW].setPosition(30.0f, 240.0f);
    this->sprites[this->RARROW].setPosition(180.0f, 240.0f);
    this->sprites[this->POCKET1].setPosition(30.0f, 30.0f);
    this->sprites[this->POCKET2].setPosition(30.0f, 30.0f);
    this->sprites[this->POCKET3].setPosition(30.0f, 30.0f);
    this->sprites[this->POCKET4].setPosition(30.0f, 30.0f);
    this->sprites[this->POCKET5].setPosition(30.0f, 30.0f);
    this->sprites[this->DROP].setPosition(430.0f, 30.0f);
    this->sprites[this->VID].setPosition(490.0f, 30.0f);
    this->sprites[this->USE].setPosition(550.0f, 30.0f);

    // texts
    if (!this->font.loadFromFile("assets/fonts/pkmnemn.ttf"))
        return false;
    this->text.setFont(this->font);
    this->text.setString("Inventaire");
    this->text.setCharacterSize(24);
    this->text.setColor(sf::Color::White);
    this->text.setPosition(WIN_W / 2 - this->text.getGlobalBounds().width / 2, 30.0f);

    this->current_pocket_name.setFont(this->font);
    this->current_pocket_name.setString("Pocket");
    this->current_pocket_name.setCharacterSize(24);
    this->current_pocket_name.setColor(sf::Color::White);
    this->current_pocket_name.setPosition(75.0f - this->current_pocket_name.getGlobalBounds().width / 2 + 50.0f, 240.0f);

    this->object_name.setFont(this->font);
    this->object_name.setString("object0");
    this->object_name.setCharacterSize(18);
    this->object_name.setColor(sf::Color::White);
    this->object_name.setPosition(250.0f, 40.0f);

    return true;
}

void InventView::render(sf::RenderWindow& window)
{
    window.draw(this->sprites[this->BCKG]);
    window.draw(this->text);
    window.draw(this->current_pocket_name);
    window.draw(this->sprites[this->LARROW]);
    window.draw(this->sprites[this->RARROW]);
    window.draw(this->sprites[this->DROP]);
    window.draw(this->sprites[this->VID]);
    window.draw(this->sprites[this->USE]);
    this->draw_content(window);
}

int InventView::process_event(sf::Event& event, sf::Time elapsed)
{
    int new_view = -1;

    switch(event.type)
    {
    case sf::Event::KeyPressed:
        switch(event.key.code)
        {
        case sf::Keyboard::Escape:
            new_view = LAST_VIEW_ID;
            break;

        default:
            break;
        }
        break;

    case sf::Event::MouseButtonPressed:
        switch(event.mouseButton.button)
        {
        case sf::Mouse::Button::Left:
            if (__X >= 30 && __X <= 50 && __Y >= 240 && __Y <= 260)
            {
                // previous
                this->current--;
                if (this->current < 0)
                    this->current = 4;
                this->current_pocket_name.setString(this->bag->getPocket(this->current)->getName());
            }
            else if (__X >= 180 && __X <= 200 && __Y >= 240 && __Y <= 260)
            {
                // next
                this->current++;
                if (this->current > 4)
                    this->current = 0;
                this->current_pocket_name.setString(this->bag->getPocket(this->current)->getName());
            }
            else if (__X >= 430 && __X <= 475 && __Y >= 30 && __Y <= 50)
            {
                // drop
                std::cout << "drop" << std::endl;
            }
            else if (__X >= 490 && __X <= 535 && __Y >= 30 && __Y <= 50)
            {
                // dropping all
                std::cout << "dropping all" << std::endl;
            }
            else if (__X >= 550 && __X <= 595 && __Y >= 30 && __Y <= 50)
            {
                // use
                std::cout << "use" << std::endl;
            }
            break;

        default:
            break;
        }
        break;

    default:
        break;
    }

    return new_view;
}

void InventView::update(sf::RenderWindow& window, sf::Time elapsed)
{

}

void InventView::draw_content(sf::RenderWindow& window)
{
    switch (this->current)
    {
    case 0:
        window.draw(this->sprites[this->POCKET1]);
        break;

    case 1:
        window.draw(this->sprites[this->POCKET2]);
        break;

    case 2:
        window.draw(this->sprites[this->POCKET3]);
        break;

    case 3:
        window.draw(this->sprites[this->POCKET4]);
        break;

    case 4:
        window.draw(this->sprites[this->POCKET5]);
        break;
    }

    for (int i=0; i < this->bag->getPocket(this->current)->getSize(); i++)
    {
        Object* obj = this->bag->getPocket(this->current)->getObject(i);
        this->object_name.setString(ObjectsTable::getName(obj) + " (" + to_string(obj->getQuantity()) + ")");
    }
}

void InventView::add_bag(Bag* bag)
{
    this->bag = bag;
    this->current_pocket_name.setString(this->bag->getPocket(this->current)->getName());
}
