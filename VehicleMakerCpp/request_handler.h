#pragma once
#include "result_code.h"
#include "request_dto.h"  
#include <iostream>  // 로그 출력 등 필요한 헤더 추가  
#include <string>
#include "vehicle.cpp"  // Vehicle 클래스가 정의된 헤더 파일을 포함

class RequestHandler {
private:
    Vehicle vehicle;  // Vehicle 객체

public:
    // 생성자 선언
    RequestHandler();

    // 요청을 처리하는 메소드
    Result handle(request_dto request);
};