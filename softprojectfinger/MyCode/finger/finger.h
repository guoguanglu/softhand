#ifndef __FINGER_H
#define __FINGER_H
#include "sys.h"


extern int finger[5];

void Init_finger(void);
void finger_read(u8*buf);
void motorcontrol(void);
void all_switch(void);
void Scan_MPU6050(void);
void finger_pose(void);
#endif
