#include "request_handler.h"


// 요청 처리 메소드 정의  
Result RequestHandler::handle(request_dto request) {
    Result ret;

    TestOption option = static_cast<TestOption>(request.getOption());

	// 차량 객체 생성 및 조립
    VehicleDTO vehicle_dto = request.getVehicleDTO();
    Vehicle* vehicle = VehicleFactory::makeVehicle(vehicle_dto.getVehicleType());
    Assembler::getInstance().assembleEngine(vehicle, vehicle_dto.getEngineName());
    Assembler::getInstance().assembleBreakSystem(vehicle, vehicle_dto.getBreakSystemName());
    Assembler::getInstance().assembleSteeringSystem(vehicle, vehicle_dto.getSteeringSystemName());

	// 요청 처리
    switch (option) {
    case TestOption::RUN:
        std::cout << "차량 RUN" << std::endl;
        ret = vehicle->run() ? Result::Success_Run : Result::Fail_EngineBroken;
        break;

    case TestOption::TEST:
        std::cout << "차량 테스트" << std::endl;
		ret = Tester::getInstance().test(vehicle);
        break;
    default:
        ret = Result::Fail_EngineBroken;  // 테스트 코드 0 반환
        break;
    }
    return ret;
}