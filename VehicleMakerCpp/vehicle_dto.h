#pragma once
#include <string>
class VehicleDTO
{
private:
	std::string carType;
	std::string engineName;
	std::string breakSystemName;
	std::string steeringSystemName;

public:
	VehicleDTO(std::string vehicleType, std::string engineName, std::string breakSystemName, std::string steeringSystemName)
		: carType(vehicleType), engineName(engineName), breakSystemName(breakSystemName), steeringSystemName(steeringSystemName) {
	}
	std::string getVehicleType() {
		return carType;
	}
	std::string getEngineName() {
		return engineName;
	}
	std::string getBreakSystemName() {
		return breakSystemName;
	}
	std::string getSteeringSystemName() {
		return steeringSystemName;
	}
};