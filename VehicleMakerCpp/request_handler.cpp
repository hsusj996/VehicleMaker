#include "request_handler.h"
#include "test_option.h"

RequestHandler::RequestHandler() {  
  std::cout << "RequestHandler ��ü ����!" << std::endl;  
}  

// ��û ó�� �޼ҵ� ����  
Result RequestHandler::handle(request_dto request) {  
  Result ret;  

  TestOption option = static_cast<TestOption>(request.getOption());  
  Vehicle vehicle = request.getVehicle();  

  switch (option) {  
  case TestOption::RUN:  
      std::cout << "���� RUN" << std::endl;
      /*
        TODO: ����Ͻ� ���� ����
      */
      ret = Result::Success_Run;  // �׽�Ʈ �ڵ� 1 ��ȯ
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