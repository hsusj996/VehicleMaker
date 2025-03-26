#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <boost/asio.hpp>
#include "request_handler.h"
#include "listener.h"
#include "vehicle.cpp"
#include "assembler.cpp"

const std::string CLEAR_SCREEN = "\033[H\033[2J";
using std::cout;
using std::cin;

// Todo: enum class
enum QuesionType {
	VehicleType_Q,
	Engine_Q,
	BreakSystem_Q,
	SteeringSystem_Q,
	Run_Test,
};

void printVehicleTypeQ() {
	cout << CLEAR_SCREEN;
	cout << "        ______________\n";
	cout << "       /|            | \n";
	cout << "  ____/_|_____________|____\n";
	cout << " |                      O  |\n";
	cout << " '-(@)----------------(@)--'\n";
	cout << "===============================\n";
	cout << "� ���� Ÿ���� �����ұ��?\n";
	cout << "1. Sedan\n";
	cout << "2. SUV\n";
	cout << "3. Truck\n";
}

void printEngineQ() {
	cout << CLEAR_SCREEN;
	cout << "� ������ ž���ұ��?\n";
	cout << "0. �ڷΰ���\n";
	cout << "1. GM\n";
	cout << "2. TOYOTA\n";
	cout << "3. WIA\n";
	cout << "4. ���峭 ����\n";
}

void printBreakSystemQ() {
	cout << CLEAR_SCREEN;
	cout << "� ������ġ�� �����ұ��?\n";
	cout << "0. �ڷΰ���\n";
	cout << "1. MANDO\n";
	cout << "2. CONTINENTAL\n";
	cout << "3. BOSCH\n";
}

void printSteeringSystemQ() {
	cout << CLEAR_SCREEN;
	cout << "� ������ġ�� �����ұ��?\n";
	cout << "0. �ڷΰ���\n";
	cout << "1. BOSCH\n";
	cout << "2. MOBIS\n";
}

void printRunTest() {
	cout << CLEAR_SCREEN;
	cout << "���� ������ �ϼ��Ǿ����ϴ�.\n";
	cout << "� ������ �ұ��?\n";
	cout << "0. ó�� ȭ������ ���ư���\n";
	cout << "1. RUN\n";
	cout << "2. Test\n";
}

void printLine() {
	cout << "===============================\n";
}

Vehicle* selectVehicleType(int answer) {
	std::string vehicleType;

	if (answer == 1) vehicleType = "Sedan";
	else if (answer == 2) vehicleType = "Suv";
	else if (answer == 3) vehicleType = "Truck";
	// Todo: exception handling
	else return nullptr;

	std::cout << "���� Ÿ������ " << vehicleType << "�� �����ϼ̽��ϴ�.\n";

	return VehicleFactory::makeVehicle(vehicleType);
}

void selectEngine(Vehicle* vehicle, int answer) {
	if (answer == 1) Assembler::getInstance().assembleEngine(vehicle, "Gm");
	if (answer == 2) Assembler::getInstance().assembleEngine(vehicle, "Toyota");
	if (answer == 3) Assembler::getInstance().assembleEngine(vehicle, "Wia");

	// Todo: exception handling
	std::cout << vehicle->getEngineName() << " ������ �����ϼ̽��ϴ�.\n";
}

void selectBreakSystem(Vehicle* vehicle, int answer) {
	if (answer == 1) Assembler::getInstance().assembleBreakSystem(vehicle, "Mando");
	if (answer == 2) Assembler::getInstance().assembleBreakSystem(vehicle, "Continental");
	if (answer == 3) Assembler::getInstance().assembleBreakSystem(vehicle, "Bosch");

	// Todo: exception handling
	std::cout << vehicle->getBreakSystemName() << " ������ġ�� �����ϼ̽��ϴ�.\n";
}

void selectSteeringSystem(Vehicle* vehicle, int answer) {
	if (answer == 1) Assembler::getInstance().assembleSteeringSystem(vehicle, "Bosch");
	if (answer == 2) Assembler::getInstance().assembleSteeringSystem(vehicle, "Mobis");

	// Todo: exception handling
	std::cout << vehicle->getSteeringSystemName() << " ������ġ�� �����ϼ̽��ϴ�.\n";
}

int main() {
	std::string buf;

	boost::asio::io_context io_context;
	RequestHandler requestHandler;
	int port = 8080;
	std::thread t{ listener_thread, std::ref(io_context), std::ref(requestHandler), port };

	// Todo: smart pointer
	Vehicle* vehicle = nullptr;
	int step = VehicleType_Q;

	while (true) {
		switch (step) {
		case VehicleType_Q:
			printVehicleTypeQ();
			break;
		case Engine_Q:
			printEngineQ();
			break;
		case BreakSystem_Q:
			printBreakSystemQ();
			break;
		case SteeringSystem_Q:
			printSteeringSystemQ();
			break;
		case Run_Test:
			printRunTest();
			break;
		default:
			break;
		}

		printLine();

		cout << "INPUT > ";
		cin >> buf;

		if (buf == "exit") {
			cout << "���̹���\n";
			break;
		}

		// Todo: error handling
		int answer = std::stoi(buf);

		//ó������ ���ư���
		if (answer == 0 && step == Run_Test) {
			step = VehicleType_Q;
			continue;
		}

		//�������� ���ư���
		if (answer == 0 && step >= 1) {
			step -= 1;
			continue;
		}

		if (step == VehicleType_Q) {
			vehicle = selectVehicleType(answer);
			std::this_thread::sleep_for(std::chrono::milliseconds(800));
			step = Engine_Q;
		}
		else if (step == Engine_Q) {
			selectEngine(vehicle, answer);
			std::this_thread::sleep_for(std::chrono::milliseconds(800));
			step = BreakSystem_Q;
		}
		else if (step == BreakSystem_Q) {
			selectBreakSystem(vehicle, answer);
			std::this_thread::sleep_for(std::chrono::milliseconds(800));
			step = SteeringSystem_Q;
		}
		else if (step == SteeringSystem_Q) {
			selectSteeringSystem(vehicle, answer);
			std::this_thread::sleep_for(std::chrono::milliseconds(800));
			step = Run_Test;
		}
		else if (step == Run_Test && answer == 1) {
			// Todo: nullptr exception handling
			vehicle->run();
			std::this_thread::sleep_for(std::chrono::milliseconds(800));
		}
		else if (step == Run_Test && answer == 2) {
			// Todo: test car
			std::this_thread::sleep_for(std::chrono::milliseconds(800));
		}
	}
}