//
// Created by Gabriel Valderramos on 2/6/24.
//

#include "node_manager.h"


namespace stardots::core {
    NodeManager::NodeManager() {

    }

    NodeManager::~NodeManager() {
        auto i = m_nodes.begin();
    }

    NodeManager::NodeIterator NodeManager::begin() {
        return m_nodes.begin();
    }

    NodeManager::NodeIterator NodeManager::end() {
        return m_nodes.end();
    }

    std::shared_ptr<Node> NodeManager::operator[](const int &index) const {
        if(index >= m_nodes.size()) {
            return nullptr;
        }
        return m_nodes[index];
    }

    std::shared_ptr<Node> NodeManager::addNode() {
        auto node = std::shared_ptr<Node>(new Node());
        m_nodes.push_back(node);
        return node;
    }

    std::shared_ptr<Node> NodeManager::getNodeWithLessConnectedInput() const {
        std::shared_ptr<Node> n = nullptr;
        auto lessResult = SIZE_T_MAX;
        for(auto& node: m_nodes) {
            if(node->connectedInputs() < lessResult) {
                lessResult = node->connectedInputs();
                n = node;
            }
        }
        return n;
    }

    std::shared_ptr<Node> NodeManager::getNodeWithLessConnectedOutput() const {
        std::shared_ptr<Node> n = nullptr;
        auto lessResult = SIZE_T_MAX;
        for(auto& node: m_nodes) {
            if(node->connectedOutputs() < lessResult) {
                lessResult = node->connectedOutputs();
                n = node;
            }
        }
        return n;
    }

    std::size_t NodeManager::size() const {
        return m_nodes.size();
    }
}