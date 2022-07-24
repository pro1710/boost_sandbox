#include <net.h>

enum class CustomMsgType : uint32_t {
    Text,
    Bye
};

class CustomClient : public net::client_interface<CustomMsgType> {
    public:
    bool Say(const std::string& text) {
        net::message<CustomMsgType> msg;
        msg.header.id = CustomMsgType::Text;
        msg << text;
        Send(msg);
    }
};

int main() {

    CustomClient c;
    c.Connect("examplee.com", 65000);
    c.Say("Hello");

    return 0;
}