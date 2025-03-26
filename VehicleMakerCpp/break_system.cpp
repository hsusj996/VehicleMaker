#pragma once
#include <iostream>
#include <string>
#define interface struct

interface BreakSystem{
private:
	std::string name;

protected:
	BreakSystem(std::string name) : name(name) {}

public:
	std::string getName() const {
		return name;
	}
};

class Mando : public BreakSystem {
public:
	Mando() : BreakSystem("Mando") {}
};

class Continental : public BreakSystem {
public:
	Continental() : BreakSystem("Continental") {}
};

class BoschBreak : public BreakSystem {
public:
	BoschBreak() : BreakSystem("Bosch") {}
};

// factory pattern
class BreakSystemFactory {
public:
	static BreakSystem* makeBreakSystem(std::string name) {
		if (name == "Mando") return new Mando();
		if (name == "Continental") return new Continental();
		if (name == "Bosch") return new BoschBreak();
		return nullptr;
	}
};