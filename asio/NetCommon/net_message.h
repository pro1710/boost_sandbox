#pragma once

#include "net_common.h"

namespace net {
    template <typename T> 
    struct message_header {
        T id{};
        uint32_t size = 0;
    };

    template <typename T> 
    struct message {
        message_header<T> header{};
        std::vector<uint8_t> body;

        size_t size() const {
            return sizeof(message_header<T>) + body.size();
        }
   
        friend std::ostream& operator << (std::ostream& os, const message<T>& msg) {
            os << "ID:" << static_cast<int>(msg.header.id) 
            << " Size:" << msg.header.size;
            
            return os;
        }

        template <typename DataType>
        friend message<T>& operator << (message<T>& msg, const DataType& data) {
            static_assert(std::is_standard_layout<DataType>::value, "Data doesn't have a standart layout");

            size_t body_size = msg.body.size();

            msg.body.resize(msg.body.size() + sizeof(DataType)); 

            std::memcpy(msg.body.data() + body_size, &data, sizeof(DataType));

            msg.header.size = msg.size();

            return msg;
        }

        template <typename DataType>
        friend message<T>& operator >> (message<T>& msg, DataType& data) {
            static_assert(std::is_standard_layout<DataType>::value, "Data doesn't have a standart layout");

            size_t loc = msg.body.size() - sizeof(DataType);

            std::memcpy(&data, msg.body.data() + loc, sizeof(DataType));

            msg.body.resize(loc);

            msg.header.size = msg.size();

            return msg;
        }
    };
}
