#include "request_handler.h"


// ��û ó�� �޼ҵ� ����  
Result RequestHandler::handle(request_dto request) {
    Result ret;

    TestOption option = static_cast<TestOption>(request.getOption());

	// ���� ��ü ���� �� ����
    VehicleDTO vehicle_dto = request.getVehicleDTO();
    Vehicle* vehicle = VehicleFactory::makeVehicle(vehicle_dto.getVehicleType());
    Assembler::getInstance().assembleEngine(vehicle, vehicle_dto.getEngineName());
    Assembler::getInstance().assembleBreakSystem(vehicle, vehicle_dto.getBreakSystemName());
    Assembler::getInstance().assembleSteeringSystem(vehicle, vehicle_dto.getSteeringSystemName());

	// ��û ó��
    switch (option) {
    case TestOption::RUN:
        std::cout << "���� RUN" << std::endl;
        ret = vehicle->run() ? Result::Success_Run : Result::Fail_EngineBroken;
        break;

    case TestOption::TEST:
        std::cout << "���� �׽�Ʈ" << std::endl;
		ret = Tester::getInstance().test(vehicle);
        break;
    default:
        ret = Result::Fail_EngineBroken;  // �׽�Ʈ �ڵ� 0 ��ȯ
        break;
    }
    return ret;
}