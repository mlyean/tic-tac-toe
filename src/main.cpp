#include <iostream>

#include "client.hpp"

int main() {
    TicTacToeClient client;
    client.init();
    client.run();

    return 0;
}