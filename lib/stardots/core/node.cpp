//
// Created by Gabriel Valderramos on 2/4/24.
//

#include "node.h"

using namespace stardots::core;

Node::Node() {

}

Node::~Node() {

}

Node::PlugIter Node::inBegin() {
    return m_inputs.begin();
}

Node::PlugIter Node::inEnd() {
    return m_inputs.end();
}

Node::PlugIter Node::outBegin() {
    return m_outputs.begin();
}

Node::PlugIter Node::outEnd() {
    return m_outputs.end();
}

std::size_t Node::connectedInputs() const {
    std::size_t result = 0;
    for(auto& plug: m_inputs) {
        if(plug->isConnected())
            result++;
    }
    return result;
}

std::size_t Node::connectedOutputs() const {
    std::size_t result = 0;
    for(auto& plug: m_outputs) {
        if(plug->isConnected())
            result++;
    }
    return result;
}
