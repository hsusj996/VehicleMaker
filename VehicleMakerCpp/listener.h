#include <boost/asio.hpp>
#include "request_handler.h"

class Listener {
    boost::asio::ip::udp::socket socket;
    boost::asio::ip::udp::endpoint endpoint;
    RequestHandler& requestHandler;

public:
    // 생성자에서 socket과 requestHandler를 초기화
    Listener(boost::asio::io_context& io_context, unsigned short port, RequestHandler& requestHandler)
        : socket(io_context, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port)), requestHandler(requestHandler) {
    }

    void startListening();  // 리스닝 시작 메소드
};

void listener_thread();  // listener_thread는 독립된 스레드로 실행될 함수