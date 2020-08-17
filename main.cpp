/*******************************************************************************
* Copyright 2017 ROBOTIS CO., LTD.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

/* Author: Ryu Woon Jung (Leon) */

//
// *********     ping Example      *********
//
//
// Available Dynamixel model on this example : All models using Protocol 1.0
// This example is designed for using a Dynamixel MX-28, and an USB2DYNAMIXEL.
// To use another Dynamixel model, such as X series, see their details in E-Manual(emanual.robotis.com) and edit below "#define"d variables yourself.
// Be sure that Dynamixel MX properties are already set as %% ID : 1 / Baudnum : 34 (Baudrate : 57600)
//
#include <fcntl.h>
#include <termios.h>
#include<signal.h>
#include<unistd.h>

int end_this_program;
void signalHandler(int sig) {
    //signal comare
    if (sig == SIGINT) end_this_program = 1;
}


#define STDIN_FILENO 0

#include <stdio.h>
extern "C"{
#include <dynamixel_sdk.h>                                  // Uses Dynamixel SDK library
}

//opencv

#include<opencv2/opencv.hpp>

// Protocol version
//#define PROTOCOL_VERSION                1.0                 // See which protocol version is used in the Dynamixel
#define PROTOCOL_VERSION                2.0                 // See which protocol version is used in the Dynamixel

//SET TORQUE
//#define TORQUE_REGISTER           24         //1BYTE         // Control table address is different in Dynamixel model
#define TORQUE_REGISTER           64         //1BYTE         // Control table address is different in Dynamixel model

//SET SPEED
//#define SPEED_REGISTER              32         //2BYTE      
#define SPEED_REGISTER              104         //4BYTE   

//GET SPEED
//#define SPEED_STATUS                  38         //2BYTE
#define SPEED_STATUS                  128         //4BYTE

#define TORQUE_ENABLE                   1                   // Value for enabling the torque
#define TORQUE_DISABLE                  0


#define BAUDRATE                        1000000
#define DEVICENAME                      "/dev/ttyUSB0"      // Check which port is being used on your controller
                                                            // ex) Windows: "COM1"   Linux: "/dev/ttyUSB0" Mac: "/dev/tty.usbserial-*"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int communication_check(int port_num, double version);

int set_motor_speed(int port_num, double version, int ID, int speed);
int get_motor_speed(int port_num, double version, int ID);

int set_motor_torque(int port_num, double version, int ID);
int clear_motor_torque(int port_num, double version, int ID);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_camera();

cv::VideoCapture video(0);

int getch()
{
#if defined(__linux__) || defined(__APPLE__)
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
#elif defined(_WIN32) || defined(_WIN64)
    return _getch();
#endif
}


int main()
{
    const int motorID[2] = { 1,2 };

    signal(SIGINT, signalHandler);

    // Initialize PortHandler Structs
    // Set the port path
    // Get methods and members of PortHandlerLinux or PortHandlerWindows
    int port_num = portHandler(DEVICENAME);

    // Initialize PacketHandler Structs
    packetHandler();

    // Open port
    if (openPort(port_num))
    {
        printf("Succeeded to open the port!\n");
    }
    else
    {
        printf("Failed to open the port!\n");
        printf("Press any key to terminate...\n");
        getchar();
        return 0;
    }

    // Set port baudrate
    if (setBaudRate(port_num, BAUDRATE))
    {
        printf("Succeeded to change the baudrate!\n");
    }
    else
    {
        printf("Failed to change the baudrate!\n");
        printf("Press any key to terminate...\n");
        getchar();
        return 0;
    }

    // Try to ping the Dynamixel
    // Get Dynamixel model number


    for (int i = 0; i < 2; i++) {
        set_motor_torque(port_num, PROTOCOL_VERSION, motorID[i]);
        communication_check(port_num, PROTOCOL_VERSION);
        printf("motor ID %d torque on!\n", motorID[i]);
    }
    if (!video.isOpened()) { std::cerr << "video open error" << std::endl; return 1; }
    
    const double gain = 1;

    const int num_frame = 5;

    int before_value[num_frame] = { 0 };
    int sum = 0;
    int avg = 0;
    unsigned int count = 0;

    while (!end_this_program) {
        before_value[count++% num_frame] = get_camera();
        for (int i = 0; i < num_frame; i++) sum += before_value[(count + i) % num_frame];
        
        avg = sum / num_frame;
        

        set_motor_speed(port_num, PROTOCOL_VERSION, motorID[0], -200 + gain * (avg));
        set_motor_speed(port_num, PROTOCOL_VERSION, motorID[1], 200 + gain * (avg));
        
        sum = 0;
    }

    //torque disable
    for (int i = 0; i < 2; i++) clear_motor_torque(port_num, PROTOCOL_VERSION, motorID[i]);
    // Close port
    closePort(port_num);

    printf("\nprogram end!\n");

    return 0;
}




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int communication_check(int port_num, double version) {
    int dxl_comm_result = COMM_TX_FAIL;
    unsigned char dxl_error = 0;

    if ((dxl_comm_result = getLastTxRxResult(port_num, version)) != COMM_SUCCESS)
    {
        printf("%s\n", getTxRxResult(version, dxl_comm_result));
    }
    else if ((dxl_error = getLastRxPacketError(port_num, version)) != 0)
    {
        printf("%s\n", getRxPacketError(version, dxl_error));
    }
    return 0;
}

int set_motor_speed(int port_num, double version, int ID, int speed) {
    write4ByteTxRx(port_num, version, ID, SPEED_REGISTER, speed);
}

int get_motor_speed(int port_num, double version, int ID) {
    return read4ByteTxRx(port_num, version, ID, SPEED_STATUS);
}

int set_motor_torque(int port_num, double version, int ID) {
    write1ByteTxRx(port_num, version, ID, TORQUE_REGISTER, TORQUE_ENABLE);
}
int clear_motor_torque(int port_num, double version, int ID) {
    write1ByteTxRx(port_num, version, ID, TORQUE_REGISTER, TORQUE_DISABLE);
}


int get_camera() {
    using namespace cv;
    const int resolution = -5;
    
    Mat img;
    video >> img;
    if (img.empty()) { std::cout << "image read error" << std::endl; return 0; }

    cvtColor(img, img, COLOR_BGR2GRAY);
    resize(img, img, img.size() / 2);
    threshold(img, img, 80, 255, CV_8UC1);


    long long col = 0, con = 0;
    for (int r = 0; r < img.rows; ++r) for (int c = 0; c < img.cols; ++c) {
        if (!img.at<uchar>(r, c)) { col += c; ++con; }
    }
    col /= con;

    imshow("img", img);
    waitKey(1);
    
    return (img.cols / 2 - col) / resolution;
}




