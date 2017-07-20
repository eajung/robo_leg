% File: motor_demo.m
% Author: Erik Jung
% Comments: This file sets up an Arduino UNO with the Shield through Matlab
% and moves a DC Motor if errors appear: 
% https://www.mathworks.com/matlabcentral/answers/268379-i-can-t-connect-my-adafruit-motorshield-v2-3-with-matlab2014a#comment_343753

% Close all applications and variables
clear all
close all
clc

% Create an Arduino object in MATLAB
% Subject to change: '/dev/tty.usbmodem1461' 
% 'ls /dev/tty.*'  or 'ls /dev/cu.*'
% to find which is the correct address for the USB to UNO
arduino_object = arduino('/dev/tty.usbmodem1461', 'Uno', 'Libraries','Adafruit/MotorShieldV2','ForceBuild',true)

% Add motorshield library
shield = addon(arduino_object,'Adafruit\MotorShieldV2')

% Display the address for I2C communication, 0x60 is default
addrs = scanI2CBus(arduino_object, 0); 

% Create DC motor object at Port M1
dcm = dcmotor(shield, 1)

% Start DC Motor 
start(dcm);

% dcm.Speed = 0.3; % Set speed forward
% pause(2); % Pause system
% dcm.Speed = -0.2; % Set speed reverse
% pause(2); % Pause system

%Stop DC Motor
stop(dcm); 







