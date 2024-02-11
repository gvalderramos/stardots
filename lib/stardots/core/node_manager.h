//
// Created by Gabriel Valderramos on 2/6/24.
//
#pragma once

#include "node.h"

#include <memory>
#include <vector>


namespace stardots::core {

    class NodeManager {
    public:
        NodeManager();
        ~NodeManager();

        typedef std::vector<std::shared_ptr<Node>>::iterator NodeIterator;
        [[nodiscard]] NodeIterator begin();
        [[nodiscard]] NodeIterator end();

        std::shared_ptr<Node> operator[](const int& index) const;

        std::shared_ptr<Node> addNode();
        std::shared_ptr<Node> getNodeWithLessConnectedInput() const;
        std::shared_ptr<Node> getNodeWithLessConnectedOutput() const;
        std::size_t size() const;

    private:
        std::vector<std::shared_ptr<Node>> m_nodes;
    };

} // core
// stardots
