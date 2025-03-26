#pragma once
#include <iostream>
#include <string>
#define interface struct

interface Engine{
private:
	bool broken;
	std::string name;

public:
	Engine(std::string name, bool broken = false) : name(name), broken(broken) {}

	std::string getName() const {
		return name;
	}

	bool isBroken() const {
		return broken;
	}
};

class Gm : public Engine {
public:
	Gm() : Engine("Gm") {}
};

class Toyota : public Engine {
public:
	Toyota() : Engine("Toyota") {}
};

class Wia : public Engine {
public:
	Wia() : Engine("Wia") {}
};

// factory pattern
class EngineFactory {
public:
	static Engine* makeEngine(std::string name, bool broken) {
		if (name == "Gm") return new Gm();
		if (name == "Toyota") return new Toyota();
		if (name == "Wia") return new Wia();
		if (broken) return new Engine(name, true);
		return nullptr;
	}
};