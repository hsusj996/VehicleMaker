#include "request_dto.h"
#include <nlohmann/json.hpp>  // JSON 파싱을 위한 헤더

// 생성자 구현
request_dto::request_dto(int option, Vehicle vehicle) : option(option), vehicle(vehicle) {}

// getter 메소드 구현
int request_dto::getOption() {
    return option;
}

Vehicle request_dto::getVehicle() {
    return vehicle;
}

// static from_json 메소드 구현
request_dto request_dto::from_json(const nlohmann::json& j) {
    return request_dto(
        j["option"],  // option 값을 가져옴
        Vehicle(j["vehicle"]["name"], j["vehicle"]["price"], j["vehicle"]["maxSpeed"])  // vehicle 객체 생성
    );
}