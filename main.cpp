#include "main.h" 
#include "MyZf.h"

int main (){
	signal(SIGINT, signal_handle);
	while(1){
		int z = MyZf();
		sleep(3);
	}
	return 0;
}

void signal_handle(int){
	std::cout << "Stopping..." << std::endl;
	exit(0);
}
