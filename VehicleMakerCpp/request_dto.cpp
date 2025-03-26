#include "request_dto.h"

// getter �޼ҵ� ����
TestOption request_dto::getOption() {
   return test_option;
}

Vehicle request_dto::getVehicle() {
   return vehicle;
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

	Vehicle* vehicle = VehicleFactory::makeVehicle(vehicle_json["CarType"]);
	Assembler::getInstance().assembleEngine(vehicle, vehicle_json["EngineType"]);
	Assembler::getInstance().assembleBreakSystem(vehicle, vehicle_json["BrakeSystem"]);
	Assembler::getInstance().assembleSteeringSystem(vehicle, vehicle_json["SteeringSystem"]);

	return request_dto(test_option, *vehicle);
}