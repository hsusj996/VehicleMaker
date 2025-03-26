#pragma once
#include "assembler.cpp"
#include "result_code.h"
#include "request_dto.h"  
#include <iostream>  // �α� ��� �� �ʿ��� ��� �߰�  
#include <string>
#include "vehicle.cpp"  // Vehicle Ŭ������ ���ǵ� ��� ������ ����
#include "test_option.h"

class RequestHandler {
public:
    // ������ ����
    RequestHandler() = default;

    // ��û�� ó���ϴ� �޼ҵ�
    Result handle(request_dto request);
};