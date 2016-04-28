/* ========================================
 *created by Samuel Bury Jan. 31, 2015
*/

#include "main.h"

//this ISR will be used to set our timeFlag according to our timer component
///set to the time of the longest path for our code
//TODO: test how long it takes code to run
CY_ISR(timer_isr)
{
    uint32 isr_var = Timer_1_GetInterruptSourceMasked();
    timerFlag = 1;
    Timer_1_ClearInterrupt(isr_var);
}

//Funtion declarations/definitions
//TODO: set bounds checking
uint16 simple_pos_to_vel(uint16 new_command, uint16 recent_command)
{
    uint16 cur_command;
    
    if(new_command >= 1000 && new_command < 1250)
    {
        if(recent_command > 1002)
        {
            cur_command = recent_command - 2;
        }
        else
        {
            cur_command = 1000;
        }
    }
    else if(new_command >= 1250 && new_command < 1375)
    {
        if(recent_command > 1001)
        {
            cur_command = recent_command - 1;
        }
        else
        {
            cur_command = 1000;
        }    
    }
    else if(new_command <= 1625 && new_command >= 1375)
    {
        cur_command = recent_command;
    }
    else if(new_command > 1625 && new_command <= 1750)
    {
        if(recent_command < 1999)
        {
            cur_command = recent_command + 1;
        }
        else
        {
            cur_command = 2000;
        }
    }
    else if(new_command > 1750 && new_command <= 2000)
    {
        if(recent_command < 1998)
        {
            cur_command = recent_command + 2;
        }
        else
        {
            cur_command = 2000;
        }
    }
    else
    {
        //increment error variable
        cur_command = 1500;
    }
    return cur_command;
}

uint16 WT_pos_to_vel(uint16 new_command, uint16 recent_command)
{
    uint16 cur_command;
    uint16 change = 12;
    
    if(new_command >= 1024 && new_command < 2000)
    {
        if(recent_command > (1024 + change))
        {
            cur_command = recent_command - change;
        }
        else
        {
            cur_command = 1024;
        }    
    }
    else if(new_command <= 2096 && new_command >= 2000)
    {
        cur_command = recent_command;
    }
    else if(new_command > 2096 && new_command <= 3072)
    {
        if(recent_command < (3072 - change))
        {
            cur_command = recent_command + change;
        }
        else
        {
            cur_command = 3072;
        }
    }
    else
    {
        //increment error variable
        cur_command = 2048;
    }
    return cur_command;
}

uint16 WR_pos_to_vel(uint16 new_command, uint16 recent_command)
{
    uint16 cur_command;
    uint16 change = 12;
    
    if(new_command >= 0 && new_command < 2000)
    {
        if(recent_command > (0+change))
        {
            cur_command = recent_command - change;
        }
        else
        {
            cur_command = 0;
        }  
    }
    else if(new_command <= 2096 && new_command >= 2000)
    {
        cur_command = recent_command;
    }
    else if(new_command > 2096 && new_command <= 4095)
    {
        if(recent_command < (4095 - change))
        {
            cur_command = recent_command + change;
        }
        else
        {
            cur_command = 4095;
        }
    }
    else
    {
        //increment error variable
        cur_command = 2048;
    }
    return cur_command;
}

uint16 make_command(uint8* info_array, uint8 byte1, uint8 byte2)
{
    uint16 command;
    uint16 temp1; //&&&&&&&&&&&&&&&&&&&&& from int16 to uint16 for temp 1 and 2
    uint16 temp2;
    int16 temp3;
    
    temp1 = (info_array[byte1] << 8) & 0xFF00;
    temp2 = 0x00FF & (info_array[byte2]);
    temp3 = (int16)(temp1 | temp2);
    command = (uint16)((temp3/2) + 1500);
    return command;
}

uint16 make_wristRotate_command(uint8* info_array, uint8 byte1, uint8 byte2)
{
    uint16 command;
    uint16 temp1; //&&&&&&&&&&&&&&&&&&&&& from int16 to uint16 for temp 1 and 2
    uint16 temp2;
    int16 temp3;
    
    temp1 = (info_array[byte1] << 8) & 0xFF00;
    temp2 = 0x00FF & (info_array[byte2]);
    temp3 = (int16)(temp1 | temp2);
    command = (uint16)((2*temp3) + 2048);
    return command;
}

