#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>
#include <stdint.h>

#include "src/example.cpp"

class MockMyNetworkClient : public MyNetworkClientInterface {
public:
    MOCK_METHOD1(heartbeat, void(uint32_t session_id));
};

TEST(example_test, func_update) {
    MockMyNetworkClient client;

    auto room = std::unique_ptr<Room>(new Room());
    room->players.push_back(Player{1, 1234});
    room->players.push_back(Player{2, 0});
    room->client = &client;

    EXPECT_CALL(client, heartbeat(1234)).Times(1);
    EXPECT_CALL(client, heartbeat(0)).Times(0); // session_id‚ª 0 ‚È‚Ì‚ÅŒÄ‚Î‚ê‚È‚¢

    room->update();
}