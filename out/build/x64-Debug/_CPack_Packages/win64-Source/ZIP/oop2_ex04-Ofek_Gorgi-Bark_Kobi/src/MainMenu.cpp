#include "MainMenu.h"
#include "Controller.h"
#include "ResourceManager.h"

MainMenu::MainMenu() : m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                                "6Colors", sf::Style::Close | sf::Style::Titlebar) {
    m_font = ResourceManager::instance().getFont();
    int starting_y = WINDOW_HEIGHT / 2;
    int starting_x = WINDOW_WIDTH / 2;
    m_background.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    m_textures[0] = ResourceManager::instance().getText();
    m_background.setTexture(&m_textures[0]);
    for (int i = 0; i < NUM_OF_BUTTONS; i++) {
        m_texts[i].setFont(m_font);
        m_texts[i].setCharacterSize(25);
        m_texts[i].setFillColor(sf::Color(255, 255, 255));
        m_texts[i].setString(m_textNames[i]);
        m_texts[i].setOrigin(
                sf::Vector2f(m_texts[i].getGlobalBounds().width / 2, m_texts[i].getGlobalBounds().height / 2));
        m_texts[i].setPosition(sf::Vector2f(starting_x, starting_y));
        starting_y += m_texts[i].getGlobalBounds().height + 30;
    }

}

void MainMenu::getEvents() {
    printMenu();
    while (m_window.isOpen()) {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_window.close();
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                handleClick(event.mouseButton);
            }
            handleHover();
        }
        printMenu();
    }
}

void MainMenu::printMenu() {
    m_window.clear();
    m_window.draw(m_background);
    for (int i = 0; i < NUM_OF_BUTTONS; i++) {
        m_window.draw(m_texts[i]);
    }
    m_window.display();
}

void MainMenu::handleHover() {
    for (int i = 0; i < NUM_OF_BUTTONS; i++) {
        if (m_texts[i].getGlobalBounds().contains(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)))) {
            m_texts[i].setOutlineThickness(2);
            m_texts[i].setOutlineColor(sf::Color::Red);
        } else {
            m_texts[i].setFillColor(sf::Color::White);
            m_texts[i].setOutlineThickness(0);
        }
    }
}

void MainMenu::handleClick(sf::Event::MouseButtonEvent &click) {
    for (int i = 0; i < NUM_OF_BUTTONS; i++) {
        if (m_texts[i].getGlobalBounds().contains(m_window.mapPixelToCoords({click.x, click.y}))) {
            switch (i) {
                case 0:
                    players[0] = std::make_unique<UserPlayer>();
                    players[1] = std::make_unique<RandomPlayer>();
                    Controller(m_window, players).run();
                    break;
                case 1:
                    players[0] = std::make_unique<UserPlayer>();
                    players[1] = std::make_unique<GreedyPlayerSmallDistance>();
                    Controller(m_window, players).run();
                    break;
                case 2:
                    players[0] = std::make_unique<UserPlayer>();
                    players[1] = std::make_unique<GreedyPlayerLongDistance>();
                    Controller(m_window, players).run();
                    break;
                case 3:
                    players[0] = std::make_unique<UserPlayer>();
                    players[1] = std::make_unique<UserPlayer>();
                    Controller(m_window, players).run();
                    break;
                case 4:
                    printHelp();
                    break;
                case 5:
                    m_window.close();
                    break;
            }

        }

    }
    players[0].reset(nullptr);
    players[1].reset(nullptr);

}

void MainMenu::printHelp() {
    std::cout << "HELP ME";
}

