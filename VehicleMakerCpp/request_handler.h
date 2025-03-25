#include <string>
#include "vehicle.h"  // Vehicle 클래스가 정의된 헤더 파일을 포함

class RequestHandler {
private:
    Vehicle vehicle;  // Vehicle 객체

public:
    // 생성자 선언
    RequestHandler();

    // 요청을 처리하는 메소드
    std::string handle(int option);
};