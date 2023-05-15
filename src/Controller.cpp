#include "Controller.h"


Controller::Controller(sf::RenderWindow &window, std::unique_ptr<Player> *players) : m_window(window),
                                                                                     m_players(players),m_board(std::make_unique<HexagonBoard>()) {
    m_board->create();
    auto tr = m_board->getTopRightCorner();
    m_lastChoosed[0] = tr.getData()->getColor();
    auto bl = m_board->getBottomLeftCorner();
    m_lastChoosed[1] = bl.getData()->getColor();
    m_players[0]->setPad(bl);
    m_players[1]->setPad(tr);
    std::stringstream stream;
    for(int i = 0; i < 2; i++) {
        m_scores[i] = float(m_players[i]->getNumOfPads()) / (NUM_OF_COLS * NUM_OF_ROWS) * 100;
        stream << std::fixed << std::setprecision(2) << m_scores[i];
        m_texts[int(i) + 2].setString(stream.str() + "%");
    }
    createColorBtns();
    initTexts();

    isTwoPlayers = typeid(*m_players[1].get()).name() == typeid(*m_players[0].get()).name();

}

void Controller::run() {
    bool didPlayerChoose[2] = {false};
    Turn turn = User;

    Colors chosenColor;
    printWindowObjects();
    while (m_window.isOpen() && !m_isGameOver) {
        if (auto event = sf::Event{}; m_window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    m_window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    for (auto btn: m_colorBtns)
                        if (btn.isPressed(event.mouseButton)) {
                            if (btn.getColor() != m_lastChoosed[0] && btn.getColor() != m_lastChoosed[1]) {
                                didPlayerChoose[turn] = true;
                                chosenColor = btn.getColor();
                            }
                        }
                    if (m_texts[0].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) return;
                    break;
                case sf::Event::MouseMoved:
                    handleHover(event.mouseMove);
                    break;
            }
        }

        if (didPlayerChoose[User]){
            playerTurn(User, chosenColor);
            turn = Other;
            m_turnText.setString("Turn: P1");
            didPlayerChoose[User] = false;

            if (!isTwoPlayers){
                playerTurn(Other, chosenColor);
                didPlayerChoose[Other] = false;
                turn = User;
            }
        }

        if (isTwoPlayers && didPlayerChoose[Other]) {
            playerTurn(Other, chosenColor);
            didPlayerChoose[Other] = false;
            m_turnText.setString("Turn: P2");
            turn = User;
        }

        if (m_scores[0] >= 50 || m_scores[1] >= 50)
            m_isGameOver = true;

        lightPads();
        m_texts[3].setOrigin(m_texts[3].getGlobalBounds().width, 0);
        printWindowObjects();
    }
}

void Controller::printWindowObjects() {
    m_window.clear();
    m_board->printBoardObject(m_window);

    for (auto btn: m_colorBtns)
        btn.draw(m_window);

    for (auto txt: m_texts)
        m_window.draw(txt);

    if (isTwoPlayers)
        m_window.draw(m_turnText);

    if (m_isGameOver) {
        std::string winner = (m_scores[0] >= 50) ? "    P1    " : "    P2    ";

        m_gameOverText.setString(m_gameOverText.getString() + winner);
        m_board->blur(m_window);
        m_window.draw(m_gameOverText);
    }

    m_window.display();
    if (m_isGameOver)
        sf::sleep(sf::seconds(5));
}

void Controller::createColorBtns() {
    const auto boardBounds = m_board->getBoardBounds();
    float pos_x = WINDOW_WIDTH*0.2;
    float pos_y = boardBounds.top + boardBounds.height;
    pos_y += (WINDOW_HEIGHT - pos_y - BUTTON_SIZE)/2;

    for (int i = 0; i < NUM_OF_COLORS; i++) {
        Colors color = Colors(i);
        bool disabled = color == m_lastChoosed[0] || color == m_lastChoosed[1];
        m_colorBtns[i] = ColorBtn(color, sf::Vector2f(pos_x, pos_y), disabled);
        pos_x += BUTTON_SIZE;
    }

    //add spacing
    const float extra_space = (WINDOW_WIDTH*0.8 - m_colorBtns[5].getBounds().left - BUTTON_SIZE)/7;
    for (int i = 0; i < NUM_OF_COLORS; i++)
        m_colorBtns[i].shiftPosition(extra_space*(i+1));


}

