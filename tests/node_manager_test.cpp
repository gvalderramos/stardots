//
// Created by Gabriel Valderramos on 2/11/24.
//

#include "gtest/gtest.h"
#include "stardots/stardots.h"

namespace {
    class NodeManager : public ::testing::Test {
    protected:
        stardots::core::NodeManager *nodeManager;

        NodeManager() {};

        virtual ~NodeManager() {};

        virtual void SetUp() {
            nodeManager = new stardots::core::NodeManager();
        }

        virtual void TearDown() {
            delete nodeManager;
        }
    };

    TEST_F(NodeManager, CanCheckLessConnections) {

        auto node1 = nodeManager->addNode();
        auto node2 = nodeManager->addNode();

        auto plug1Node1 = dynamic_cast<stardots::core::Plug<int> *>(node1->addOutputPlug(1, "plug_01"));
        auto plug2Node1 = node1->addInputPlug(2.0f, "plug_02");

        auto plug1Node2 = dynamic_cast<stardots::core::Plug<int> *>(node2->addInputPlug(1, "plug_01"));

        plug1Node1->next(plug1Node2);

        ASSERT_EQ(nodeManager->getNodeWithLessConnectedInput(), node1);
        ASSERT_EQ(nodeManager->getNodeWithLessConnectedOutput(), node2);
    }

    TEST_F(NodeManager, CanCheckNodeSize) {

        auto node1 = nodeManager->addNode();
        auto node2 = nodeManager->addNode();

        ASSERT_EQ(nodeManager->size(), 2);
    }

    TEST_F(NodeManager, CanGetByIndex) {

        auto node1 = nodeManager->addNode();
        auto node2 = nodeManager->addNode();

        ASSERT_EQ((*nodeManager)[0], node1);
        ASSERT_EQ((*nodeManager)[1], node2);
        ASSERT_EQ((*nodeManager)[2], nullptr);
    }

    TEST_F(NodeManager, CanGetName) {

        auto node1 = nodeManager->addNode();
        auto node2 = nodeManager->addNode();
        auto node3 = nodeManager->addNode();

        node1->name("node1");
        node2->name("node2");
        node3->name("node3");

        int i = 0;
        for(auto node : *nodeManager) {

            if(i==0) {
                ASSERT_EQ(node->name(), "node1");
            } else if (i==1) {
                ASSERT_EQ(node->name(), "node2");
            } else if (i==2) {
                ASSERT_EQ(node->name(), "node3");
            } else {
                FAIL();
            }

            i++;
        }
    }
}