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
//			// RequestDTO 파싱
//			request_dto request = request_dto::from_json(nlohmann::json::parse(data));
//			// 비즈니스 로직 수행
//			std::string result = requestHandler.handle(request);
//
//			// 응답 처리
//			int retry = 0;
//			socket.send_to(boost::asio::buffer(result), sender_endpoint, 0, ec);
//			while (ec && ++retry < 5) {
//				socket.send_to(boost::asio::buffer(result), sender_endpoint, 0, ec);
//			}
//		}
//	}
//	catch (const boost::system::system_error& e) {
//		// Boost 시스템 오류
//		// 쓰레드 재실행
//		std::cerr << e.what() << std::endl;
//		startListening();
//	}
//	catch (const std::exception& e) {
//		// 그 외의 오류
//		std::cerr << e.what() << std::endl;
//		// 쓰레드 재실행
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
            // 클라이언트 연결 대기
            acceptor.accept(socket);

            // 클라이언트 연결이 성립되면 데이터 수신
            boost::system::error_code ec;
            size_t length = socket.read_some(boost::asio::buffer(data, sizeof(data)), ec);

            if (ec) {
                std::cerr << "Error receiving data: " << ec.message() << std::endl;
                continue;
            }

            if (length == 0) {
                continue;
            }

            // 수신된 데이터를 JSON으로 파싱하여 request_dto 객체 생성
            std::string s = std::string(data, length);
            nlohmann::json json_request = nlohmann::json::parse(std::string(data, length));
            request_dto request = request_dto::from_json(json_request);

            // 비즈니스 로직 수행
            std::string result = requestHandler.handle(request);

            // 응답 송신
            boost::asio::write(socket, boost::asio::buffer("test"), ec);
            while (ec) {
                boost::asio::write(socket, boost::asio::buffer("test"), ec); // 재시도
            }

            socket.close(); // 응답 후 소켓 닫기
        }
    }
    catch (const boost::system::system_error& e) {
        // Boost 시스템 오류
        std::cerr << "System error: " << e.what() << std::endl;
        startListening();  // 오류 발생 시 재시작
    }
    catch (const std::exception& e) {
        // 그 외의 오류
        std::cerr << "Exception: " << e.what() << std::endl;
        startListening();  // 오류 발생 시 재시작
    }
}

void listener_thread(boost::asio::io_context& io_context, RequestHandler& requestHandler, int port) {
    Listener listener(io_context, port, requestHandler);
    listener.startListening();
}
