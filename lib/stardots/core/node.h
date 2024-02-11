//
// Created by Gabriel Valderramos on 2/4/24.
//
#pragma once

#include <vector>
#include <memory>
#include <string>
#include <map>

#include "plug.h"


namespace stardots::core {
    class NodeManager;
    class Node {

    public:
        ~Node();

        typedef std::vector<IPlug*>::iterator PlugIter;
        PlugIter inBegin();
        PlugIter inEnd();
        PlugIter outBegin();
        PlugIter outEnd();

        template<typename T>
        IPlug* addInputPlug(const T& value, const std::string& name) {
            IPlug* plug;
            plug = new Plug<T>(value, name);
            plug->node(this);
            m_plugs[PlugDesc::INPUT].push_back(plug);
            return plug;
        }
        template<typename T>
        IPlug* addOutputPlug(const T& value, const std::string& name) {
            auto* plug = new Plug<T>(value, name);
            plug->node(this);
            m_plugs[PlugDesc::OUTPUT].push_back(plug);
            return plug;
        }

        std::size_t connectedInputs() const;
        std::size_t connectedOutputs() const;

        inline std::string name() const {return m_name;};
        inline void name(const std::string& name) {m_name = name;};
    private:
        Node();

        enum class PlugDesc {
            OUTPUT = 0,
            INPUT
        };
        std::map<PlugDesc, std::vector<IPlug*>> m_plugs;
        std::string m_name;

        friend class NodeManager;
    };
}
