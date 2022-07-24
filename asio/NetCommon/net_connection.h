#pragma once

#include "net_common.h"
#include "net_message.h"
#include "net_tsqueue.h"

namespace net {
    template <typename T>
    class connection : public std::enabled_shared_from_this<connection<T>> {
        public:
        connection(){

        }

        virtual ~connection() {

        }

        public:
        bool ConnectToServer();
        bool Disconnect();
        bool IsConnected() const;
        bool Send(const message<T>& msg);

        protected:
        asio::ip::tcp::socket m_socket;
        asio::io_context& m_asioContext;

        tsqueue<message<T>> m_qMessageOut;
        tsqueue<message<T>> m_qMessageIn;
    };
}