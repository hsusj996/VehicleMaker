#pragma once
#include <nlohmann/json.hpp>
#include "vehicle_dto.h"
#include "test_option.h"
#include "assembler.cpp"

class request_dto {
private:
    TestOption test_option;
    VehicleDTO vehicle_dto;

public:
    // ������ ����
    request_dto() = default;
    request_dto(TestOption test_option, VehicleDTO vehicle_dto) : test_option(test_option), vehicle_dto(vehicle_dto) {}

    // getter �޼ҵ� ����
    TestOption getOption();
    VehicleDTO getVehicleDTO();

    // static from_json �޼ҵ� ����
    static request_dto from_json(const nlohmann::json& j);
};