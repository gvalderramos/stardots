/**
 * @file node.h
 * @brief Defines the Node class, which represents a node in the Stardots framework.
 * 
 * @author 
 * Gabriel Valderramos
 * @date 
 * 2024-02-04
 */
#pragma once

#include <vector>
#include <memory>
#include <string>
#include <map>

#include "plug.h"


namespace stardots::core {
/**
 * @class Node
 * @brief Represents a node in the Stardots framework, managing input and output plugs.
 * 
 * The Node class provides mechanisms to define, manage, and interact with a node's
 * input and output plugs, supporting extensible data types through templates. It is
 * a key component within the Stardots framework.
 */
class NodeManager;
class Node {

public:
    /**
     * @brief Destroys the Node object, cleaning up allocated resources.
     */
    ~Node();

    /**
     * @typedef PlugIter
     * @brief An iterator type for navigating through the node's plugs.
     */
    typedef std::vector<IPlug*>::iterator PlugIter;

    /**
     * @brief Returns an iterator to the beginning of the input plugs.
     * @return PlugIter pointing to the first input plug.
     */
    PlugIter inBegin();
    /**
     * @brief Returns an iterator to the end of the input plugs.
     * @return PlugIter pointing one past the last input plug.
     */
    PlugIter inEnd();
    /**
     * @brief Returns an iterator to the beginning of the output plugs.
     * @return PlugIter pointing to the first output plug.
     */
    PlugIter outBegin();
    /**
     * @brief Returns an iterator to the end of the output plugs.
     * @return PlugIter pointing one past the last output plug.
     */
    PlugIter outEnd();

    /**
     * @brief Adds an input plug to the node.
     * 
     * @tparam T The type of the data the plug will hold.
     * @param value The initial value of the plug.
     * @param name The name of the plug.
     * @return A pointer to the created input plug.
     */
    template<typename T>
    IPlug* addInputPlug(const T& value, const std::string& name) {
        IPlug* plug;
        plug = new Plug<T>(value, name);
        plug->node(this);
        m_plugs[PlugDesc::INPUT].push_back(plug);
        return plug;
    }

    /**
     * @brief Adds an output plug to the node.
     * 
     * @tparam T The type of the data the plug will hold.
     * @param value The initial value of the plug.
     * @param name The name of the plug.
     * @return A pointer to the created output plug.
     */
    template<typename T>
    IPlug* addOutputPlug(const T& value, const std::string& name) {
        auto* plug = new Plug<T>(value, name);
        plug->node(this);
        m_plugs[PlugDesc::OUTPUT].push_back(plug);
        return plug;
    }

    /**
     * @brief Gets the count of connected input plugs.
     * @return The number of connected input plugs.
     */
    std::size_t connectedInputs() const;

    /**
     * @brief Gets the count of connected output plugs.
     * @return The number of connected output plugs.
     */
    std::size_t connectedOutputs() const;

    /**
     * @brief Gets the name of the node.
     * @return The name of the node as a string.
     */
    inline std::string name() const {return m_name;};
    /**
     * @brief Sets the name of the node.
     * @param name The new name for the node.
     */
    inline void name(const std::string& name) {m_name = name;};
private:
    /**
     * @brief Constructs a new Node object. Private to enforce controlled instantiation.
     */
    Node();

    /**
     * @enum PlugDesc
     * @brief Describes the type of plug (input or output).
     */
    enum class PlugDesc {
        OUTPUT = 0,
        INPUT
    };

    /**
     * @brief A map managing the node's input and output plugs.
     */
    std::map<PlugDesc, std::vector<IPlug*>> m_plugs;

    /**
     * @brief The name of the node.
     */
    std::string m_name;

    /**
     * @brief Allows NodeManager to access private members of Node.
     */
    friend class NodeManager;
};
}
