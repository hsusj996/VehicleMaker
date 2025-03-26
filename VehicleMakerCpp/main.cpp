#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <cstdint>
#include <boost/asio.hpp>
#include "request_handler.h"
#include "listener.h"
#include "vehicle.cpp"
#include "assembler.cpp"
#include "tester.cpp"

const std::string CLEAR_SCREEN = "\033[H\033[2J";
using std::cout;
using std::cin;

enum class QuesionType : uint8_t {
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
	else return nullptr;

	std::cout << "���� Ÿ������ " << vehicleType << "�� �����ϼ̽��ϴ�.\n";

	return VehicleFactory::makeVehicle(vehicleType);
}

void selectEngine(Vehicle* vehicle, int answer) {
	if (answer == 1) Assembler::getInstance().assembleEngine(vehicle, "Gm");
	if (answer == 2) Assembler::getInstance().assembleEngine(vehicle, "Toyota");
	if (answer == 3) Assembler::getInstance().assembleEngine(vehicle, "Wia");
	if (answer == 4) {
		Assembler::getInstance().assembleEngine(vehicle, "Engine", true);
		return;
	}

	std::cout << vehicle->getEngineName() << " ������ �����ϼ̽��ϴ�.\n";
}

void selectBreakSystem(Vehicle* vehicle, int answer) {
	if (answer == 1) Assembler::getInstance().assembleBreakSystem(vehicle, "Mando");
	if (answer == 2) Assembler::getInstance().assembleBreakSystem(vehicle, "Continental");
	if (answer == 3) Assembler::getInstance().assembleBreakSystem(vehicle, "Bosch");

	std::cout << vehicle->getBreakSystemName() << " ������ġ�� �����ϼ̽��ϴ�.\n";
}

void selectSteeringSystem(Vehicle* vehicle, int answer) {
	if (answer == 1) Assembler::getInstance().assembleSteeringSystem(vehicle, "Bosch");
	if (answer == 2) Assembler::getInstance().assembleSteeringSystem(vehicle, "Mobis");

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
	int step = static_cast<int>(QuesionType::VehicleType_Q);

	while (true) {
		switch (step) {
		case static_cast<int>(QuesionType::VehicleType_Q):
			printVehicleTypeQ();
			break;
		case static_cast<int>(QuesionType::Engine_Q):
			printEngineQ();
			break;
		case static_cast<int>(QuesionType::BreakSystem_Q):
			printBreakSystemQ();
			break;
		case static_cast<int>(QuesionType::SteeringSystem_Q):
			printSteeringSystemQ();
			break;
		case static_cast<int>(QuesionType::Run_Test):
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

		try {
			int answer = std::stoi(buf);

			if (step == static_cast<int>(QuesionType::VehicleType_Q) && !(answer >= 1 && answer <= 3))
				throw std::out_of_range("���� Ÿ���� 1 ~ 3 ������ ���� ����\n");

			if (step == static_cast<int>(QuesionType::Engine_Q) && !(answer >= 0 && answer <= 4))
				throw std::out_of_range("������ 1 ~ 4 ������ ���� ����\n");

			if (step == static_cast<int>(QuesionType::BreakSystem_Q) && !(answer >= 0 && answer <= 3))
				throw std::out_of_range("������ġ�� 1 ~ 3 ������ ���� ����\n");

			if (step == static_cast<int>(QuesionType::SteeringSystem_Q) && !(answer >= 0 && answer <= 2))
				throw std::out_of_range("������ġ�� 1 ~ 2 ������ ���� ����\n");

			if (step == static_cast<int>(QuesionType::Run_Test) && !(answer >= 0 && answer <= 2))
				throw std::out_of_range("Run �Ǵ� Test �� �ϳ��� ���� �ʿ�\n");

			//ó������ ���ư���
			if (answer == 0 && step == static_cast<int>(QuesionType::Run_Test)) {
				step = static_cast<int>(QuesionType::VehicleType_Q);
				continue;
			}

			//�������� ���ư���
			if (answer == 0 && step >= 1) {
				step -= 1;
				continue;
			}

			if (step == static_cast<int>(QuesionType::VehicleType_Q)) {
				vehicle = selectVehicleType(answer);
				std::this_thread::sleep_for(std::chrono::milliseconds(800));
				step = static_cast<int>(QuesionType::Engine_Q);
			}
			else if (step == static_cast<int>(QuesionType::Engine_Q)) {
				selectEngine(vehicle, answer);
				std::this_thread::sleep_for(std::chrono::milliseconds(800));
				step = static_cast<int>(QuesionType::BreakSystem_Q);
			}
			else if (step == static_cast<int>(QuesionType::BreakSystem_Q)) {
				selectBreakSystem(vehicle, answer);
				std::this_thread::sleep_for(std::chrono::milliseconds(800));
				step = static_cast<int>(QuesionType::SteeringSystem_Q);
			}
			else if (step == static_cast<int>(QuesionType::SteeringSystem_Q)) {
				selectSteeringSystem(vehicle, answer);
				std::this_thread::sleep_for(std::chrono::milliseconds(800));
				step = static_cast<int>(QuesionType::Run_Test);
			}
			else if (step == static_cast<int>(QuesionType::Run_Test) && answer == 1) {
				vehicle->run();
				std::this_thread::sleep_for(std::chrono::milliseconds(800));
			}
			else if (step == static_cast<int>(QuesionType::Run_Test) && answer == 2) {
				Tester::getInstance().test(vehicle);
				std::this_thread::sleep_for(std::chrono::milliseconds(800));
			}
		}
		catch (const std::invalid_argument& e) {
			std::cout << "ERROR :: ���ڸ� �Է� ����\n";
			std::this_thread::sleep_for(std::chrono::milliseconds(800));
		}
		catch (const std::out_of_range& e) {
			std::cout << "ERROR :: " << e.what();
			std::this_thread::sleep_for(std::chrono::milliseconds(800));
		}
		catch (const std::exception& e) {
			std::cout << "ERROR :: " << e.what() << '\n';
			std::this_thread::sleep_for(std::chrono::milliseconds(800));
		}
	}
}