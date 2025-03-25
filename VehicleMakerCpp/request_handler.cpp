#include "request_handler.h"
#include "request_dto.h"
#include <iostream>  // �α� ��� �� �ʿ��� ��� �߰�

RequestHandler::RequestHandler() {
    std::cout << "RequestHandler ��ü ����!" << std::endl;
}

// ��û ó�� �޼ҵ� ����
std::string RequestHandler::handle(request_dto request) {
    std::string ret;

	int option = request.getOption();
	Vehicle vehicle = request.getVehicle();
    switch (option) {
    case 1:
        std::cout << "���� �׽�Ʈ" << std::endl;
        std::cout << vehicle.toString() << std::endl;
        break;
    case 2:
		std::cout << "���� RUN" << std::endl;
		std::cout << vehicle.toString() << std::endl;
		break;
    default:
        ret = "Invalid option";
        break;
    }
    return ret;
}