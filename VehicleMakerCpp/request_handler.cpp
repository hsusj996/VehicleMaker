#include "request_handler.h"


// ��û ó�� �޼ҵ� ����  
Result RequestHandler::handle(request_dto request) {  
  Result ret;  

  TestOption option = static_cast<TestOption>(request.getOption());  
  Vehicle vehicle = request.getVehicle();  

  switch (option) {  
  case TestOption::RUN:  
      std::cout << "���� RUN" << std::endl;
      ret = vehicle.run() ? Result::Success_Run : Result::Fail_EngineBroken;
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