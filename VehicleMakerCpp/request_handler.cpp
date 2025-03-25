#include "request_handler.h"
#include "request_dto.h"
#include <iostream>  // 로그 출력 등 필요한 헤더 추가

RequestHandler::RequestHandler() {
    std::cout << "RequestHandler 객체 생성!" << std::endl;
}

// 요청 처리 메소드 정의
std::string RequestHandler::handle(request_dto request) {
    std::string ret;

	int option = request.getOption();
	Vehicle vehicle = request.getVehicle();
    switch (option) {
    case 1:
        std::cout << "차량 테스트" << std::endl;
        std::cout << vehicle.toString() << std::endl;
        break;
    case 2:
		std::cout << "차량 RUN" << std::endl;
		std::cout << vehicle.toString() << std::endl;
		break;
    default:
        ret = "Invalid option";
        break;
    }
    return ret;
}