uint16 make_wristTilt_command(uint8* info_array, uint8 byte1, uint8 byte2)
{
    uint16 command;
    uint16 temp1; //&&&&&&&&&&&&&&&&&&&&& from int16 to uint16 for temp 1 and 2
    uint16 temp2;
    int16 temp3;
    
    temp1 = (info_array[byte1] << 8) & 0xFF00;
    temp2 = 0x00FF & (info_array[byte2]);
    temp3 = (int16)(temp1 | temp2);
    command = (uint16)(temp3 + 2048);
    return command;
}

enum send_packet_states {send_start, send_init, send_feedback, send_heartbeat, send_wait} send_packet_state;
void send_packet()
{
    //compile all of the most recent feedback variables into a packet
    //necessary feedback variables: system state, dynamixel read write errors, PID errors
    //TODO define system state
    //send packet via serial to wiznet
    
    switch(send_packet_state)
    {
        case send_start:
            break;
        
        case send_init:
            feedback_array[0] = 0x02; //0x02
            feedback_array[1] = 0xCA; //0xCA
            feedback_array[2] = 0;
            feedback_array[3] = 0;
            feedback_array[4] = 0;
            feedback_array[5] = 0;
            feedback_array[6] = 0;
            feedback_array[7] = 0;
            feedback_array[8] = 0;
            feedback_array[9] = 0;
            feedback_array[10] = 0;
            feedback_array[11] = 0;
            feedback_array[12] = 0;
            feedback_array[13] = 0;
            feedback_array[14] = 0;
            feedback_array[15] = 0;
            feedback_array[16] = 0;
            feedback_array[17] = 0;
            feedback_array[18] = 0;
            feedback_array[19] = 0;
            feedback_array[20] = 0;            
            //feedback_array[13] = 0xee;
            
            heartbeat_array[0] = 0x03;
            heartbeat_array[1] = 0xCA;
            heartbeat_array[2] = 7;
//            heartbeat_array[3] = 7;
//            heartbeat_array[4] = 7;
//            heartbeat_array[5] = 7;
//            heartbeat_array[6] = 7;
//            heartbeat_array[7] = 7;
//            heartbeat_array[8] = 7;
//            heartbeat_array[9] = 7;
//            heartbeat_array[10] = 7;
//            heartbeat_array[11] = 7;
//            heartbeat_array[12] = 7;
//            heartbeat_array[13] = 0xee;
            break;
        
        case send_feedback:
            wiznetWriteUdpFrame(feedback_array, FEEDBACK_ARRAY_SIZE);
            wiznetSend();
            break;
        
        case send_heartbeat:
            wiznetWriteUdpFrame(heartbeat_array, HEARTBEAT_ARRAY_SIZE);
            wiznetSend();
            HEARTBEAT_FLAG = 0;
            break;
        
        case send_wait:
            break;
        
        default:
            send_packet_state = send_start;
            break;
    }
    
    switch(send_packet_state)
    {
        case send_start:
            send_packet_state = send_init;
            break;
        
        case send_init:
            send_packet_state = send_heartbeat;
            break;
        
        case send_feedback:
            send_packet_state = send_wait;            
            break;
        
        case send_heartbeat:
            send_packet_state = send_wait;
            break;
        
        case send_wait:
            if(HEARTBEAT_FLAG && (WIZ_INT_Read() == 0))
            {
                wiznetClearInterrupts();    
                send_packet_state = send_heartbeat;
            }
            else if(!HEARTBEAT_FLAG && (WIZ_INT_Read() == 0))
            {
                wiznetClearInterrupts();    
                send_packet_state = send_feedback;
            }
            else
            {
                send_packet_state = send_wait;
            }
            break;

        default:
            send_packet_state = send_start;
            break;
    }    
}

