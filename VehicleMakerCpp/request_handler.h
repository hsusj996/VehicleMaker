#pragma once
#include <string>
#include "vehicle.h"  // Vehicle Ŭ������ ���ǵ� ��� ������ ����
#include "request_dto.h"

class RequestHandler {
private:
    Vehicle vehicle;  // Vehicle ��ü

public:
    // ������ ����
    RequestHandler();

    // ��û�� ó���ϴ� �޼ҵ�
    std::string handle(request_dto request);
};