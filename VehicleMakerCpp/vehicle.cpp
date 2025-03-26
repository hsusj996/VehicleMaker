#pragma once
#include <iostream>
#include "engine.cpp"
#include "break_system.cpp"
#include "steering_system.cpp"
#define interface struct

interface Vehicle{
private:
	std::string vehicleType;
	Engine* engine;
	BreakSystem* breakSystem;
	SteeringSystem* steeringSystem;

protected:
	Vehicle(std::string vehicleType) : vehicleType(vehicleType), engine(nullptr), breakSystem(nullptr), steeringSystem(nullptr) {}

public:
	// Todo: getter nullptr exception handling
	std::string getVehicleType() {
		return vehicleType;
	}

	std::string getEngineName() {
		return engine->getName();
	}

	std::string getBreakSystemName() {
		return breakSystem->getName();
	}

	std::string getSteeringSystemName() {
		return steeringSystem->getName();
	}

	void setEngine(Engine* engine) {
		this->engine = engine;
	}

	void setBreakSystem(BreakSystem* breakSystem) {
		this->breakSystem = breakSystem;
	}

	void setSteeringSystem(SteeringSystem* steeringSystem) {
		this->steeringSystem = steeringSystem;
	}

	void run() {
		if (engine == nullptr) {
			std::cout << "엔진이 고장났습니다.\n";
			std::cout << "자동차가 움직이지 않습니다.\n";
		}
		else {
			std::cout << "자동차가 동작됩니다.\n";
		}
	}
};

class Sedan : public Vehicle {
public:
	Sedan() : Vehicle("Sedan") {}
};

class Suv : public Vehicle {
public:
	Suv() : Vehicle("Suv") {}
};

class Truck : public Vehicle {
public:
	Truck() : Vehicle("Truck") {}
};

// factory pattern
class VehicleFactory {
public:
	static Vehicle* makeVehicle(std::string name) {
		if (name == "Sedan") return new Sedan();
		if (name == "Suv") return new Suv();
		if (name == "Truck") return new Truck();
		return nullptr;
	}
};