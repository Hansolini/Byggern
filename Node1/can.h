#ifndef CAN_H_
#define CAN_H_

typedef struct can_msg_t {
	int id;
	char* data;
	int length;
} Msg;

void can_init(int mode);
void can_transmit(Msg msg); 
char* can_receive();
int can_test();

#endif /* CAN_H_ */