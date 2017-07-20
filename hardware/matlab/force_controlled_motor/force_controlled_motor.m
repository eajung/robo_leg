% File: force_controlled_motor.m
% Author: Erik Jung
% Comments: Control motor based off of Adafruit stretch cord sensor

% Close all applications and variables
clear all
close all
clc

% Define local reference variables
flexed_state = 0;
maximum_tension = 3.66;
rest_tension = 1.3;

% Create an Arduino object in MATLAB
% Subject to change: '/dev/tty.usbmodem1461' 
% 'ls /dev/tty.*'  or 'ls /dev/cu.*'
% to find which is the correct address for the USB to UNO
arduino_object = arduino('/dev/tty.usbmodem1461', 'Uno', 'Libraries','Adafruit/MotorShieldV2','ForceBuild',true);

% Add motorshield library
shield = addon(arduino_object,'Adafruit\MotorShieldV2');

% Display the address for I2C communication, 0x60 is default
addrs = scanI2CBus(arduino_object, 0); 

% Create DC motor object at Port M1
dcm = dcmotor(shield, 1);

% Start DC Motor 
start(dcm);

% Start knee flexion
motor_api.increase(dcm);

% Reading the voltage input into the Arduino pin A0
stretchcord_reading = readVoltage(arduino_object, 'A0');

% Resistance of the stretch cord sensor 
r_s = 10000 / ((5/stretchcord_reading) - 1); % voltage drop
force = ((0.759096*exp(0.00178499*r_s)) - 1.26725); 

if force > maximum_tension % If we reach the maximum tension in the hamstring
    motor_api.stop(dcm); % Stop knee flexion
    motor_api.decrease(dcm); % Start releasing the knee back to resting position
    flexed_state = 1; % Update state
end

if (force < rest_tension) && (flexed_state == 1) % Once we're back at rest length
    motor_api.stop(dcm); % Stop the release of the knee
    flexed_state = 0;
    stop(dcm); % Cut power off to M1
end







