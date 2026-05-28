#include <iostream>
#include <functional>
#include <string>

// Define a callback type
using MessageCallback = std::function<void(const std::string&)>;

class Messenger {
public:
    void setCallback(MessageCallback cb) {
        callback = cb;
    }

    void sendMessage(const std::string& msg) {
        std::cout << "Sending message...\n";

        // Invoke callback if it exists
        if (callback) {
            callback(msg);
        }
    }

private:
    MessageCallback callback;
};

int main() {
    Messenger messenger;

    // Assign a lambda as the callback
    messenger.setCallback([](const std::string& text) {
        std::cout << "First Callback received: " << text << std::endl;
    });

    messenger.sendMessage("Hello from C++!");

    messenger.setCallback([](const std::string& text) {
        std::cout << "Second Callback received: " << text << std::endl;
    });

    messenger.sendMessage("Hello from C++ Again!");

    return 0;
}

// MessageCallback can hold any function that accept the specified parameters
// in this way it is possible to assign at runtime the function to execute