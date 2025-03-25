//#include "listener.h"
//#include "request_dto.h"
//#include <nlohmann/json.hpp>
//
//void Listener::startListening() {
//	char data[max_length];
//	boost::asio::ip::udp::endpoint sender_endpoint;
//
//	try {
//		while (listen_flag) {
//			boost::system::error_code ec;
//			size_t length = socket.receive_from(boost::asio::buffer(data, sizeof(data)), sender_endpoint, 0, ec);
//
//			if (ec) {
//				std::cerr << "Error: " << ec.message() << std::endl;
//				continue;
//			}
//
//			if (length == 0) {
//				continue;
//			}
//
//			// RequestDTO �Ľ�
//			request_dto request = request_dto::from_json(nlohmann::json::parse(data));
//			// ����Ͻ� ���� ����
//			std::string result = requestHandler.handle(request);
//
//			// ���� ó��
//			int retry = 0;
//			socket.send_to(boost::asio::buffer(result), sender_endpoint, 0, ec);
//			while (ec && ++retry < 5) {
//				socket.send_to(boost::asio::buffer(result), sender_endpoint, 0, ec);
//			}
//		}
//	}
//	catch (const boost::system::system_error& e) {
//		// Boost �ý��� ����
//		// ������ �����
//		std::cerr << e.what() << std::endl;
//		startListening();
//	}
//	catch (const std::exception& e) {
//		// �� ���� ����
//		std::cerr << e.what() << std::endl;
//		// ������ �����
//		startListening();
//	}
//}
//
//void listener_thread(boost::asio::io_context& io_context, RequestHandler& requestHandler, int port) {
//	Listener listener(io_context, port, requestHandler);
//	listener.startListening();
//}

#include "listener.h"
#include "request_dto.h"
#include <iostream>
#include <boost/asio.hpp>
#include <nlohmann/json.hpp>

void Listener::startListening() {
    char data[max_length];

    try {
        while (listen_flag) {
            // Ŭ���̾�Ʈ ���� ���
            acceptor.accept(socket);

            // Ŭ���̾�Ʈ ������ �����Ǹ� ������ ����
            boost::system::error_code ec;
            size_t length = socket.read_some(boost::asio::buffer(data, sizeof(data)), ec);

            if (ec) {
                std::cerr << "Error receiving data: " << ec.message() << std::endl;
                continue;
            }

            if (length == 0) {
                continue;
            }

            // ���ŵ� �����͸� JSON���� �Ľ��Ͽ� request_dto ��ü ����
            std::string s = std::string(data, length);
            nlohmann::json json_request = nlohmann::json::parse(std::string(data, length));
            request_dto request = request_dto::from_json(json_request);

            // ����Ͻ� ���� ����
            std::string result = requestHandler.handle(request);

            // ���� �۽�
            boost::asio::write(socket, boost::asio::buffer("test"), ec);
            while (ec) {
                boost::asio::write(socket, boost::asio::buffer("test"), ec); // ��õ�
            }

            socket.close(); // ���� �� ���� �ݱ�
        }
    }
    catch (const boost::system::system_error& e) {
        // Boost �ý��� ����
        std::cerr << "System error: " << e.what() << std::endl;
        startListening();  // ���� �߻� �� �����
    }
    catch (const std::exception& e) {
        // �� ���� ����
        std::cerr << "Exception: " << e.what() << std::endl;
        startListening();  // ���� �߻� �� �����
    }
}

void listener_thread(boost::asio::io_context& io_context, RequestHandler& requestHandler, int port) {
    Listener listener(io_context, port, requestHandler);
    listener.startListening();
}
