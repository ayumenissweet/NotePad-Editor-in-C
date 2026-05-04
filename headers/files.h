#ifndef FILES_H
#define FILES_H

#include "types.h"  

Main_L all_null();
int save_file(Main_L* HTC, char file_path[260]);
Main_L charge_file(char file_path[260], int user_input);

#endif