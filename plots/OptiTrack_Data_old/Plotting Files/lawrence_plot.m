% File: lawrence_plot.m
% Author: Erik Jung & Lawrence Ngo
% Comments: This file plots the OptiTrack data for Lawrence in (x,y)

close all
clear all
clc

lawrence_y_offset = 0.95;
% lawrence_gait
% (0 ,323 ) 2.66 seconds
% ( 323, 603 ) 5.00 seconds
% (603,  945)  7.85 seconds
% (945, 1203) 10.00 seconds
% 
% tensegrity_gait
% (0, 653) 5.41 seconds
% (653, 1213) 10.08 seconds
% (1213, 1900) 15.81 seconds
% (1900, 2700) 22.47 seconds


subplot(1,4,1) %1x4 postion 1
%==LABELING=============================================================
set(gcf,'color','w'); %grid color white
ylabel('y (m)')
xlabel('x (m)')
set(gca,'fontsize',16) %axis font size
grid on
hold on
axis([-1, 1.5, 0.5, 3]); % axis([xmin, xmax, ymin, ymax]
%=====================================================================
prev_frame = 0; % Start frame
end_frame = 323; % End frame
while prev_frame < end_frame
    P = csvread('hinged_lawrence_organized.csv', prev_frame+2);
    P = P';
    P = P(1:1:19);
    % -------------PREVIOUS--------------
    % Hip x and y points
    hip_x = [P(2) P(4) P(6)];
    hip_y = [P(3) P(5) P(7)] + lawrence_y_offset;

    % Femur x and y points
    fem_x = [P(8) P(10) P(12)];
    fem_y = [P(9) P(11) P(13)] + lawrence_y_offset;

    % Tibia x and y points
    tib_x = [P(14) P(16) P(18)];
    tib_y = [P(15) P(17) P(19)] + lawrence_y_offset;

    % Plot hip, femur, and tibia 
    % Master Lawrence fix
    plot(hip_x, hip_y, '-k', 'LineWidth',1)
    hold on
    plot(fem_x, fem_y, '-k', 'LineWidth',1)
    hold on
    plot(tib_x, tib_y, '-k', 'LineWidth',1)
    hold on
    prev_frame = prev_frame+30;  
end
title({'Stage 1: Heel Lift','(Time 0.0-2.66 secs)'})
subplot(1,4,2) %1x4 postion 2 
%==LABELING=============================================================
set(gcf,'color','w'); %grid color white
ylabel('y (m)')
xlabel('x (m)')
set(gca,'fontsize',16) %axis font size
grid on
hold on
axis([-1, 1.5, 0.5, 3]); % axis([xmin, xmax, ymin, ymax]
%=====================================================================
prev_frame = 323;
end_frame = 603;
while prev_frame < end_frame
    P = csvread('hinged_lawrence_organized.csv', prev_frame+2);
    P = P';
    P = P(1:1:19);
    % -------------PREVIOUS--------------
    % Hip x and y points
    hip_x = [P(2) P(4) P(6)];
    hip_y = [P(3) P(5) P(7)] + lawrence_y_offset;

    % Femur x and y points
    fem_x = [P(8) P(10) P(12)];
    fem_y = [P(9) P(11) P(13)] + lawrence_y_offset;

    % Tibia x and y points
    tib_x = [P(14) P(16) P(18)];
    tib_y = [P(15) P(17) P(19)] + lawrence_y_offset;

    % Plot hip, femur, and tibia 
    % Master Lawrence fix
    plot(hip_x, hip_y, '-k', 'LineWidth',1)
    hold on
    plot(fem_x, fem_y, '-k', 'LineWidth',1)
    hold on
    plot(tib_x, tib_y, '-k', 'LineWidth',1)
    hold on
    prev_frame = prev_frame+30;  
end
title({'Stage 2: Extension Forward','(Time 2.66-5.0 secs)'})
subplot(1,4,3) %1x4 postion 3
%==LABELING=============================================================
set(gcf,'color','w'); %grid color white
ylabel('y (m)')
xlabel('x (m)')
set(gca,'fontsize',16) %axis font size
grid on
hold on
axis([-1, 1.5, 0.5, 3]); % axis([xmin, xmax, ymin, ymax]
%=====================================================================
prev_frame = 603;
end_frame = 945;
while prev_frame < end_frame
    P = csvread('hinged_lawrence_organized.csv', prev_frame+2);
    P = P';
    P = P(1:1:19);
    % -------------PREVIOUS--------------
    % Hip x and y points
    hip_x = [P(2) P(4) P(6)];
    hip_y = [P(3) P(5) P(7)] + lawrence_y_offset;

    % Femur x and y points
    fem_x = [P(8) P(10) P(12)];
    fem_y = [P(9) P(11) P(13)] + lawrence_y_offset;

    % Tibia x and y points
    tib_x = [P(14) P(16) P(18)];
    tib_y = [P(15) P(17) P(19)] + lawrence_y_offset;

    % Plot hip, femur, and tibia 
    % Master Lawrence fix
    plot(hip_x, hip_y, '-k', 'LineWidth',1)
    hold on
    plot(fem_x, fem_y, '-k', 'LineWidth',1)
    hold on
    plot(tib_x, tib_y, '-k', 'LineWidth',1)
    hold on
    prev_frame = prev_frame+30;  
end
title({'Stage 3: Step Through','(Time 5.0-7.85 secs)'})
subplot(1,4,4) %1x4 postion 4
%==LABELING=============================================================
set(gcf,'color','w'); %grid color white
ylabel('y (m)')
xlabel('x (m)')
set(gca,'fontsize',16) %axis font size
grid on
hold on
axis([-1, 1.5, 0.5, 3]); % axis([xmin, xmax, ymin, ymax]
%=====================================================================
prev_frame = 945;
end_frame = 1203;
while prev_frame < end_frame
    P = csvread('hinged_lawrence_organized.csv', prev_frame+2);
    P = P';
    P = P(1:1:19);
    % -------------PREVIOUS--------------
    % Hip x and y points
    hip_x = [P(2) P(4) P(6)];
    hip_y = [P(3) P(5) P(7)] + lawrence_y_offset;

    % Femur x and y points
    fem_x = [P(8) P(10) P(12)];
    fem_y = [P(9) P(11) P(13)] + lawrence_y_offset;

    % Tibia x and y points
    tib_x = [P(14) P(16) P(18)];
    tib_y = [P(15) P(17) P(19)] + lawrence_y_offset;

    % Plot hip, femur, and tibia 
    % Master Lawrence fix
    plot(hip_x, hip_y, '-k', 'LineWidth',1)
    hold on
    plot(fem_x, fem_y, '-k', 'LineWidth',1)
    hold on
    plot(tib_x, tib_y, '-k', 'LineWidth',1)
    hold on

    prev_frame = prev_frame+30;  
end
title({'Stage 4: Equilibrium','(Time 7.85-10.0 secs)'})
%==LABELING=============================================================
set(gcf,'color','w'); %grid color white
ylabel('y (m)')
xlabel('x (m)')
set(gca,'fontsize',16) %axis font size
grid on
hold on
axis([-1, 1.5, 0.5, 3]); % axis([xmin, xmax, ymin, ymax]
%=====================================================================
% lgd = legend('Prev\_Hip','Prev\_Femorus', 'Prev\_Tibia', 'Curr\_Hip','Curr\_Femorus', 'Curr\_Tibia')
% lgd.FontSize = 10;
%======================================================================

% plot(tibia_x,tibia_y,'r--o');
