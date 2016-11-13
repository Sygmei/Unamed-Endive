#ifndef DEF_CHARACTER
#define DEF_CHARACTER

#include <string>
#include <vector>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>

#include "../constants.hpp"
#include "../abstract/point.hpp"
#include "../map/map.hpp"
#include "../abstract/texturesmanager.hpp"
#include "../bag/bag.hpp"
#include "../abstract/functions.hpp"

enum class MvState {
    idle,
    walking,
    idle2,
    walking2
};

enum class ChState {
    idle,
    walking,
    running
};

enum class Sex {
    Female,
    Male
};

class Character {
private:
    // variables
    std::string name;
    Point pos;
    float speed;
    DIR direction;
    TexturesManager textures;
    std::vector<sf::Sprite> sprites;
    ChState state;
    MvState anim_cursor;
    std::string sex;
    std::string path;
    Bag bag;
    sf::Time elapsed_mvt_time;
    sf::Time not_moving_time;
    // methods
    void update_anim(sf::Time);
    void update_walk_anim();
    void update_run_anim();
    void load_character_textures();

public:
    sf::RectangleShape rectangle {sf::Vector2f(16.0f, 16.0f)};
    // methods
    Character(Sex sex_=Sex::Male);
    int move(DIR, Map, sf::Time);
    int save();
    sf::Sprite& getCurrentSprite();
    void update(sf::RenderWindow&, sf::Time);
    void setName(const std::string);
    bool load();
    Bag* getBag();
};

#endif // DEF_CHARACTER
