//
// Created by Gabriel Valderramos on 2/4/24.
//
#pragma once

#include <vector>
#include <memory>
#include <string>

#include "plug.h"


namespace stardots::core {
    class NodeManager;
    class Node {

    public:
        ~Node();

        typedef std::vector<std::unique_ptr<IPlug>>::iterator PlugIter;
        PlugIter inBegin();
        PlugIter inEnd();
        PlugIter outBegin();
        PlugIter outEnd();

        template<typename T>
        void addInputPlug(const T& value, const std::string& name) {
            auto plug = std::make_unique<Plug<T>>(new Plug((std::make_shared<Node>(*this), value, name)));
            m_inputs.push_back(plug);
        }
        template<typename T>
        void addOutputPlug(const T& value, const std::string& name) {
            auto plug = std::make_unique<Plug<T>>(new Plug((std::make_shared<Node>(*this), value, name)));
            m_outputs.push_back(plug);
        }

        std::size_t connectedInputs() const;
        std::size_t connectedOutputs() const;

    private:
        Node();

        std::vector<std::unique_ptr<IPlug>> m_outputs;
        std::vector<std::unique_ptr<IPlug>> m_inputs;

        friend class NodeManager;
    };
}
