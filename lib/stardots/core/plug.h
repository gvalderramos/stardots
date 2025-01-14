/**
 * @file plug.h
 * @brief Defines the IPlug and Plug classes, representing the base and templated plug types in the Stardots framework.
 * 
 * @author 
 * Gabriel Valderramos
 * @date 
 * 2024-02-04
 */

#pragma once

#include <memory>
#include <string>


namespace stardots::core {
/**
 * @class IPlug
 * @brief Abstract base class for all plug types in the Stardots framework.
 * 
 * The IPlug class provides a common interface for plug objects, representing
 * connections to and from nodes. It defines the type of plug and the essential
 * behaviors that derived plug types must implement.
 */
class Node;

class IPlug {
protected:
    /**
     * @brief The type of the plug as a string.
     */
    std::string m_type;
public:
    /**
     * @brief Default constructor is deleted to enforce specific instantiation.
     */
    IPlug() = delete;
    /**
     * @brief Copy constructors are deleted to prevent unintended duplication.
     */
    IPlug(const IPlug&) = delete;
    /**
     * @brief Virtual destructor for safe polymorphic usage.
     */
    IPlug(IPlug&) = delete;
    
    /**
     * @brief Virtual destructor for safe polymorphic usage.
     */
    virtual ~IPlug() {};
    /**
     * @brief Constructs an IPlug with a specified type name.
     * 
     * @param typeName The name of the plug's type.
     */
    explicit IPlug(const std::string& typeName) : m_type(typeName) {}
    /**
     * @brief Retrieves the type of the plug.
     * 
     * @return The type of the plug as a string.
     */
    [[nodiscard]] std::string plugType() const {return m_type;};

    /**
     * @brief Checks if the plug is connected to another plug.
     * 
     * @return True if the plug is connected; otherwise, false.
     */
    virtual bool isConnected() const = 0;

    /**
     * @brief Retrieves the node associated with this plug.
     * 
     * @return A pointer to the associated Node.
     */
    virtual Node* node() = 0;
    /**
     * @brief Associates the plug with a node.
     * 
     * @param n Pointer to the Node to associate with the plug.
     */
    virtual void node(Node* n) = 0;
};

/**
 * @class Plug
 * @brief Templated plug type that holds a value of a specific type and provides connections.
 * 
 * The Plug class extends the IPlug class to include specific data types through templates.
 * It manages connections to other plugs and holds a value that can be propagated through the connection.
 * 
 * @tparam T The data type the plug holds.
 */
template<typename T>
class Plug : public IPlug {
private:
    /**
     * @brief Pointer to the node associated with this plug.
     */
    Node* m_node;
    /**
     * @brief Pointer to the next plug in the connection.
     */
    Plug<T>* m_next;

    /**
     * @brief The value held by this plug.
     */
    T m_value;
    /**
     * @brief The name of the plug.
     */
    std::string m_name;
public:
    /**
     * @brief Constructs a Plug object with a value and a name.
     * 
     * @param value The initial value for the plug.
     * @param name The name of the plug.
     */
    Plug(const T& value, const std::string& name)
            : IPlug(typeid(T).name()), m_node(nullptr), m_value(value), m_name(name), m_next(nullptr) {};
    /**
     * @brief Destroys the Plug object.
     */
    ~Plug() override { };

    /**
     * @brief Retrieves the name of the plug.
     * 
     * @return The name of the plug as a string.
     */
    [[nodiscard]] inline std::string name() const {return m_name; };

    /**
     * @brief Sets the value of the plug. Propagates the value if connected.
     * 
     * @param v The new value to set.
     */
    inline void value(const T& v) {
        if(isConnected()) {
            m_next->m_value = v;
            m_value = v;
        } else {
            m_value = v;
        }
    };
    /**
     * @brief Retrieves the value of the plug.
     * 
     * @return The current value held by the plug.
     */
    inline T value() const {return m_value; };

    /**
     * @brief Prevents assignment of Plug values.
     */
    Plug<T>& operator=(const T& value) = delete;
    /**
     * @brief Prevents assignment of another Plug instance.
     */
    Plug<T>& operator=(const Plug<T>& other) = delete;

    /**
     * @brief Retrieves the next plug in the connection.
     * 
     * @return A pointer to the next Plug object.
     */
    Plug<T>* next() const {return m_next; };
    /**
     * @brief Sets the next plug in the connection and links back to this plug.
     * 
     * @param next Pointer to the next Plug object.
     */
    void next(Plug<T>* next) {
        m_next = next;
        next->m_next = this;
    };

    /**
     * @brief Retrieves the associated node.
     * 
     * @return A pointer to the Node object associated with this plug.
     */
    Node* node() override {return m_node;};
    /**
     * @brief Sets the associated node for the plug.
     * 
     * @param n Pointer to the Node to associate with this plug.
     */
    void node(Node* n) override {m_node = n;};
    /**
     * @brief Checks if the plug is connected to another plug.
     * 
     * @return True if the plug is connected; otherwise, false.
     */
    bool isConnected() const override { if (m_next) return true; return false; };
};
} // stardots::core
