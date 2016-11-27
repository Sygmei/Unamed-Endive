#include <iostream>

#include "animatedentity.hpp"

void AnimatedEntity::update_anim(sf::Time elapsed)
{
    this->elapsed_mvt_time += elapsed;

    if (this->elapsed_mvt_time.asMilliseconds() % 24 < 3)
    {
        if (this->state == ChState::walking)
            this->update_walk_anim();
        else if (this->state == ChState::running)
            this->update_run_anim();
    }

    // reset timer to prevent an overflow
    if (this->elapsed_mvt_time.asSeconds() > 3600.0f)
        this->elapsed_mvt_time = sf::seconds((this->elapsed_mvt_time % sf::seconds(3600.0f)).asSeconds());
}

void AnimatedEntity::update_walk_anim()
{
    if (this->anim_cursor == MvState::idle)
    {
        this->anim_cursor = MvState::walking;
        goto stop;
    }
    else if (this->anim_cursor == MvState::walking)
    {
        this->anim_cursor = MvState::idle2;
        goto stop;
    }
    else if (this->anim_cursor == MvState::idle2)
    {
        this->anim_cursor = MvState::walking2;
        goto stop;
    }
    else if (this->anim_cursor == MvState::walking2)
    {
        this->anim_cursor = MvState::idle;
        goto stop;
    }

    stop:;
}

void AnimatedEntity::update_run_anim()
{
    if (this->anim_cursor == MvState::idle)
    {
        this->anim_cursor = MvState::walking;
        goto stop2;
    }
    else if (this->anim_cursor == MvState::walking)
    {
        this->anim_cursor = MvState::walking2;
        goto stop2;
    }
    else if (this->anim_cursor == MvState::walking2)
    {
        this->anim_cursor = MvState::idle;
        goto stop2;
    }

    stop2:;
}

AnimatedEntity::AnimatedEntity(int x, int y) :
    pos(x, y)
    , state(ChState::idle)
    , anim_cursor(MvState::idle)
    , direction(DIRECTION::down)
    , speed(1.0f / 32.0f)
{
}

bool AnimatedEntity::load()
{
    const std::vector<std::string> chtexfname = {"up", "down", "left", "right"};
    std::cout << "Loading AnimatedEntity " << this->path << std::endl;

    for (const auto& dir: chtexfname)
    {
        for (int i=0; i < 4; i++)
        {
            sf::Image image;

            if (!image.loadFromFile(this->path + dir + to_string<int>(i) + ".png"))
            {
                std::cout << "Unable to open " << this->path << dir << to_string<int>(i) << ".png" << std::endl;
                return false;
            }

            image.createMaskFromColor(sf::Color(255, 0, 255, 255));
            sf::Texture texture;
            texture.loadFromImage(image);

            this->textures.addTexture(this->path + dir + to_string<int>(i), texture);
            this->sprites.push_back(sf::Sprite(this->textures.getTexture(this->path + dir + to_string<int>(i))));
        }
    }
    this->_load();

    return true;
}

int AnimatedEntity::move(DIRECTION dir, Map map_, sf::Time elapsed)
{
    // update state
    if (this->state == ChState::idle)
        this->state = ChState::walking;  // default value, we will change it regarding the AnimatedEntity equipment in the future

    // set the new direction
    if (this->direction != dir)
        this->anim_cursor = MvState::idle;
        // the AnimatedEntity change his direction so we reset the anim cursor
        // to prevent some visual glitches
    this->direction = dir;

    // update anim
    this->not_moving_time = sf::seconds(0.0f);  // reset it
    this->update_anim(elapsed);

    float speed = this->speed * TILE_SIZE * 2;  // * (elapsed.asMilliseconds() / 100.0f);
    std::vector<float> vect {0, 0};
    sf::Vector2u csprite_size = (this->getCurrentSprite().getTexture())->getSize();

    if (dir == DIRECTION::up)
    {
        if (this->pos.getY() - speed >= 0.0f)
            vect[1] = -1 * speed;
    }
    else if (dir == DIRECTION::down)
    {
        if (this->pos.getY() + speed - csprite_size.y < map_.getHeight() * TILE_SIZE)
            vect[1] = 1 * speed;
    }
    else if (dir == DIRECTION::left)
    {
        if (this->pos.getX() - speed >= 0.0f)
            vect[0] = -1 * speed;
    }
    else if (dir == DIRECTION::right)
    {
        if (this->pos.getX() + speed - csprite_size.x < map_.getWidth() * TILE_SIZE)
            vect[0] = 1 * speed;
    }

    bool pass = !map_.colliding_at(vect[0] / TILE_SIZE + this->pos.getX() / TILE_SIZE, vect[1] / TILE_SIZE + this->pos.getY() / TILE_SIZE)
                        && !map_.colliding_at(vect[0] / TILE_SIZE + this->pos.getX() / TILE_SIZE + 1, vect[1] / TILE_SIZE + this->pos.getY() / TILE_SIZE)
                        && !map_.colliding_at(vect[0] / TILE_SIZE + this->pos.getX() / TILE_SIZE, vect[1] / TILE_SIZE + this->pos.getY() / TILE_SIZE + 1)
                        && !map_.colliding_at(vect[0] / TILE_SIZE + this->pos.getX() / TILE_SIZE + 1, vect[1] / TILE_SIZE + this->pos.getY() / TILE_SIZE + 1);
    if (pass)
    {
        // we can set the new position
        this->pos.move(int(vect[0]), int(vect[1]));
        return 0;
    }
    // we need to recalculate a valid position
    std::cout << "need to recalculate a valid position " << this->pos.getX() << " " << this->pos.getY() << std::endl;
    return 0;
}

sf::Sprite& AnimatedEntity::getCurrentSprite()
{
    return this->sprites[static_cast<int>(this->direction) * 4 + static_cast<int>(this->anim_cursor)];
}

void AnimatedEntity::update(sf::RenderWindow& window, sf::Time elapsed)
{
    sf::Vector2f _pos {
        float(int(this->pos.getX()))
        , float(int(this->pos.getY()))
    };

    if (this->state != ChState::idle)
        this->not_moving_time += elapsed;
    if (this->not_moving_time.asSeconds() > 1.0f)
        this->state = ChState::idle;
}

void AnimatedEntity::setDir(DIRECTION direc)
{
    this->direction = direc;
}

Point& AnimatedEntity::getPos()
{
    return this->pos;
}