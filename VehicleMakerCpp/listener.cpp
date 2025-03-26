#include "listener.h"

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

            // �߸��� ��û
			if (request.getOption() == TestOption::NONE) {
				continue;
			}

            // ����Ͻ� ���� ����
            Result result = requestHandler.handle(request);
			std::string response = std::to_string(static_cast<int>(result));

            // ���� �۽�
            boost::asio::write(socket, boost::asio::buffer(response), ec);
            while (ec) {
                boost::asio::write(socket, boost::asio::buffer(response), ec); // ��õ�
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
