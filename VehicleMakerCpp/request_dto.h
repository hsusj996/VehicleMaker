#pragma once
#include <nlohmann/json.hpp>
#include "vehicle.h"  // Vehicle Ŭ���� ������� ����

class request_dto {
private:
    int option;
    Vehicle vehicle;

public:
    // ������ ����
    request_dto(int option, Vehicle vehicle);

    // getter �޼ҵ� ����
    int getOption();
    Vehicle getVehicle();

    // static from_json �޼ҵ� ����
    static request_dto from_json(const nlohmann::json& j);
};