//to be used for parsing reading/parsing the data from the wiznet
void fill_data_array()
{
    wiznetReadUdpFrame(data_array, DATA_ARRAY_SIZE);
}

enum wristTilt_states {tilt_start, tilt_init, tilt_control, tilt_wait} wristTilt_state;
//control the tilting motion of the wrist
void wristTilt()
{
    uint16 newest_command;
    uint16 temp_command;
    
    
    switch(wristTilt_state){ //actions
        case tilt_start:
            break;

        case tilt_init:      
            ServoGoalPosition(0x02, 2048);
            latest_WT_command = 2048;
            break;

        case tilt_control:
            newest_command = make_wristTilt_command(data_array, WT_BYTE_1, WT_BYTE_2);
            
            if(newest_command <= 3072 && newest_command >= 1024)
            {
                LED_Write(0);
                latest_WT_command = WT_pos_to_vel(newest_command, latest_WT_command);
                ServoGoalPosition(0x02, latest_WT_command);            
            }
            else
            {
                //increment error variable
                WT_errors += 1;
                LED_Write(1);
                temp_command = WT_pos_to_vel(2048, latest_WT_command);
                ServoGoalPosition(0x02, temp_command);
            }
            
            WT_FLAG = 0;
            break;
            
        case tilt_wait:
            break;
                        
        default:
            wristTilt_state = tilt_start;
            break;
    }
    
    switch(wristTilt_state){ //transitions
        case tilt_start:
            wristTilt_state = tilt_init;
            break;
        
        case tilt_init:
            wristTilt_state = tilt_wait;
            break;
        
        case tilt_control:
            if(WT_FLAG)
            {
                wristTilt_state = tilt_control;
            }
            else
            {
                wristTilt_state = tilt_wait;
            }
            break;
        
        case tilt_wait:
            if(WT_FLAG)
            {
                wristTilt_state = tilt_control;
            }
            else
            {
                wristTilt_state = tilt_wait; 
            }
            break;
            
        default:
            wristTilt_state = tilt_start;
            break;
    }  
}

enum wristRotate_states {rotate_start, rotate_init, rotate_control, rotate_wait} wristRotate_state;
//control the rotating motion of the wrist
void wristRotate()
{
    uint16 newest_command;
    uint16 temp_command;
    
    switch(wristRotate_state){ //actions
        case rotate_start:
            break;

        case rotate_init:
            ServoGoalPosition(0x01, 2048);
            latest_WR_command = 2048;
            break;

        case rotate_control:
            newest_command = make_wristRotate_command(data_array, WR_BYTE_1, WR_BYTE_2);
            
            if(newest_command <= 4095 && newest_command >= 0)
            {
                LED_Write(0);
                latest_WR_command = WR_pos_to_vel(newest_command,latest_WR_command);
                ServoGoalPosition(0x01, latest_WR_command);            
            }
            else
            {
                //increment error variable
                WR_errors += 1;
                LED_Write(1);
                temp_command = WR_pos_to_vel(2048,latest_WR_command);
                ServoGoalPosition(0x01, temp_command);
            }
            WR_FLAG = 0;
            break;
            
        case rotate_wait:
            break;
 
        default:
            wristRotate_state = rotate_start;
            break;
    }
    
    switch(wristRotate_state){ //transitions
        case rotate_start:
            wristRotate_state = rotate_init;
            break;
        
        case rotate_init:
            wristRotate_state = rotate_wait;
            break;
        
        case rotate_control:
            if(WR_FLAG)
            {
                wristRotate_state = rotate_control;
            }
            else
            {
                wristRotate_state = rotate_wait;
            }
            break;
        
        case rotate_wait:
            if(WR_FLAG)
            {
                wristRotate_state = rotate_control;
            }
            else
            {
                wristRotate_state = rotate_wait;
            }
            break;
            
        default:
            wristRotate_state = rotate_start;
            break;
    }  
}

