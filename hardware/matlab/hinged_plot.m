% File: lawrence_plot.m
% Author: Erik Jung & Lawrence Ngo
% Comments: This file plots the OptiTrack data for Lawrence in (x,y)

% Close all applications and variables
% clear all
% close all
% clc

%offset variables
x_offset = 0.524626;
y_offset = 0.946598;


subplot(1,4,4) %3x3 postion1 

% Previous frame
prev_frame = 1625;
P = csvread('hinged_gait_organized.csv', prev_frame+2);
P = P';
P = P(1:1:19);

% Current frame 
current_frame = 2850;
C = csvread('hinged_gait_organized.csv', current_frame+2);
C = C';
C = C(1:1:19);


% Time (seconds)
previous_time = P(1)
current_time = C(1)

% -------------PREVIOUS--------------
% Hip x and y points
hip_x = [P(2) P(4) P(6)];
hip_y = [P(3) P(5) P(7)];

% Femur x and y points
fem_x = [P(8) P(10) P(12)];
fem_y = [P(9) P(11) P(13)]; 

% Tibia x and y points
tib_x = [P(14) P(16) P(18)];
tib_y = [P(15) P(17) P(19)];

% Plot hip, femur, and tibia 
% Master Lawrence fix
% plot(hip_x,hip_y,'--ok','LineWidth',2)
plot(hip_x,hip_y,'-ok','LineWidth',2)
hold on
% plot(fem_x,fem_y,'--oc','LineWidth',2)
plot(fem_x,fem_y,'-oc','LineWidth',2)
hold on
% plot(tib_x,tib_y,'--om','LineWidth',2)
plot(tib_x,tib_y,'-om','LineWidth',2)
hold on
% -----------------------------------

% -------------CURRENT--------------
% Hip x and y points
hip_x = [C(2) C(4) C(6)];
hip_y = [C(3) C(5) C(7)];

% Femur x and y points
fem_x = [C(8) C(10) C(12)];
fem_y = [C(9) C(11) C(13)];

% Tibia x and y points
tib_x = [C(14) C(16) C(18)];
tib_y = [C(15) C(17) C(19)];

% Plot hip, femur, and tibia 
% Master Lawrence fix
   plot(hip_x,hip_y,'-or','LineWidth',2)
%    plot(hip_x,hip_y,'--r','LineWidth',1)
hold on
  plot(fem_x,fem_y,'-ob','LineWidth',2)
%   plot(fem_x,fem_y,'--b','LineWidth',1)
hold on
  plot(tib_x,tib_y,'-og','LineWidth',2)
%   plot(tib_x,tib_y,'--g','LineWidth',1)
hold on
% ----------------------------------

%==LABELING=============================================================
set(gcf,'color','w'); %grid color white
title( 'D) Time: 23.75 sec','FontWeight','Normal')

ylabel('y (m)')
xlabel('x (m)')
set(gca,'fontsize',8) %axis font size
grid on
hold on

axis([-1, 1.5, 0, 3]); % axis([xmin, xmax, ymin, ymax]

lgd = legend('Start\_Hip','Start\_Femorus', 'Start\_Tibia', 'End\_Hip','End\_Femorus', 'End\_Tibia')
lgd.FontSize = 10;
%======================================================================

% plot(tibia_x,tibia_y,'r--o');
