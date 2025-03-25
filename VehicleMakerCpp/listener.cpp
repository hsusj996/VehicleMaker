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

			// RequestDTO �Ľ�
			request_dto request = request_dto::from_json(nlohmann::json::parse(data));
			// ����Ͻ� ���� ����
			std::string result = requestHandler.handle(request);

			// ���� ó��
			int retry = 0;
			socket.send_to(boost::asio::buffer(result), sender_endpoint, 0, ec);
			while (ec && ++retry < 5) {
				socket.send_to(boost::asio::buffer(result), sender_endpoint, 0, ec);
			}
		}
	}
	catch (const boost::system::system_error& e) {
		// Boost �ý��� ����
		// ������ �����
		std::cerr << e.what() << std::endl;
		startListening();
	}
	catch (const std::exception& e) {
		// �� ���� ����
		std::cerr << e.what() << std::endl;
		// ������ �����
		startListening();
	}
}

void listener_thread(boost::asio::io_context& io_context, RequestHandler& requestHandler, int port) {
	Listener listener(io_context, port, requestHandler);
	listener.startListening();
}