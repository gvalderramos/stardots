//
// Created by Gabriel Valderramos on 2/4/24.
//

#include "gtest/gtest.h"
#include "stardots/stardots.h"

namespace {
class PlugTest : public ::testing::Test {
protected:
    stardots::core::NodeManager * nodeManager;

    PlugTest() {};
    virtual ~PlugTest() {};

    virtual void SetUp() {
        nodeManager = new stardots::core::NodeManager();
    }
    virtual void TearDown() {
        delete nodeManager;
    }
};

    TEST_F(PlugTest, CanSetNodeInstance) {

        auto node = nodeManager->addNode();

        stardots::core::Plug<int> plug(1, "plug_01");
        plug.node(node.get());

        ASSERT_EQ(plug.node(), node.get());
    }

    TEST_F(PlugTest, CanSetNameValueAndType) {

        auto node = nodeManager->addNode();

        stardots::core::Plug<int> plug(1, "plug_01");
        plug.node(node.get());

        ASSERT_EQ(plug.value(), 1);
        plug.value(2);

        ASSERT_EQ(plug.name(), "plug_01");
        ASSERT_EQ(plug.value(), 2);
        ASSERT_EQ(plug.plugType(), typeid(int).name());
    }

    TEST_F(PlugTest, CanConnectWithNextPlug) {

        auto node1 = nodeManager->addNode();
        auto node2 = nodeManager->addNode();

        stardots::core::Plug<float> plug01(2.0f, "plug_01");
        plug01.node(node1.get());

        stardots::core::Plug<float> plug02(2.0f, "plug_02");
        plug02.node(node2.get());

        plug01.next(&plug02);

        ASSERT_EQ(plug01.isConnected(), true);
        ASSERT_EQ(plug02.isConnected(), true);
    }

    TEST_F(PlugTest, CanSetValueOfConnectedPlugs) {

        auto node1 = nodeManager->addNode();
        auto node2 = nodeManager->addNode();

        stardots::core::Plug<float> plug01(2.0f, "plug_01");
        plug01.node(node1.get());

        stardots::core::Plug<float> plug02(2.0f, "plug_02");
        plug02.node(node2.get());

        plug01.next(&plug02);

        plug01.value(3.0f);
        ASSERT_EQ(plug01.value(), 3.0f);
        ASSERT_EQ(plug02.value(), 3.0f);

        plug02.value(5.0f);
        ASSERT_EQ(plug01.value(), 5.0f);
        ASSERT_EQ(plug02.value(), 5.0f);

    }

}