#include <boost/asio.hpp>
#include "request_handler.h"

class Listener {
    boost::asio::ip::udp::socket socket;
    boost::asio::ip::udp::endpoint endpoint;
    RequestHandler& requestHandler;

public:
    // �����ڿ��� socket�� requestHandler�� �ʱ�ȭ
    Listener(boost::asio::io_context& io_context, unsigned short port, RequestHandler& requestHandler)
        : socket(io_context, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port)), requestHandler(requestHandler) {
    }

    void startListening();  // ������ ���� �޼ҵ�
};

void listener_thread();  // listener_thread�� ������ ������� ����� �Լ