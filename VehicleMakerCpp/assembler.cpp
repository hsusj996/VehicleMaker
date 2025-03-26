#pragma once
#include <iostream>
#include "vehicle.cpp"
#include "engine.cpp"
#include "break_system.cpp"
#include "steering_system.cpp"

// singleton
class Assembler {
private:
	Assembler() = default;
	Assembler(const Assembler& ref) = delete;
	Assembler& operator=(const Assembler& ref) = delete;

public:
	static Assembler& getInstance() {
		static Assembler assembler;
		return assembler;
	}

	void assembleEngine(Vehicle* vehicle, std::string name) {
		vehicle->setEngine(EngineFactory::makeEngine(name));
	}

	void assembleBreakSystem(Vehicle* vehicle, std::string name) {
		vehicle->setBreakSystem(BreakSystemFactory::makeBreakSystem(name));
	}

	void assembleSteeringSystem(Vehicle* vehicle, std::string name) {
		vehicle->setSteeringSystem(SteeringSystemFactory::makeSteeringSystem(name));
	}
};