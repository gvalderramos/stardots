//
// Created by Gabriel Valderramos on 2/4/24.
//
#pragma once

#include <memory>
#include <string>


namespace stardots::core {
    class Node;

    class IPlug {
    protected:
        std::string m_type;
    public:
        virtual ~IPlug() = 0;
        explicit IPlug(const std::string& typeName) : m_type(typeName) {}
        [[nodiscard]] std::string plugType() const {return m_type;};

        [[nodiscard]] virtual std::shared_ptr<IPlug>& next() const = 0;
        virtual void next(const std::shared_ptr<IPlug>& next) = 0;
        virtual bool isConnected() const = 0;

        virtual std::shared_ptr<Node>& node() = 0;
    };

    template<typename T>
    class Plug : public IPlug {
    private:
        Plug() = delete;
        std::shared_ptr<Node> m_node;
        std::shared_ptr<Plug> m_next;

        T m_value;
        std::string m_name;
    public:
        Plug(const std::shared_ptr<Node>& node, const T& value, const std::string& name)
                : IPlug(typeid(T).name()), m_node(node), m_value(value), m_name(name) {};
        Plug(const Plug& other) {
            m_node = std::move(other.m_node);
            m_next = std::move(other.m_next);
            m_value = other.m_value;
            m_name = other.m_name;
            m_type = other.m_type;
        };
        ~Plug() {};

        [[nodiscard]] inline std::string name() const {return m_name; };

        inline void value(const T& v) {m_value = v; };
        inline T value() const {return m_value; };

        Plug& operator=(const T& value) {
            if(m_value != value)
                m_value = value;
            return *this;
        };
        Plug& operator=(const Plug& other) {
            return Plug(other);
        };

        [[nodiscard]] std::shared_ptr<Plug>& next() const override {return m_next; };
        void next(const std::shared_ptr<Plug>& next) override {m_next = next;};
        [[nodiscard]] bool isConnected() const override { if (m_next) return true; return false; };

        std::shared_ptr<Node>& node() override {return m_node;};
    };
} // core
// stardots
