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
			std::cout << "�ڵ��� �׽�Ʈ ��� : FAIL\n";
			std::cout << "Sedan�� Continental ������ġ�� �� �� �����ϴ�\n";
			return Result::Fail_Sedan_Continental;
		}
		else if (vehicle != nullptr && vehicle->getVehicleType() == "Suv" && vehicle->getEngineName() == "Toyota") {
			std::cout << "�ڵ��� �׽�Ʈ ��� : FAIL\n";
			std::cout << "SUV�� ����Ÿ ������ �� �� �����ϴ�.\n";
			return Result::Fail_SUV_Toyota;
		}
		else if (vehicle != nullptr && vehicle->getVehicleType() == "Truck" && vehicle->getEngineName() == "Wia") {
			std::cout << "�ڵ��� �׽�Ʈ ��� : FAIL\n";
			std::cout << "Truck�� WIA ������ �� �� �����ϴ�.\n";
			return Result::Fail_Truck_WIA;
		}
		else if (vehicle != nullptr && vehicle->getVehicleType() == "Truck" && vehicle->getBreakSystemName() == "Mando") {
			std::cout << "�ڵ��� �׽�Ʈ ��� : FAIL\n";
			std::cout << "Truck�� MANDO ������ġ�� �� �� �����ϴ�.\n";
			return Result::Fail_Truck_Mando;
		}
		else if (vehicle != nullptr && vehicle->getBreakSystemName() == "Bosch" && vehicle->getSteeringSystemName() != "Bosch") {
			std::cout << "�ڵ��� �׽�Ʈ ��� : FAIL\n";
			std::cout << "������ġ�� Bosch ��ǰ�� ��ٸ�, ������ġ�� Bosch ��ǰ�� ����մϴ�.\n";
			return Result::Fail_BoschBrake_NoBoschSteering;
		}
		else if (vehicle != nullptr && vehicle->getBreakSystemName() != "Bosch" && vehicle->getSteeringSystemName() == "Bosch") {
			std::cout << "�ڵ��� �׽�Ʈ ��� : FAIL\n";
			std::cout << "������ġ�� Bosch ��ǰ�� ��ٸ�, ������ġ�� Bosch ��ǰ�� ����մϴ�.\n";
			return Result::Fail_BoschSteering_NoBoschBrake;
		}

		std::cout << "�ڵ��� �׽�Ʈ ��� : PASS\n";
		return Result::Success_Test;
	}
};