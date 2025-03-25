#include "request_handler.h"
#include <iostream>  // 로그 출력 등 필요한 헤더 추가

RequestHandler::RequestHandler() {
    std::cout << "RequestHandler 객체 생성!" << std::endl;
}

// 요청 처리 메소드 정의
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