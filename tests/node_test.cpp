//
// Created by Gabriel Valderramos on 2/11/24.
//

#include "gtest/gtest.h"
#include "stardots/stardots.h"

namespace {
    class NodeTest : public ::testing::Test {
    protected:
        stardots::core::NodeManager * nodeManager;

        NodeTest() {};
        virtual ~NodeTest() {};

        virtual void SetUp() {
            nodeManager = new stardots::core::NodeManager();
        }
        virtual void TearDown() {
            delete nodeManager;
        }
    };

    TEST_F(NodeTest, CanAccessInputPlugsByNode) {

        auto node1 = nodeManager->addNode();

        node1->addInputPlug(1, "plug_01");
        node1->addInputPlug(2.0f, "plug_02");

        for(auto plugIter = node1->inBegin(); plugIter != node1->inEnd(); plugIter++) {
            auto iplug = *plugIter;
            if(iplug->plugType() == "i") {
                auto plug = dynamic_cast<stardots::core::Plug<int>*>(iplug);
                if (plug) {
                    ASSERT_EQ(plug->name(), "plug_01");
                    ASSERT_EQ(plug->value(), 1);
                }
            } else {
                auto plug = dynamic_cast<stardots::core::Plug<float>*>(iplug);
                if (plug) {
                    ASSERT_EQ(plug->name(), "plug_02");
                    ASSERT_EQ(plug->value(), 2.0f);
                }
            }
        }

    }

    TEST_F(NodeTest, CanAccessOutputPlugsByNode) {

        auto node1 = nodeManager->addNode();

        node1->addInputPlug(1, "plug_01");
        node1->addInputPlug(2.0f, "plug_02");

        for(auto plugIter = node1->outBegin(); plugIter != node1->outEnd(); plugIter++) {
            auto iplug = *plugIter;
            if(iplug->plugType() == "i") {
                auto plug = dynamic_cast<stardots::core::Plug<int>*>(iplug);
                if (plug) {
                    ASSERT_EQ(plug->name(), "plug_01");
                    ASSERT_EQ(plug->value(), 1);
                }
            } else {
                auto plug = dynamic_cast<stardots::core::Plug<float>*>(iplug);
                if (plug) {
                    ASSERT_EQ(plug->name(), "plug_02");
                    ASSERT_EQ(plug->value(), 2.0f);
                }
            }
        }

    }

    TEST_F(NodeTest, CanCheckConnectionSize) {

        auto node1 = nodeManager->addNode();
        auto node2 = nodeManager->addNode();

        auto plug1Node1 = dynamic_cast<stardots::core::Plug<int>*>(node1->addOutputPlug(1, "plug_01"));
        auto plug2Node1 = node1->addInputPlug(2.0f, "plug_02");

        auto plug1Node2 = dynamic_cast<stardots::core::Plug<int>*>(node2->addInputPlug(1, "plug_01"));

        plug1Node1->next(plug1Node2);

        ASSERT_EQ(node1->connectedInputs(), 0);
        ASSERT_EQ(node1->connectedOutputs(), 1);
        ASSERT_EQ(node2->connectedInputs(), 1);
        ASSERT_EQ(node2->connectedOutputs(), 0);
    }
}