//
// Created by Gabriel Valderramos on 2/4/24.
//

#include "node.h"

using namespace stardots::core;

Node::Node() {
    m_plugs[PlugDesc::OUTPUT] = {};
    m_plugs[PlugDesc::INPUT] = {};
}

Node::~Node() {
    auto it = m_plugs.begin();
    while (it != m_plugs.end()) {
        for (auto plug : it->second) {
            delete plug;
        }
        it++;
    }
}

Node::PlugIter Node::inBegin() {
    return m_plugs[PlugDesc::INPUT].begin();
}

Node::PlugIter Node::inEnd() {
    return m_plugs[PlugDesc::INPUT].end();
}

Node::PlugIter Node::outBegin() {
    return m_plugs[PlugDesc::OUTPUT].begin();
}

Node::PlugIter Node::outEnd() {
    return m_plugs[PlugDesc::OUTPUT].end();
}

std::size_t Node::connectedInputs() const {
    std::size_t result = 0;
    for(auto& plug: m_plugs.at(PlugDesc::INPUT)) {
        if(plug->isConnected())
            result++;
    }
    return result;
}

std::size_t Node::connectedOutputs() const {
    std::size_t result = 0;
    for(auto& plug: m_plugs.at(PlugDesc::OUTPUT)) {
        if(plug->isConnected())
            result++;
    }
    return result;
}
