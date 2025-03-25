#pragma once
#include <iostream>
#include <string>
#define interface struct

interface Engine{
private:
	std::string name;

protected:
	Engine(std::string name) : name(name) {}

public:
	std::string getName() const {
		return name;
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
inline Engine* makeEngine(std::string name) {
	if (name == "Gm") return new Gm();
	if (name == "Toyota") return new Toyota();
	if (name == "Wia") return new Wia();
	return nullptr;
}