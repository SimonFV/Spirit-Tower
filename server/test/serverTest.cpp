#include <gtest/gtest.h>
#include <game.hpp>

struct serverTest : public ::testing::Test
{
    virtual void SetUp() override {}
    virtual void TearDown() override {}
};

/** Test of add method, of class server.
 * 
 */
TEST_F(serverTest, CheckNewBitMap)
{
    spdlog::info("Revisando la función newBitMap...");
    game::getInstance()->newBitMap(",011\n110\n010\n");
    EXPECT_EQ(game::getInstance()->getStrGrid(),
              "Generado el mapa de bits del nivel:\n0 1 1 \n1 1 0 \n0 1 0 \n");
}