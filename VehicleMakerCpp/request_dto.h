#pragma once
#include <nlohmann/json.hpp>
#include "vehicle.cpp"
#include "test_option.h"
#include "assembler.cpp"

class request_dto {
private:
    TestOption test_option;
    Vehicle vehicle;

public:
    // 持失切 識情
	request_dto() = default;
	request_dto(TestOption test_option, Vehicle vehicle) : test_option(test_option), vehicle(vehicle) {}

    // getter 五社球 識情
    TestOption getOption();
    Vehicle getVehicle();

    // static from_json 五社球 識情
    static request_dto from_json(const nlohmann::json& j);
};