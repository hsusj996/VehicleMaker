#pragma once
#include <iostream>
#include <string>
#define interface struct

interface SteeringSystem{
private:
	std::string name;

protected:
	SteeringSystem(std::string name) : name(name) {}

public:
	std::string getName() const {
		return name;
	}
};

class BoschSteering : public SteeringSystem {
public:
	BoschSteering() : SteeringSystem("Bosch") {}
};

class Mobis : public SteeringSystem {
public:
	Mobis() : SteeringSystem("Mobis") {}
};

// factory pattern
class SteeringSystemFactory {
public:
	static SteeringSystem* makeSteeringSystem(std::string name) {
		if (name == "Bosch") return new BoschSteering();
		if (name == "Mobis") return new Mobis();
		return nullptr;
	}
};