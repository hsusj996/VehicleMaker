#include "request_handler.h"
#include <iostream>  // �α� ��� �� �ʿ��� ��� �߰�

RequestHandler::RequestHandler() {
    std::cout << "RequestHandler ��ü ����!" << std::endl;
}

// ��û ó�� �޼ҵ� ����
std::string RequestHandler::handle(int option) {
    std::string ret;
    switch (option) {
    case 1:
        ret = vehicle.testAPI();
        break;
    case 2:
        ret = "Option 2 is selected";
        break;
    default:
        ret = "Invalid option";
        break;
    }
    return ret;
}