//control the elbow
enum elbow_states {elbw_start,elbw_init,elbw_execute,elbw_wait} elbow_state;
void elbow()
{ 
    uint16 command;
        
    switch(elbow_state){ //actions
        case elbw_start:
            break;

        case elbw_init:
            ELBW_PWM_WriteCompare(NEUTRAL);
            break;

        case elbw_execute:
            command = make_command(data_array, ELBW_BYTE_1, ELBW_BYTE_2);
            
            if(command <= 2000 && command >= 1000)
            {
                LED_Write(0);
                ELBW_PWM_WriteCompare(command);
            }
            else
            {
                //increment error variable
                elbw_errors += 1;
                LED_Write(1);
                ELBW_PWM_WriteCompare(NEUTRAL);
            }
            ELBOW_FLAG = 0;
            break;
            
        case elbw_wait:
            break;
                        
        default:
            elbow_state = elbw_start;
            break;
    }
    
    switch(elbow_state){ //transitions
        case elbw_start:
            elbow_state = elbw_init;
            break;
        
        case elbw_init:
            elbow_state = elbw_wait;
            break;
        
        case elbw_execute:
            if(ELBOW_FLAG)
            {
                elbow_state = elbw_execute;
            }
            else
            {
                elbow_state = elbw_wait;
            }
            break;
        
        case elbw_wait:
            if(ELBOW_FLAG)
            {
                elbow_state = elbw_execute;
            }
            else
            {
                elbow_state = elbw_wait; 
            }
            break;
            
        default:
            elbow_state = elbw_start;
            break;
    }
}

//control the shoulder
enum shoulder_states {shldr_start,shldr_init,shldr_execute,shldr_wait} shoulder_state;
void shoulder()
{ 
    uint16 command;
        
    switch(shoulder_state){ //actions
        case shldr_start:
            break;

        case shldr_init:
            SHLDR_PWM_WriteCompare(NEUTRAL);
            break;

        case shldr_execute:
            command = make_command(data_array, SHLDR_BYTE_1, SHLDR_BYTE_2);
            
            if(command <= 2000 && command >= 1000) //changed from avg
            {
                LED_Write(0);
                SHLDR_PWM_WriteCompare(command);
            }
            else
            {
                //increment error variable
                shldr_errors += 1;
                LED_Write(1);
                SHLDR_PWM_WriteCompare(NEUTRAL);
            }
            SHOULDER_FLAG = 0;
            break;
            
        case shldr_wait:
            break;
                        
        default:
            shoulder_state = shldr_start;
            break;
    }
    
    switch(shoulder_state){ //transitions
        case shldr_start:
            shoulder_state = shldr_init;
            break;
        
        case shldr_init:
            shoulder_state = shldr_wait;
            break;
        
        case shldr_execute:
            if(SHOULDER_FLAG)
            {
                shoulder_state = shldr_execute;
            }
            else
            {
                shoulder_state = shldr_wait;
            }
            break;
        
        case shldr_wait:
            if(SHOULDER_FLAG)
            {
                shoulder_state = shldr_execute;
            }
            else
            {
                shoulder_state = shldr_wait; 
            }
            break;
            
        default:
            shoulder_state = shldr_start;
            break;
    }  
}

//control the turret
enum baseAzimuth_states {BA_start,BA_init,BA_execute,BA_wait} baseAzimuth_state;
void baseAzimuth()
{ 
    uint16 newest_command;
    uint16 temp_command;
    
    switch(baseAzimuth_state){ //actions
        case BA_start:
            break;

        case BA_init:
            BA_PWM_WriteCompare(NEUTRAL);
            latest_command = 1500;
            break;

        case BA_execute:
            newest_command = make_command(data_array, BA_BYTE_1, BA_BYTE_2);

            if(newest_command <= 2000 && newest_command >= 1000)
            {
                BA_PWM_WriteCompare(latest_command);
                latest_command = simple_pos_to_vel(newest_command, latest_command);
                LED_Write(0);
            }
            else
            {
                LED_Write(1);
                BA_errors += 1;
                //increment error variable
                temp_command = simple_pos_to_vel(1500, latest_command);
                BA_PWM_WriteCompare(temp_command);
            }
            BA_FLAG = 0;
            break;
            
        case BA_wait:
            break;
            
        default:
            baseAzimuth_state = BA_start;
            break;
    }
    
    switch(baseAzimuth_state)
    { //transitions
        case BA_start:
            baseAzimuth_state = BA_init;
            break;
        
        case BA_init:
            baseAzimuth_state = BA_wait;
            break;
        
        case BA_execute:
            if(BA_FLAG)
            {
                baseAzimuth_state = BA_execute;
            }
            else
            {
                baseAzimuth_state = BA_wait;
            }
            break;
        
        case BA_wait:
            if(BA_FLAG)
            {
                baseAzimuth_state = BA_execute;
            }
            else
            {
                baseAzimuth_state = BA_wait; 
            }
            break;
            
        default:
            baseAzimuth_state = BA_start;
            break;
    }
}

