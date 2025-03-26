#pragma once
#include "result_code.h"
#include "request_dto.h"  
#include <iostream>  // �α� ��� �� �ʿ��� ��� �߰�  
#include <string>
#include "vehicle.cpp"  // Vehicle Ŭ������ ���ǵ� ��� ������ ����

class RequestHandler {
private:
    Vehicle vehicle;  // Vehicle ��ü

public:
    // ������ ����
    RequestHandler();

    // ��û�� ó���ϴ� �޼ҵ�
    Result handle(request_dto request);
};