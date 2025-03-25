#pragma once
#include <iostream>
#include "vehicle.cpp"
#include "engine.cpp"
#include "break_system.cpp"
#include "steering_system.cpp"

class Assembler {
public:
	void selectEngine(Vehicle* vehicle, std::string name) {
		vehicle->setEngine(makeEngine(name));
	}

	void selectBreakSystem(Vehicle* vehicle, std::string name) {
		vehicle->setBreakSystem(makeBreakSystem(name));
	}

	void selectSteeringSystem(Vehicle* vehicle, std::string name) {
		vehicle->setSteeringSystem(makeSteeringSystem(name));
	}
};