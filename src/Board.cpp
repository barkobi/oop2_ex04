#include "Board.h"
#include "iostream"

void Board::create() {
    srand(time(NULL));
    const float total_width = ((PAD_WIDTH * 1.5) + 4) * (NUM_OF_COLS - 0.5);
    const float starting_x = WINDOW_WIDTH / 2 - total_width / 2 - ((PAD_WIDTH * 1.5) + 4) / 2;

    const float total_height = (PAD_WIDTH * 1.5) * (NUM_OF_ROWS - 0.5);
    const float starting_y = WINDOW_HEIGHT / 2 - total_height / 2;

    int i = 0;
    float x = starting_x, y = starting_y;
    for (int row = 0; row < NUM_OF_ROWS; row++, y += PAD_WIDTH * 1.5) {
        for (int col = 0; col < NUM_OF_COLS; col++, x += (PAD_WIDTH * 1.5) + 4) {
            int rand = std::rand() % NUM_OF_COLORS;
            std::shared_ptr<Shapes> shape = std::make_shared<Pad>(i, Colors(rand), sf::Vector2f(x, y));
            MosaicNode<std::shared_ptr<Shapes>> node(&shape);
            m_pads.add(&node);
            i++;
        }
        x = row % 2 == 0 ? (PAD_WIDTH * 0.75) + 2 : 0;
        x += starting_x;
    }

    while (getTopRightCorner()->data->get()->getColor() == getBottomLeftCorner()->data->get()->getColor()) {
        int rand = std::rand() % NUM_OF_COLORS;
        getTopRightCorner()->data->get()->setColor(Colors(rand));
    }

    initOverlay(starting_x, starting_y, total_width, total_height);
    createNeighbors();

}

void Board::initOverlay(float starting_x, float starting_y, float width, float height) {

    // overlay frame
    m_overlay[4].setSize(sf::Vector2f(width, height));
    m_overlay[4].setPosition(starting_x + PAD_WIDTH * 0.75 + 2, starting_y + PAD_WIDTH * 0.5);
    m_overlay[4].setFillColor(sf::Color::Transparent);
    m_overlay[4].setOutlineColor(sf::Color::White);
    m_overlay[4].setOutlineThickness(2);

    // top overlay
    m_overlay[0].setSize(sf::Vector2f(WINDOW_WIDTH, starting_y + PAD_WIDTH * 0.5));
    m_overlay[0].setPosition(sf::Vector2f(0, 0));
    m_overlay[0].setFillColor(sf::Color(34, 160, 191));
    // left overlay
    m_overlay[1].setSize(sf::Vector2f(starting_x + PAD_WIDTH * 0.75 + 2, WINDOW_HEIGHT));
    m_overlay[1].setPosition(sf::Vector2f(0, 0));
    m_overlay[1].setFillColor(sf::Color(34, 160, 191));
    // right overlay
    m_overlay[2].setSize(sf::Vector2f(starting_x + PAD_WIDTH * 0.75 + 2, WINDOW_HEIGHT));
    m_overlay[2].setPosition(sf::Vector2f(starting_x + PAD_WIDTH * 0.75 + 2 + width, 0));
    m_overlay[2].setFillColor(sf::Color(34, 160, 191));
    // bottom overlay
    m_overlay[3].setSize(sf::Vector2f(WINDOW_WIDTH, starting_y));
    m_overlay[3].setPosition(sf::Vector2f(0, starting_y + PAD_WIDTH * 0.5 + height));
    m_overlay[3].setFillColor(sf::Color(34, 160, 191));

//    for (int i = 0; i < 4; i++){
//        m_overlay[i].setFillColor(sf::Color(255,255,255,100));
//    }

}

MosaicNode<std::shared_ptr<Shapes>> *Board::getBottomLeftCorner() {
    return &m_pads[NUM_OF_COLS * NUM_OF_ROWS - NUM_OF_COLS];
}

MosaicNode<std::shared_ptr<Shapes>> *Board::getTopRightCorner() {
    return &m_pads[NUM_OF_COLS - 1];
}

sf::FloatRect Board::getBoardBounds() {
    return m_overlay[4].getGlobalBounds();
}

void Board::printBoardObject(sf::RenderWindow &window) {
    for (auto &it: m_pads) {
        it.data->get()->draw(window);
    }

    for (int i = 0; i < 5; i++)
        window.draw(m_overlay[i]);
}

