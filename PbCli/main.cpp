#include"person.pb.h"



int main() {
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	Person MSG;

	MSG.set_id(00);
	MSG.set_name("duan");

	int sz=MSG.ByteSize();
	void* bf=malloc(sz);
	std::string ss = MSG.SerializeAsString();
	MSG.Serial
	//MSG.Serialize


	//FILE* fp = fopen("pb.txt", "wb");



	return 0;
}