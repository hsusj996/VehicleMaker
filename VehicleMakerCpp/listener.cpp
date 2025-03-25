#include "listener.h"

void Listener::startListening() {
	char data[max_length];
	boost::asio::ip::udp::endpoint sender_endpoint;

	try {
		while (listen_flag) {
			boost::system::error_code ec;
			size_t length = socket.receive_from(boost::asio::buffer(data, sizeof(data)), sender_endpoint, 0, ec);

			if (ec) {
				std::cerr << "Error: " << ec.message() << std::endl;
				continue;
			}

			if (length > 0) {
				std::string response = requestHandler.handle(1);
				socket.send_to(boost::asio::buffer(response), sender_endpoint);
			}
			else {
				continue;
			}

			std::string response = requestHandler.handle(1);
			socket.send_to(boost::asio::buffer(response), sender_endpoint);
		}
	}
	catch (const boost::system::system_error& e) {
		// Boost 시스템 오류
		// 쓰레드 재실행
		std::cerr << e.what() << std::endl;
		startListening();
	}
	catch (const std::exception& e) {
		// 그 외의 오류
		std::cerr << e.what() << std::endl;
		// 쓰레드 재실행
		startListening();
	}
}

void listener_thread(boost::asio::io_context& io_context, RequestHandler& requestHandler, int port) {
	Listener listener(io_context, port, requestHandler);
	listener.startListening();
}