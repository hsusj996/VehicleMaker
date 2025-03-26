#include "request_dto.h"

// getter 메소드 구현
TestOption request_dto::getOption() {
   return test_option;
}

Vehicle request_dto::getVehicle() {
   return vehicle;
}

// static from_json 메소드 구현
request_dto request_dto::from_json(const nlohmann::json& j) {
	//TODO: 통합 후에 Vehicle 역직렬화 구현
	TestOption test_option = TestOption::NONE;
	if (j["Test"] == "Run") {
		test_option = TestOption::RUN;
	}

	if (j["Test"] == "Test") {
		test_option = TestOption::TEST;
	}

	nlohmann::json vehicle_json = j["Data"];

	Vehicle* vehicle = VehicleFactory::makeVehicle(vehicle_json["CarType"]);
	Assembler::getInstance().assembleEngine(vehicle, vehicle_json["EngineType"]);
	Assembler::getInstance().assembleBreakSystem(vehicle, vehicle_json["BrakeSystem"]);
	Assembler::getInstance().assembleSteeringSystem(vehicle, vehicle_json["SteeringSystem"]);

	return request_dto(test_option, *vehicle);
}