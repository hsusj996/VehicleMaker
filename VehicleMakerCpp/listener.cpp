#include "listener.h"
#include "request_dto.h"
#include <nlohmann/json.hpp>

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

			if (length == 0) {
				continue;
			}

			// RequestDTO 파싱
			request_dto request = request_dto::from_json(nlohmann::json::parse(data));
			// 비즈니스 로직 수행
			std::string result = requestHandler.handle(request);

			// 응답 처리
			int retry = 0;
			socket.send_to(boost::asio::buffer(result), sender_endpoint, 0, ec);
			while (ec && ++retry < 5) {
				socket.send_to(boost::asio::buffer(result), sender_endpoint, 0, ec);
			}
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