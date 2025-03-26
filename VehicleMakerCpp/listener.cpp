#include "listener.h"

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

            // 잘못된 요청
			if (request.getOption() == TestOption::NONE) {
				continue;
			}

            // 비즈니스 로직 수행
            Result result = requestHandler.handle(request);
			std::string response = std::to_string(static_cast<int>(result));

            // 응답 송신
            boost::asio::write(socket, boost::asio::buffer(response), ec);
            while (ec) {
                boost::asio::write(socket, boost::asio::buffer(response), ec); // 재시도
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