void Controller::playerTurn(Turn t, Colors color) {
    const Colors c = m_players[t]->play(color, m_lastChoosed);
    setLastColors(c);
    std::stringstream stream;

    m_scores[t] = float(m_players[t]->getNumOfPads()) / (NUM_OF_COLS * NUM_OF_ROWS) * 100;
    stream << std::fixed << std::setprecision(2) << m_scores[t];
    m_texts[int(t) + 2].setString(stream.str() + "%");

}

void Controller::setLastColors(Colors color) {
    m_colorBtns[m_lastChoosed[1]].setDisabled(false);

    m_lastChoosed[1] = m_lastChoosed[0];
    m_lastChoosed[0] = color;

    m_colorBtns[color].setDisabled(true);

}

void Controller::handleHover(sf::Event::MouseMoveEvent &event) {
    if (m_texts[0].getGlobalBounds().contains(m_window.mapPixelToCoords({event.x, event.y}))) {
        m_texts[0].setOutlineThickness(2);
        m_texts[0].setOutlineColor(sf::Color::Red);
    } else {
        m_texts[0].setFillColor(sf::Color::White);
        m_texts[0].setOutlineThickness(0);
    }
    printWindowObjects();
}

void Controller::initTexts() {
    sf::FloatRect boardBounds = m_board->getBoardBounds();

    int starting_x = WINDOW_WIDTH * 0.03;
    int starting_y = starting_x;

    std::stringstream stream;

    for (int i = 0; i < 4; i++) {
        m_texts[i].setFont(ResourceManager::instance().getFont());
        if (i < 2) {
            m_texts[i].setCharacterSize(30);
            m_texts[i].setPosition(sf::Vector2f(starting_x, starting_y));
            m_texts[i].setFillColor(sf::Color::White);
            m_texts[i].setOutlineColor(sf::Color::Black);
            m_texts[i].setOutlineThickness(1);
            m_texts[i].setString(m_textNames[i]);
            starting_x = WINDOW_WIDTH / 2 - m_texts[i].getGlobalBounds().width * 2;
            starting_y += m_texts[i].getGlobalBounds().height;
        } else {
            stream << std::fixed << std::setprecision(2) << m_scores[i - 2];
            m_texts[i].setString(stream.str() + "%");
            m_texts[i].setCharacterSize(30);
            m_texts[i].setOutlineColor(sf::Color::Black);
            m_texts[i].setOutlineThickness(1);
            stream.str("");
        }
    }

    m_texts[2].setPosition(boardBounds.left, boardBounds.top - m_texts[2].getGlobalBounds().height * 1.5);
    m_texts[3].setPosition(boardBounds.left + boardBounds.width,
                           boardBounds.top - m_texts[3].getGlobalBounds().height * 1.5);
    m_texts[3].setOrigin(m_texts[3].getGlobalBounds().width, 0);

    m_turnText.setString("Turn: P1");
    m_turnText.setFont(ResourceManager::instance().getFont());
    m_turnText.setCharacterSize(30);
    m_turnText.setOutlineColor(sf::Color::Black);
    m_turnText.setOutlineThickness(1);
    m_turnText.setPosition(WINDOW_WIDTH / 2, m_board->getBoardBounds().top - m_turnText.getGlobalBounds().height * 1.5);
    m_turnText.setOrigin(m_turnText.getGlobalBounds().width / 2, 0);

    m_gameOverText.setString("Game Over!\n\nWinner is:\n\n");
    m_gameOverText.setFont(ResourceManager::instance().getFont());
    m_gameOverText.setCharacterSize(50);
    m_gameOverText.setFillColor(sf::Color::White);
    m_gameOverText.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    m_gameOverText.setOrigin(m_gameOverText.getGlobalBounds().width / 2,
                             m_gameOverText.getGlobalBounds().height / 2);
}

void Controller::lightPads() {
    static sf::Clock clock;
    float dt = clock.getElapsedTime().asSeconds();
    static bool light = true;
    auto player_pads = m_players[0]->getPads();
    auto other_pads = m_players[1]->getPads();
    if (dt > 0.5) {
        light = !light;
        for (GraphNode<std::shared_ptr<Pad>> pad: *player_pads)
            pad.getData()->setOutline(light);
        for (GraphNode<std::shared_ptr<Pad>> pad: *other_pads)
            pad.getData()->setOutline(light);

        clock.restart().asSeconds();
    }
}