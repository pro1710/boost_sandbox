#pragma once

#include "net_common.h"
#include "net_message.h"
#include "net_tsqueue.h"

namespace net {
    template<typename T>
    class client_interface {
        public:

        client_interface() : m_socket(m_context) {
        }

        virtual ~client_interface() {
            Disconnect();
        }

        bool Connect(const std::string& host, const uint16_t port) {
            try {
                m_connection = std::make_unique<connection<T>>(); 
                asio::ip::tcp::resolver resolver(m_context);
                m_endpoints = resolver.resolve(host, std::to_string(port));
                m_connection->ConnectToServer(m_endpoints);
                thrContext = std::thread([this](){
                    m_context.run();
                });
                return true;
            } catch (std::exception& e) {
                std::cerr << "Client Exception: " << e.what() << std::endl;
            }
            return false;
        }

        bool Disconnect() {
            if (IsConnected()) {
                m_connection->Disconnect();
            }

            m_context.stop();

            if (thrContext.joinable()) {
                thrContext.join();
            }

            m_connection.release();

            return true;
        }

        bool IsConnected() {
            if (m_connection) {
                return m_connection->IsConnected();
            } else {
                return false;
            }
        }

        tsqueue<owned_message<T>>& Incomming() {
            return m_qMessagesIn;
        }

        protected:
        asio::io_context m_context;
        std::thread thrContext;
        asio::ip::tcp::socket m_socket;
        std::unique_ptr<connection<T>> m_connection;
        asio::ip::tcp::resolver::iterator m_endpoints;

        private:
        tsqueue<owned_message<T>> m_qMessagesIn;
    };
}