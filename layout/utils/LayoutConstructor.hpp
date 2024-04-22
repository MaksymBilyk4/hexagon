#include <SFML/Graphics.hpp>
#include "../components/Modal.hpp"
#include "../components/Button.hpp"

struct LayoutConstructor {

    static auto makeMainModal(sf::RenderWindow &window) -> Modal;

    static auto makeStartGameButton(sf::RenderWindow &window) -> Button;

};