enum effector_states {eff_start, eff_init, eff_execute, eff_wait} effector_state;
void effector()
{
    uint16 command;

    switch(effector_state){ //actions
        case eff_start:
            break;

        case eff_init:           
           EFFECTOR_PWM_WriteCompare(NEUTRAL);
           break;

        case eff_execute:
            command = make_command(data_array, EFF_BYTE_1, EFF_BYTE_2);

            if(command <= 2000 && command >= 1000)
            {
                EFFECTOR_PWM_WriteCompare(command);
            }
            else
            {
                EFFECTOR_PWM_WriteCompare(1000);
            }
            
            EFFECTOR_FLAG = 0;
            break;
            
        case eff_wait:
            break;
        
        default:
            effector_state = eff_start;
            break;
    }
    
    switch(effector_state){ //transitions
        case eff_start:
            effector_state = eff_init;
            break;
        
        case eff_init:
            effector_state = eff_wait;
            break;
        
        case eff_execute:
            if(EFFECTOR_FLAG)
            {
                effector_state = eff_execute;
            }
            else
            {
                effector_state = eff_wait;
            }
            break;
        
        case eff_wait:
            if(EFFECTOR_FLAG)
            {
                effector_state = eff_execute;
            }
            else
            {
                effector_state = eff_wait; 
            }
            break;
        
        default:
            effector_state = eff_start;
            break;
    }    
}

enum arduino_states {ard_start, ard_init, ard_wait, ard_read, ard_write} arduino_state;
void arduino()
{
    uint8 video_mux;
    uint8 laser;
    uint8 pack_for_rover;
    uint8 ARD_ARRAY_SIZE = 12;
    
    switch(arduino_state) //state actions
    {
        case ard_start:
            break;
        
        case ard_init:
            video_mux = 0x10;
            laser = 0x00;
            pack_for_rover = video_mux | laser;
            //write initial video, laser enable
            Arduino_UART_UartPutChar(pack_for_rover); 
            break;
        
        case ard_wait:
            break;
        
        case ard_read:
            for(int i = 0; i < ARD_ARRAY_SIZE; i++)
            {
              feedback_array[i] = Arduino_UART_UartGetByte();
            }
            break;
        
        case ard_write:
            //write laser
            //write video
            video_mux = data_array[ARD_BYTE_1];
            laser = data_array[ARD_BYTE_2];
            
            pack_for_rover = video_mux | laser;
            
            Arduino_UART_UartPutChar(pack_for_rover);
            
            //pass exactly what was sent to me by basestation
            ARD_FLAG = 0;
            break;
        
        default:
            arduino_state = ard_start;
            break;
    }
    switch(arduino_state) //state transitions
    {
        case ard_start:
            arduino_state = ard_init;
            break;
        
        case ard_init:
            arduino_state = ard_wait;
            break;
        
        case ard_wait:
            arduino_state = ard_read;
            break;
        
        case ard_read:
            if(ARD_FLAG)
            {
                arduino_state = ard_write;
            }
            else
            {
                arduino_state = ard_wait;
            }
            break;
            
        case ard_write:
            if(ARD_FLAG)
            {
                arduino_state = ard_write;
            }
            else
            {
                arduino_state = ard_wait;
            }
            break;
            
        default:
            arduino_state = ard_start;
            break;
    }   
}

