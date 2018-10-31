#include "gtest/gtest.h"
#include "QConn.hpp"

TEST(QConnConstructor, Simple) {

    EXPECT_EQ(QConn(":localhost:8833").host(), "localhost");
    EXPECT_EQ(QConn(":localhost:8833").port(), 8833);
    EXPECT_EQ(QConn(":localhost:8833").auth(), "");

    EXPECT_EQ(QConn(":localhost:8833:user:pass").host(), "localhost");
    EXPECT_EQ(QConn(":localhost:8833:user:pass").port(), 8833);
    EXPECT_EQ(QConn(":localhost:8833:user:pass").auth(), "user:pass");

    EXPECT_EQ(QConn("::8833:user:pass").host(), "localhost");
    EXPECT_EQ(QConn("::8833:user:pass").port(), 8833);
    EXPECT_EQ(QConn("::8833:user:pass").auth(), "user:pass");

    EXPECT_EQ(QConn("::8833").host(), "localhost");
    EXPECT_EQ(QConn("::8833").port(), 8833);
    EXPECT_EQ(QConn("::8833").auth(), "");


}