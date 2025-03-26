#include "request_handler.h"


// ��û ó�� �޼ҵ� ����  
Result RequestHandler::handle(request_dto request) {
    Result ret;

    TestOption option = static_cast<TestOption>(request.getOption());
    VehicleDTO vehicle_dto = request.getVehicleDTO();

    Vehicle* vehicle = VehicleFactory::makeVehicle(vehicle_dto.getVehicleType());
    Assembler::getInstance().assembleEngine(vehicle, vehicle_dto.getEngineName());
    Assembler::getInstance().assembleBreakSystem(vehicle, vehicle_dto.getBreakSystemName());
    Assembler::getInstance().assembleSteeringSystem(vehicle, vehicle_dto.getSteeringSystemName());

    switch (option) {
    case TestOption::RUN:
        std::cout << "���� RUN" << std::endl;
        ret = vehicle->run() ? Result::Success_Run : Result::Fail_EngineBroken;
        break;
    case TestOption::TEST:
        std::cout << "���� �׽�Ʈ" << std::endl;
        /*
          TODO: ����Ͻ� ���� ����
        */
        ret = Result::Success_Test; // �׽�Ʈ �ڵ� 8 ��ȯ
        break;
    default:
        ret = Result::Fail_EngineBroken;  // �׽�Ʈ �ڵ� 0 ��ȯ
        break;
    }
    return ret;
}