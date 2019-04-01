#include <memory>
#include <vector>
#include <stdint.h>
#include <iostream>

struct Player {
    uint32_t player_id;
    uint32_t session_id;
};

class MyNetworkClientInterface {
public:
    virtual void heartbeat(uint32_t session_id) = 0;
};

class MyNetworkClient : public MyNetworkClientInterface {
public:
    void heartbeat(uint32_t session_id);
};

class Room {
public:
    std::vector<Player> players;
    MyNetworkClientInterface *client;

    void update() {
        for (auto &player : players) {
            if (player.session_id != 0) {
                client->heartbeat(player.session_id);
            }
        }
    }
};
