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
        IPlug() = delete;
        IPlug(const IPlug&) = delete;
        IPlug(IPlug&) = delete;

        virtual ~IPlug() {};
        explicit IPlug(const std::string& typeName) : m_type(typeName) {}
        [[nodiscard]] std::string plugType() const {return m_type;};

//        [[nodiscard]] virtual std::shared_ptr<IPlug>& next() const = 0;
//        virtual void next(const std::shared_ptr<IPlug>& next) = 0;
        virtual bool isConnected() const = 0;

        virtual Node* node() = 0;
        virtual void node(Node* n) = 0;
    };

    template<typename T>
    class Plug : public IPlug {
    private:
        Node* m_node;
        Plug<T>* m_next;

        T m_value;
        std::string m_name;
    public:
        Plug(const T& value, const std::string& name)
                : IPlug(typeid(T).name()), m_node(nullptr), m_value(value), m_name(name), m_next(nullptr) {};
        ~Plug() override {
//            delete m_node;
//            delete m_next;
        };

        [[nodiscard]] inline std::string name() const {return m_name; };

        inline void value(const T& v) {
            if(isConnected()) {
                m_next->m_value = v;
                m_value = v;
            } else {
                m_value = v;
            }
        };
        inline T value() const {return m_value; };

        Plug<T>& operator=(const T& value) = delete;
        Plug<T>& operator=(const Plug<T>& other) = delete;

        Plug<T>* next() const {return m_next; };
        void next(Plug<T>* next) {
            m_next = next;
            next->m_next = this;
        };

        Node* node() override {return m_node;};
        void node(Node* n) override {m_node = n;};

        bool isConnected() const override { if (m_next) return true; return false; };
    };
} // stardots::core
