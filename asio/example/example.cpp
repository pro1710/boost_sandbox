#include <iostream>
#include <chrono>

#define ASIO_STANDALONE

#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

std::vector<char> vBuff(20 * 1024);

void grabSomeData(asio::ip::tcp::socket& socket) {
    socket.async_read_some(asio::buffer(vBuff.data(), vBuff.size()),
        [&](std::error_code ec, std::size_t len) {
            if (!ec) {
                std::cout << "\n\nRead " << len << " bytes\n\n";
                
                for (int i = 0; i < len; ++i) {
                    std::cout << vBuff[i];
                }

                grabSomeData(socket);
            } else {
                std::cout << "\n\nEC: " << ec.message() << std::endl;
            }
        }
    );
}

int main () {

    asio::error_code ec;

    asio::io_context context;

    asio::io_context::work idleWork(context);

    std::thread threadContext = std::thread(
        [&]() {
            context.run();
        }
    );

    asio::ip::tcp::endpoint ep(asio::ip::make_address("51.38.81.49", ec), 80);

    asio::ip::tcp::socket socket(context);

    socket.connect(ep, ec);

    if (!ec) {
        std::cout << "Connected!" << std::endl;
    } else {
        std::cout << "Failed to connect:\n" << ec.message() << std::endl; 
    }

    if (socket.is_open()) {

        grabSomeData(socket);

        std::string sReq = 
        "GET /index.html HTTP/1.1\r\n"
        "Host: example.com\r\n"
        "Connection: close\r\n\r\n";

        socket.write_some(asio::buffer(sReq.data(), sReq.size()), ec);

        using namespace std::chrono_literals;
        std::this_thread::sleep_for(2000ms);

        
    }

    return 0;

}