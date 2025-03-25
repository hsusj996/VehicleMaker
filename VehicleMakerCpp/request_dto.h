#pragma once
#include <nlohmann/json.hpp>
#include "vehicle.h"  // Vehicle 클래스 헤더파일 포함

class request_dto {
private:
    int option;
    Vehicle vehicle;

public:
    // 생성자 선언
    request_dto(int option, Vehicle vehicle);

    // getter 메소드 선언
    int getOption();
    Vehicle getVehicle();

    // static from_json 메소드 선언
    static request_dto from_json(const nlohmann::json& j);
};