//Initialization function for the program
void initialize()
{
    //initialize the wiznet
    WIZ_RST_Write(0);
    CyDelay(10);
    WIZ_RST_Write(1);
    WIZ_SS_Write(1);
    for(uint8 j=0; j<100; j++)
    {
        if(WIZ_RDY_Read())
        {
            break;
        }
        else
        {
            CyDelay(4);
        }
    }
    
    //Initialize state variables
    baseAzimuth_state = BA_start;
    wristTilt_state = tilt_start;
    wristRotate_state = rotate_start;
    shoulder_state = shldr_start;
    elbow_state = elbw_start;
    effector_state = eff_start;
    arduino_state = ard_start;
    send_packet_state = send_start;
    
    //start all of our components
    SPIM_1_Start();
    Clock_pwm_Start();
    Clock_counter_Start();
    Wrist_UART_Start();
    SHLDR_PWM_Start();
    BA_PWM_Start();
    ELBW_PWM_Start();
    EFFECTOR_PWM_Start();
    //ADC_Start();
    //ADC_StartConvert();
    Arduino_UART_Start();
    
    wiznetInit(ownIpAddr, dstIpAddr, udpPort);
    
    //Initialize the dynamixels <-- Will do this on the computer
    ServoSpeed(0xFE, 300);
    SetServoTorque(0xFE, 0x03FF);
    
    //Initialize our motor drivers
    ELBW_PWM_WriteCompare(NEUTRAL); 
    SHLDR_PWM_WriteCompare(NEUTRAL);
    EFFECTOR_PWM_WriteCompare(NEUTRAL);
    CyDelay(3000);
    
    //ISR stuff
    CyGlobalIntEnable;
    isr_1_StartEx(timer_isr);
    Timer_1_Start();    
}
int main()
{  
    //Define variables
    uint8 fs_count = 0; //fail safe counter to check the interval between receiving packets
    int16 temp_val = NEUTRAL;
    uint8 tick_count = 0;
    uint16 dynamixel_count = 0;
    uint16 feedback_count = 0;
    
    initialize();

    for(;;)
    {   
        if(WIZ_INT_Read()==0)
        {
            wiznetClearInterrupts();
            fill_data_array();
            BA_FLAG = 1;
            WR_FLAG = 1;
            WT_FLAG = 1;
            SHOULDER_FLAG = 1;
            ELBOW_FLAG = 1;
            EFFECTOR_FLAG = 1;
            ARD_FLAG = 1;
            fs_count = 0;
        }
        else
        {
            fs_count += 1;
        }
        
        if(fs_count >= 50)
        {
            temp_val = NEUTRAL;
            fail_safe_errors += 1;
            for(int i = 0; i < DATA_ARRAY_SIZE; (i+=2))
            {
                data_array[i] = temp_val >> 8;
                data_array[i+1] = temp_val & 0x00FF;
            }
        }
        
        baseAzimuth();
        shoulder();
        elbow();
        effector();
        wristTilt();
        wristRotate();
        arduino();
        
        tick_count += 1;
        if(tick_count == 100)
        {
            tick_count = 0;
            HEARTBEAT_FLAG = 1;
        }
        else
        {
            HEARTBEAT_FLAG = 0;
        }
        
        if(dynamixel_count > 1000)
        {
            SetServoTorque(0xFE, 0x03FF);
            dynamixel_count = 0;
        }
        
        feedback_array[14] = fail_safe_errors;
        feedback_array[15] = shldr_errors;
        feedback_array[16] = elbw_errors;
        feedback_array[17] = BA_errors;
        feedback_array[18] = WT_errors;
        feedback_array[19] = WR_errors;
        feedback_array[20] = eff_errors;
        
        feedback_count += 1;
        
        if(feedback_count > 500)
        {
            feedback_count = 0;
            fail_safe_errors = 0;
            shldr_errors = 0;
            elbw_errors = 0;
            BA_errors = 0;
            WT_errors = 0;
            WR_errors = 0;
            eff_errors = 0;
        }
        
        send_packet(); //send feedback packet
        
        while(!timerFlag){} //this while loop will periodize our code to the time of longest path
        timerFlag = 0;
    } 
}
