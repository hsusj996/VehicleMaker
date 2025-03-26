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
    // 持失切 識情
    request_dto() = default;
    request_dto(TestOption test_option, VehicleDTO vehicle_dto) : test_option(test_option), vehicle_dto(vehicle_dto) {}

    // getter 五社球 識情
    TestOption getOption();
    VehicleDTO getVehicleDTO();

    // static from_json 五社球 識情
    static request_dto from_json(const nlohmann::json& j);
};