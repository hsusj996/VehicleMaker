#include <string>
#include "vehicle.h"  // Vehicle Ŭ������ ���ǵ� ��� ������ ����

class RequestHandler {
private:
    Vehicle vehicle;  // Vehicle ��ü

public:
    // ������ ����
    RequestHandler();

    // ��û�� ó���ϴ� �޼ҵ�
    std::string handle(int option);
};