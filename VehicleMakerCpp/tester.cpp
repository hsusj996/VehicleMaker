#pragma once
#include <iostream>
#include "vehicle.cpp"
#include "result_code.h"

// singleton
class Tester {
private:
	Tester() = default;
	Tester(const Tester& ref) = delete;
	Tester& operator=(const Tester& ref) = delete;

public:
	static Tester& getInstance() {
		static Tester tester;
		return tester;
	}

	Result test(Vehicle* vehicle) {
		if (vehicle != nullptr && vehicle->getVehicleType() == "Sedan" && vehicle->getBreakSystemName() == "Continental") {
			std::cout << "자동차 테스트 결과 : FAIL\n";
			std::cout << "Sedan은 Continental 제동장치를 쓸 수 없습니다\n";
			return Result::Fail_Sedan_Continental;
		}
		else if (vehicle != nullptr && vehicle->getVehicleType() == "Suv" && vehicle->getEngineName() == "Toyota") {
			std::cout << "자동차 테스트 결과 : FAIL\n";
			std::cout << "SUV는 도요타 엔진을 쓸 수 없습니다.\n";
			return Result::Fail_SUV_Toyota;
		}
		else if (vehicle != nullptr && vehicle->getVehicleType() == "Truck" && vehicle->getEngineName() == "Wia") {
			std::cout << "자동차 테스트 결과 : FAIL\n";
			std::cout << "Truck은 WIA 엔진을 쓸 수 없습니다.\n";
			return Result::Fail_Truck_WIA;
		}
		else if (vehicle != nullptr && vehicle->getVehicleType() == "Truck" && vehicle->getBreakSystemName() == "Mando") {
			std::cout << "자동차 테스트 결과 : FAIL\n";
			std::cout << "Truck은 MANDO 제동장치를 쓸 수 없습니다.\n";
			return Result::Fail_Truck_Mando;
		}
		else if (vehicle != nullptr && vehicle->getBreakSystemName() == "Bosch" && vehicle->getSteeringSystemName() != "Bosch") {
			std::cout << "자동차 테스트 결과 : FAIL\n";
			std::cout << "제동장치에 Bosch 제품을 썼다면, 조향장치도 Bosch 제품을 써야합니다.\n";
			return Result::Fail_BoschBrake_NoBoschSteering;
		}
		else if (vehicle != nullptr && vehicle->getBreakSystemName() != "Bosch" && vehicle->getSteeringSystemName() == "Bosch") {
			std::cout << "자동차 테스트 결과 : FAIL\n";
			std::cout << "조향장치에 Bosch 제품을 썼다면, 제동장치도 Bosch 제품을 써야합니다.\n";
			return Result::Fail_BoschSteering_NoBoschBrake;
		}

		std::cout << "자동차 테스트 결과 : PASS\n";
		return Result::Success_Test;
	}
};