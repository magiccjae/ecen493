#ifndef MAIN_H
#define MAIN_H

    #include <project.h>
    #include <time.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include "wiznet5500.h"
    #include "spi.h"
    #include <cypins.h>
    #include "dynamixel.h"

    //Initializations of global variables
    #define ownIpAddr 4u
    #define dstIpAddr 1u //<-- This is the only number we need to change when we change the ip config. unless we change our subnet
    #define udpPort 27015u
   
    //TODO: make sure ourbyte scheme matching the newest version for udp format
    //Array indices of specific bytes transmitted from the wiznet
    #define BA_BYTE_1 10 
    #define BA_BYTE_2 11
    #define SHLDR_BYTE_1 12
    #define SHLDR_BYTE_2 13
    #define ELBW_BYTE_1 14
    #define ELBW_BYTE_2 15
    #define WT_BYTE_1 16
    #define WT_BYTE_2 17
    #define WR_BYTE_1 18
    #define WR_BYTE_2 19
    #define EFF_BYTE_1 20
    #define EFF_BYTE_2 21
    #define ARD_BYTE_1 22
    #define ARD_BYTE_2 23

    uint16 NEUTRAL = 1500;

    //TODO: Make sure that this data_array is the proper size for the newest version of udp format
    #define DATA_ARRAY_SIZE 24
    uint8 data_array[DATA_ARRAY_SIZE]; //stores the parsed instructions from the wiznet
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& from int8 to uint8
    #define FEEDBACK_ARRAY_SIZE 21
    #define HEARTBEAT_ARRAY_SIZE 3
    uint8_t feedback_array[FEEDBACK_ARRAY_SIZE];
    uint8_t heartbeat_array[HEARTBEAT_ARRAY_SIZE];
    uint8 HEARTBEAT_FLAG;

//    #define ELBW_ARR_SIZE 20
//    #define SHLDR_ARR_SIZE 20
//    #define BA_ARR_SIZE 20
//    #define WT_ARR_SIZE 20  //for wristTilt
//    #define WR_ARR_SIZE 20  //for wristRotate
    
    // execute flags
    uint8 WT_feedback_flag = 0;
    uint8 WR_feedback_flag = 0;
    uint16 WR_feedback = 0;//this is variable for storing feedback
    uint8 WT_FLAG = 0;
    uint8 WR_FLAG = 0;
    uint8 ELBOW_FLAG = 0;
    uint8 SHOULDER_FLAG = 0;
    uint8 BA_FLAG = 0;
    uint8 EFFECTOR_FLAG = 0;
    uint8 ARD_FLAG = 0;
    
    //these are for feedback path
    uint8 Time_Out_flag = 0;
    uint8 Time_count = 0;
    
    //error variables to send back to base station
    //uint16 dropped_packets = 0;
    uint8 fail_safe_errors = 0;
    uint8 shldr_errors = 0;
    uint8 elbw_errors = 0;
    uint8 BA_errors = 0;
    uint8 WT_errors = 0;
    uint8 WR_errors = 0;
    uint8 eff_errors = 0;

    volatile uint8 timerFlag; //used in the timer_isr
    
    enum equipment {SHOULDER = 0, ELBOW, WRIST, TURRET, EFFECTOR};
    
    //---------------------------------------------------
    //    Function stubs for the header
    //---------------------------------------------------
    uint16 simple_pos_to_vel(uint16 new_command, uint16 recent_command);
    uint16 latest_command;
    
    uint16 WR_pos_to_vel(uint16 new_command, uint16 recent_command);
    uint16 WT_pos_to_vel(uint16 new_command, uint16 recent_command);
    uint16 latest_WR_command;
    uint16 latest_WT_command;
    //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& from int8* to uint8*
    uint16 make_command(uint8* info_array, uint8 byte1, uint8 byte2);
    uint16 make_wristRotate_command(uint8* info_array, uint8 byte1, uint8 byte2);
    uint16 make_wristTilt_command(uint8* info_array, uint8 byte1, uint8 byte2);
    
    void send_packet();
    void fill_data_array();
    
    void wristTilt();
    void wristRotate();
    void elbow();
    void shoulder();
    void baseAzimuth();
    void effector();
    void arduino();
    
    void initialize();
    //--------------------------------------------------- END Function Stubs
#endif
