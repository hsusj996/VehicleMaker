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
	cout << "어떤 차량 타입을 선택할까요?\n";
	cout << "1. Sedan\n";
	cout << "2. SUV\n";
	cout << "3. Truck\n";
}

void printEngineQ() {
	cout << CLEAR_SCREEN;
	cout << "어떤 엔진을 탑재할까요?\n";
	cout << "0. 뒤로가기\n";
	cout << "1. GM\n";
	cout << "2. TOYOTA\n";
	cout << "3. WIA\n";
	cout << "4. 고장난 엔진\n";
}

void printBreakSystemQ() {
	cout << CLEAR_SCREEN;
	cout << "어떤 제동장치를 선택할까요?\n";
	cout << "0. 뒤로가기\n";
	cout << "1. MANDO\n";
	cout << "2. CONTINENTAL\n";
	cout << "3. BOSCH\n";
}

void printSteeringSystemQ() {
	cout << CLEAR_SCREEN;
	cout << "어떤 조향장치를 선택할까요?\n";
	cout << "0. 뒤로가기\n";
	cout << "1. BOSCH\n";
	cout << "2. MOBIS\n";
}

void printRunTest() {
	cout << CLEAR_SCREEN;
	cout << "멋진 차량이 완성되었습니다.\n";
	cout << "어떤 동작을 할까요?\n";
	cout << "0. 처음 화면으로 돌아가기\n";
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

	std::cout << "차량 타입으로 " << vehicleType << "을 선택하셨습니다.\n";

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

	std::cout << vehicle->getEngineName() << " 엔진을 선택하셨습니다.\n";
}

void selectBreakSystem(Vehicle* vehicle, int answer) {
	if (answer == 1) Assembler::getInstance().assembleBreakSystem(vehicle, "Mando");
	if (answer == 2) Assembler::getInstance().assembleBreakSystem(vehicle, "Continental");
	if (answer == 3) Assembler::getInstance().assembleBreakSystem(vehicle, "Bosch");

	std::cout << vehicle->getBreakSystemName() << " 제동장치를 선택하셨습니다.\n";
}

void selectSteeringSystem(Vehicle* vehicle, int answer) {
	if (answer == 1) Assembler::getInstance().assembleSteeringSystem(vehicle, "Bosch");
	if (answer == 2) Assembler::getInstance().assembleSteeringSystem(vehicle, "Mobis");

	std::cout << vehicle->getSteeringSystemName() << " 조향장치를 선택하셨습니다.\n";
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
			cout << "바이바이\n";
			break;
		}

		try {
			int answer = std::stoi(buf);

			if (step == static_cast<int>(QuesionType::VehicleType_Q) && !(answer >= 1 && answer <= 3))
				throw std::out_of_range("차량 타입은 1 ~ 3 범위만 선택 가능\n");

			if (step == static_cast<int>(QuesionType::Engine_Q) && !(answer >= 0 && answer <= 4))
				throw std::out_of_range("엔진은 1 ~ 4 범위만 선택 가능\n");

			if (step == static_cast<int>(QuesionType::BreakSystem_Q) && !(answer >= 0 && answer <= 3))
				throw std::out_of_range("제동장치는 1 ~ 3 범위만 선택 가능\n");

			if (step == static_cast<int>(QuesionType::SteeringSystem_Q) && !(answer >= 0 && answer <= 2))
				throw std::out_of_range("조향장치는 1 ~ 2 범위만 선택 가능\n");

			if (step == static_cast<int>(QuesionType::Run_Test) && !(answer >= 0 && answer <= 2))
				throw std::out_of_range("Run 또는 Test 중 하나를 선택 필요\n");

			//처음으로 돌아가기
			if (answer == 0 && step == static_cast<int>(QuesionType::Run_Test)) {
				step = static_cast<int>(QuesionType::VehicleType_Q);
				continue;
			}

			//이전으로 돌아가기
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
			std::cout << "ERROR :: 숫자만 입력 가능\n";
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