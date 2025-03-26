#include "request_dto.h"

// 생성자 구현
request_dto::request_dto(TestOption test_option, Vehicle vehicle) : test_option(test_option), vehicle(vehicle) {}

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
	Vehicle vehicle = Vehicle(vehicle_json["CarType"]);
	vehicle.setBreakSystem(makeBreakSystem(vehicle_json["BrakeSystem"]));
	vehicle.setEngine(makeEngine(vehicle_json["EngineType"]));
	vehicle.setSteeringSystem(makeSteeringSystem(vehicle_json["SteeringSystem"]));
	return request_dto(test_option, vehicle);
}