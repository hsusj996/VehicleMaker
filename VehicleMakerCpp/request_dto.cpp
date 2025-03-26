#include "request_dto.h"

// getter �޼ҵ� ����
TestOption request_dto::getOption() {
	return test_option;
}

VehicleDTO request_dto::getVehicleDTO() {
	return vehicle_dto;
}

// static from_json �޼ҵ� ����
request_dto request_dto::from_json(const nlohmann::json& j) {
	//TODO: ���� �Ŀ� Vehicle ������ȭ ����
	TestOption test_option = TestOption::NONE;
	if (j["Test"] == "Run") {
		test_option = TestOption::RUN;
	}

	if (j["Test"] == "Test") {
		test_option = TestOption::TEST;
	}

	nlohmann::json vehicle_json = j["Data"];

	VehicleDTO vehicle_dto{ vehicle_json["CarType"], vehicle_json["EngineType"], vehicle_json["BrakeSystem"], vehicle_json["SteeringSystem"] };

	return request_dto(test_option, vehicle_dto);
}