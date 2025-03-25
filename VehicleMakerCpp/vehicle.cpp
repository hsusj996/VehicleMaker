#pragma once
#include <iostream>
#include "engine.cpp"
#include "break_system.cpp"
#include "steering_system.cpp"
#define interface struct

interface Vehicle{
public:
	std::string vehicleType;
	Engine* engine;
	BreakSystem* breakSystem;
	SteeringSystem* steeringSystem;

protected:
	Vehicle(std::string vehicleType) : vehicleType(vehicleType), engine(nullptr), breakSystem(nullptr), steeringSystem(nullptr) {}

public:
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
inline Vehicle* makeVehicle(std::string name) {
	if (name == "Sedan") return new Sedan();
	if (name == "Suv") return new Suv();
	if (name == "Truck") return new Truck();
	return nullptr;
}