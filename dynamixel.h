/* ========================================
 * BYU Mars Rover 2015
 * Author: Sam Bury
 * ========================================
*/
#ifndef DYNAMIXEL_H
#define DYNAMIXEL_H

    #include <project.h>
    
    void ServoGoalPosition( uint8 servoID, uint16 position);
    void SetServoTorque( uint8 servoID, uint16 torque);
    void ServoSpeed( uint8 servoID, uint16 speed);

    void ServoGoalPosition( uint8 servoID, uint16 position)
    {
        uint8 array[9];
        
        array[0] = 0xFF;
        array[1] = 0xFF;
        array[2] = servoID; //this is a broadcast ID.  Change for daisychained servos.
        array[3] = 0x05;
        array[4] = 0x03; //write instruction
        array[5] = 0x1E;
        array[6] = position;
        array[7] = position >> 8;
        array[8] = ~(servoID + 0x05 + 0x1E + array[6] + array[7] + 0x03);
        
        Wrist_UART_SpiUartPutArray(array, 0x09);  
    }

    void SetServoTorque( uint8 servoID, uint16 torque)
    {
        uint8 array[9];
        
        array[0] = 0xFF;
        array[1] = 0xFF;
        array[2] = servoID; 
        array[3] = 0x05;
        array[4] = 0x03; //write instruction
        array[5] = 0x0E;
        array[6] = torque;
        array[7] = torque >> 8;
        array[8] = ~(servoID + 0x05 + 0x0E + array[6] + array[7] + 0x03);
        
        Wrist_UART_SpiUartPutArray(array, 0x09);
    }    

    void ServoSpeed( uint8 servoID, uint16 speed)
    {
        uint8 array[9];
        
        array[0] = 0xFF;
        array[1] = 0xFF;
        array[2] = servoID; //this is a broadcast ID.  Change for daisychained servos.
        array[3] = 0x05;
        array[4] = 0x03; //write instruction
        array[5] = 0x20;
        array[6] = speed;
        array[7] = speed >> 8;
        array[8] = ~(servoID + 0x05 + 0x20 + array[6] + array[7] + 0x03);
        
        Wrist_UART_SpiUartPutArray(array, 0x09);  
    }
    
#endif

