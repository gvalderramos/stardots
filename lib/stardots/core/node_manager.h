/**
 * @file node_manager.h
 * @brief Defines the NodeManager class, which manages a collection of nodes in the Stardots framework.
 * 
 * @author Gabriel Valderramos
 * @date 2024-02-06
 */
#pragma once

#include "node.h"

#include <memory>
#include <vector>


namespace stardots::core {
/**
 * @class NodeManager
 * @brief Manages a collection of nodes, providing utilities to add, access, and query nodes.
 * 
 * The NodeManager class encapsulates a collection of nodes, allowing iteration,
 * access by index, and specialized queries for nodes with the least connected inputs
 * or outputs. This is part of the Stardots framework core.
 */
class NodeManager {
public:
    /**
     * @brief Constructs a new NodeManager object.
     */
    NodeManager();
    /**
     * @brief Destroys the NodeManager object and cleans up resources.
     */
    ~NodeManager();

    /**
     * @typedef NodeIterator
     * @brief An iterator type for the internal node collection.
     */
    typedef std::vector<std::shared_ptr<Node>>::iterator NodeIterator;
    
    /**
     * @brief Returns an iterator to the beginning of the node collection.
     * @return NodeIterator to the first node.
     */
    [[nodiscard]] NodeIterator begin();
    
    /**
     * @brief Returns an iterator to the end of the node collection.
     * @return NodeIterator to one past the last node.
     */
    [[nodiscard]] NodeIterator end();

    /**
     * @brief Accesses a node by its index.
     * 
     * @param index The index of the node to access.
     * @return A shared pointer to the node at the given index.
     * @throws std::out_of_range if the index is invalid.
     */
    std::shared_ptr<Node> operator[](const int& index) const;

    /**
     * @brief Adds a new node to the collection.
     * 
     * @return A shared pointer to the newly added node.
     */
    std::shared_ptr<Node> addNode();

    /**
     * @brief Finds the node with the fewest connected input connections.
     * 
     * @return A shared pointer to the node with the least connected inputs,
     *         or nullptr if the collection is empty.
     */
    std::shared_ptr<Node> getNodeWithLessConnectedInput() const;

    /**
     * @brief Finds the node with the fewest connected output connections.
     * 
     * @return A shared pointer to the node with the least connected outputs,
     *         or nullptr if the collection is empty.
     */
    std::shared_ptr<Node> getNodeWithLessConnectedOutput() const;

    /**
     * @brief Gets the number of nodes managed by this NodeManager.
     * 
     * @return The size of the node collection.
     */
    std::size_t size() const;

private:
    /**
     * @brief A collection of nodes managed by this NodeManager.
     */
    std::vector<std::shared_ptr<Node>> m_nodes;
};

} // core
// stardots
