#include "request_handler.h"


// 요청 처리 메소드 정의  
Result RequestHandler::handle(request_dto request) {  
  Result ret;  

  TestOption option = static_cast<TestOption>(request.getOption());  
  Vehicle vehicle = request.getVehicle();  

  switch (option) {  
  case TestOption::RUN:  
      std::cout << "차량 RUN" << std::endl;
      ret = vehicle.run() ? Result::Success_Run : Result::Fail_EngineBroken;
      break;  
  case TestOption::TEST:  
      std::cout << "차량 테스트" << std::endl;  
      /*
        TODO: 비즈니스 로직 포함
      */
      ret = Result::Success_Test; // 테스트 코드 8 반환
      break;  
  default:  
	  ret = Result::Fail_EngineBroken;  // 테스트 코드 0 반환
      break;  
  }  
  return ret;  
}