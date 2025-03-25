#include "listener.h"

void Listener::startListening() {
    char data[1024];
    boost::asio::ip::udp::endpoint sender_endpoint;

    while (true) {
        size_t length = socket.receive_from(boost::asio::buffer(data, sizeof(data)), sender_endpoint);
        std::string response = requestHandler.handle(1);
        socket.send_to(boost::asio::buffer(response), sender_endpoint);
    }
}

void listener_thread() {
    boost::asio::io_context io_context;
    RequestHandler requestHandler;
    Listener listener(io_context, 8080, requestHandler);

    listener.startListening();
}