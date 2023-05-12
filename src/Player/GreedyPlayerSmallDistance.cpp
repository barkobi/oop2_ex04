
#include "GreedyPlayerSmallDistance.h"

GreedyPlayerSmallDistance::GreedyPlayerSmallDistance()
    : Player() {}

Colors GreedyPlayerSmallDistance::play(Colors color, Colors *lastChoosed) {
    int count_colors[NUM_OF_COLORS] = {0};

    count_colors[lastChoosed[0]] = (NUM_OF_ROWS*NUM_OF_COLS)*-1;
    count_colors[lastChoosed[1]] = (NUM_OF_ROWS*NUM_OF_COLS)*-1;

    for(auto pad : m_pads)
        pad.sumNeighborsColors(count_colors);

    int *max = std::max_element(std::begin(count_colors), std::end(count_colors));
    int new_color = max-count_colors;

    drawNeighbors(Colors(new_color));
    return Colors(new_color);

}