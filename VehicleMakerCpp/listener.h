#pragma once
#include <boost/asio.hpp>
#include <iostream>
#include <nlohmann/json.hpp>
#include "request_handler.h"
#include "request_dto.h"

class Listener {
    bool listen_flag = true;  // 리스닝 플래그 false면 쓰레드 중지
    boost::asio::ip::tcp::acceptor acceptor;
    boost::asio::ip::tcp::socket socket;
    RequestHandler& requestHandler;

public:
    static const int max_length = 1024;

    // 생성자에서 acceptor와 socket을 초기화
    Listener(boost::asio::io_context& io_context, unsigned short port, RequestHandler& requestHandler)
        : acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
        socket(io_context), requestHandler(requestHandler) {
    }

    void startListening();  // 리스닝 시작 메소드
};

void listener_thread(boost::asio::io_context& io_context, RequestHandler& requestHandler, int port);  // listener_thread는 독립된 스레드로 실행될 함수