/*
void Board::attachNeighbors() {
    for (int row = 0; row < NUM_OF_ROWS; row++) {
        for (int col = 0; col < NUM_OF_COLS; col++) {
            auto arr_neighbors = m_pads[row][col]->getNeighbor();
            auto it = arr_neighbors->begin();
            if (row == 0) {
                if (col != 0) {
                    *it = m_pads[row][col-1];
                    it++;
                    *it = m_pads[row + 1][col - 1];
                    it++;
                }
                *it = m_pads[row + 1][col];
                it++;
                if (col != NUM_OF_COLS - 1) {
                    *it = m_pads[row][col + 1];
                }
            } else if (row == NUM_OF_ROWS - 1) {
                if (col != 0) {
                    *it = m_pads[row - 1][col - 1];
                    it++;
                    *it = m_pads[row][col - 1];
                    it++;
                }
                *it = m_pads[row - 1][col];
                it++;
                if (col != NUM_OF_COLS - 1){
                    *it = m_pads[row][col + 1];
                }
            } else {
                if(row % 2 == 0){
                    if(col == 0){
                        *it = m_pads[row][col + 1];
                        it++;
                        *it = m_pads[row - 1][col];
                        it++;
                        *it = m_pads[row + 1][col];
                    }
                    else if(col == NUM_OF_COLS - 1){
                        *it = m_pads[row][col - 1];
                        it++;
                        *it = m_pads[row - 1][col];
                        it++;
                        *it = m_pads[row + 1][col];
                        it++;
                        *it = m_pads[row - 1][col - 1];
                        it++;
                        *it = m_pads[row + 1][col - 1];
                    }
                    else{
                        *it = m_pads[row - 1][col - 1];
                        it++;
                        *it = m_pads[row][col + 1];
                        it++;
                        *it = m_pads[row - 1][col];
                        it++;
                        *it = m_pads[row][col - 1];
                        it++;
                        *it = m_pads[row + 1][col];
                        it++;
                        *it = m_pads[row + 1][col - 1];
                    }
                }else{
                    if(col == NUM_OF_COLS - 1){
                        *it = m_pads[row][col - 1];
                        it++;
                        *it = m_pads[row - 1][col];
                        it++;
                        *it = m_pads[row + 1][col];
                    }
                    else if(col == 0){
                        *it = m_pads[row][col + 1];
                        it++;
                        *it = m_pads[row - 1][col];
                        it++;
                        *it = m_pads[row + 1][col];
                        it++;
                        *it = m_pads[row - 1][col + 1];
                        it++;
                        *it = m_pads[row + 1][col + 1];
                    }
                    else{
                        *it = m_pads[row - 1][col + 1];
                        it++;
                        *it = m_pads[row][col + 1];
                        it++;
                        *it = m_pads[row - 1][col];
                        it++;
                        *it = m_pads[row][col - 1];
                        it++;
                        *it = m_pads[row + 1][col];
                        it++;
                        *it = m_pads[row + 1][col + 1];
                    }
                }
            }
        }
    }
}

*/
void Board::blur(sf::RenderWindow &window) {
    m_overlay[4].setFillColor(sf::Color(0, 0, 0, 180));
    window.draw(m_overlay[4]);
}

void Board::createNeighbors() {
    std::vector<sf::Vector2u> odd_neighbors{
            sf::Vector2u(1, 0),
            sf::Vector2u(-1, 0),
            sf::Vector2u(0, -1),
            sf::Vector2u(1, -1),
            sf::Vector2u(0, 1),
            sf::Vector2u(1, 1)
    };
    std::vector<sf::Vector2u> even_neighbors{
            sf::Vector2u(1, 0),
            sf::Vector2u(-1, 0),
            sf::Vector2u(0, -1),
            sf::Vector2u(-1, -1),
            sf::Vector2u(0, 1),
            sf::Vector2u(-1, 1)
    };
    auto tmp_odd = odd_neighbors;
    auto tmp_even = even_neighbors;
    for (int i = 0; i < (NUM_OF_COLS * NUM_OF_ROWS); i++) {
        std::cout << i << " \n";

        int x = i % NUM_OF_COLS;
        int y = i / NUM_OF_COLS;
        if (y % 2 == 0)
        {
            for (sf::Vector2u& neighbor : tmp_even) {
                neighbor += sf::Vector2u(x, y);
                if(neighbor.x >= 0 && neighbor.x < NUM_OF_COLS && neighbor.y >= 0 && neighbor.y < NUM_OF_ROWS){
                    std::cout << "neighbor = " << neighbor.x+neighbor.y*NUM_OF_COLS << "\n";
                    m_pads[i].addNeighbor(&m_pads[neighbor.x+neighbor.y*NUM_OF_COLS]);
                }
            }
        }
        else
        {
            for (sf::Vector2u& neighbor : tmp_odd) {
                neighbor += sf::Vector2u(x, y);
                if(neighbor.x >= 0 && neighbor.x < NUM_OF_COLS && neighbor.y >= 0 && neighbor.y < NUM_OF_ROWS){
                    m_pads[i].addNeighbor(&m_pads[neighbor.x+neighbor.y*NUM_OF_COLS]);
                }
            }
        }
        tmp_even = even_neighbors;
        tmp_odd = odd_neighbors;
    }
}

