#ifndef DEF_SETTINGS_VIEW
#define DEF_SETTINGS_VIEW

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

#include "view.hpp"
#include "../abstract/container.hpp"
#include "../json/json.h"
#include "../abstract/functions.hpp"

class SettingsView : public View
{
private:
    Json::Value root;
    Container<sf::Texture> textures;
    Container<sf::Text> texts;
    std::map<std::string, sf::Sprite> sprites;
    sf::Font font;

    const std::string BCKG = "background";
    const std::string CHECKED = "checked";
    const std::string UNCHECKED = "unchecked";
    const std::string MUSIC = "musique";
    const std::string AA = "aa";
    const std::string VS = "vs";
    const std::string SHADER = "shader";
    const std::string FPS = "fps";
    const std::string CTRL = "controles";
    const std::string MENU = "menu";
    const std::string UP = "up";
    const std::string DW = "dwn";
    const std::string RI = "right";
    const std::string LE = "left";
    const std::string VMU = "valuemusique";
    const std::string VAA = "valueaa";
    const std::string VVS = "valuevsync";
    const std::string VSHADER = "valueshader";
    const std::string VFPS = "valuefps";
    const std::string VMENU = "valuemenu";
    const std::string VUP = "valueup";
    const std::string VDW = "valuedw";
    const std::string VRI = "valueright";
    const std::string VLE = "valueleft";

    void update_texts();

public:
    SettingsView();
    bool load() override;
    void render(sf::RenderWindow&) override;
    int process_event(sf::Event&, sf::Time) override;
    void update(sf::RenderWindow&, sf::Time) override;
};

#endif // DEF_SETTINGS_VIEW