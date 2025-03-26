#include "request_handler.h"
#include "test_option.h"

RequestHandler::RequestHandler() {  
  std::cout << "RequestHandler 객체 생성!" << std::endl;  
}  

// 요청 처리 메소드 정의  
Result RequestHandler::handle(request_dto request) {  
  Result ret;  

  TestOption option = static_cast<TestOption>(request.getOption());  
  Vehicle vehicle = request.getVehicle();  

  switch (option) {  
  case TestOption::RUN:  
      std::cout << "차량 RUN" << std::endl;
      /*
        TODO: 비즈니스 로직 포함
      */
      ret = Result::Success_Run;  // 테스트 코드 1 반환
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