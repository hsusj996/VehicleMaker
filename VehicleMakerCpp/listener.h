#pragma once
#include <boost/asio.hpp>
#include <iostream>
#include <nlohmann/json.hpp>
#include "request_handler.h"
#include "request_dto.h"

class Listener {
    bool listen_flag = true;  // ������ �÷��� false�� ������ ����
    boost::asio::ip::tcp::acceptor acceptor;
    boost::asio::ip::tcp::socket socket;
    RequestHandler& requestHandler;

public:
    static const int max_length = 1024;

    // �����ڿ��� acceptor�� socket�� �ʱ�ȭ
    Listener(boost::asio::io_context& io_context, unsigned short port, RequestHandler& requestHandler)
        : acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
        socket(io_context), requestHandler(requestHandler) {
    }

    void startListening();  // ������ ���� �޼ҵ�
};

void listener_thread(boost::asio::io_context& io_context, RequestHandler& requestHandler, int port);  // listener_thread�� ������ ������� ����� �Լ�
