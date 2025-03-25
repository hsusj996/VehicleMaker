#include "request_dto.h"
#include <nlohmann/json.hpp>  // JSON �Ľ��� ���� ���

// ������ ����
request_dto::request_dto(int option, Vehicle vehicle) : option(option), vehicle(vehicle) {}

// getter �޼ҵ� ����
int request_dto::getOption() {
    return option;
}

Vehicle request_dto::getVehicle() {
    return vehicle;
}

// static from_json �޼ҵ� ����
request_dto request_dto::from_json(const nlohmann::json& j) {
    return request_dto(
        j["option"],  // option ���� ������
        Vehicle(j["vehicle"]["name"], j["vehicle"]["price"], j["vehicle"]["maxSpeed"])  // vehicle ��ü ����
    );
}