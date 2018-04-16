% File: range_of_motion_plot.m
% Author: Erik Jung & Lawrence Ngo
% Comments: This file plots the OptiTrack data for the leg's range of motion in (x,y)

clear all
close all
clc

% subplot(1,2,1);
prev_frame = 1194;
P = csvread('hinged_gait_organized.csv', prev_frame+2);
P = P';
P = P(1:1:19);

% Current frame 
current_frame = 1948;
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

origin = [P(6) P(7)];
tibia_vector_beginning = [(P(18)-P(2)) (P(19)-P(3)) 0];
tibia_vector_end = [(C(18)-P(2)) (C(19)-P(3)) 0];
theta = rad2deg(atan2(norm(cross(tibia_vector_beginning, tibia_vector_end)), dot(tibia_vector_beginning,tibia_vector_end)))

% Plot hip, femur, and tibia 
% Master Lawrence fix
plot(hip_x,hip_y,'-r','LineWidth',1)
hold on
plot(fem_x,fem_y,'-r','LineWidth',1)
hold on
plot(tib_x,tib_y,'-r','LineWidth',1)
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
plot(hip_x,hip_y,'-r','LineWidth',1)
hold on
plot(fem_x,fem_y,'-r','LineWidth',1)
hold on
plot(tib_x,tib_y,'-r','LineWidth',1)
hold on

C = csvread('hinged_gait_organized.csv',2);

hip_bottom_x = C(:,6);
hip_bottom_y = C(:,7);

femur_top_x = C(:,8);
femur_top_y = C(:,9);

femur_bottom_x = C(:,12);
femur_bottom_y = C(:,13);

tibia_top_x = C(:,14);
tibia_top_y = C(:,15);

tibia_bottom_x = C(:,18);
tibia_bottom_y = C(:,19);

% plot(hip_bottom_x(1), hip_bottom_y(1), 'o');
% hold on
% plot(femur_top_x(1194:1948), femur_top_y(1194:1948),'k--');
% hold on
% plot(femur_bottom_x(1194:1948), femur_bottom_y(1194:1948),'k--');
% hold on
% plot(tibia_top_x(1194:1948), tibia_top_y(1194:1948), 'k--');
% hold on
% plot(tibia_bottom_x(1194:1948), tibia_bottom_y(1194:1948), 'k--');
% hold on
set(gca,'fontsize',16)
title('Range of Motion for Tensegrity Flexural Joints');
xlabel('x (meters)');
ylabel('y (meters)');
legend('Hip Flexion')
% lgd = legend('Hip','Femorus', 'Tibia')
lgd.FontSize = 14;
axis([-0.5, 1.5, 0.5, 2.9]); % axis([xmin, xmax, ymin, ymax]

figure
prev_frame = 1385;
P = csvread('knee_flexion_organized.csv', prev_frame+2);
P = P';
P = P(1:1:8);

% Current frame 
current_frame = 5404;
C = csvread('knee_flexion_organized.csv', current_frame+2);
C = C';
C = C(1:1:8);

% Femur x and y points
fem_x = [P(1) P(3)];
fem_y = [P(2) P(4)];

% Tibia x and y points
tib_x = [P(5) P(7)];
tib_y = [P(6) P(8)];

% Plot hip, femur, and tibia 
% Master Lawrence fix
plot(fem_x,fem_y,'-b','LineWidth',1)
hold on
plot(tib_x,tib_y,'-b','LineWidth',1)
hold on

% Femur x and y points
fem_x = [C(1) C(3)];
fem_y = [C(2) C(4)];

% Tibia x and y points
tib_x = [C(5) C(7)];
tib_y = [C(6) C(8)];

% Plot hip, femur, and tibia 
plot(fem_x,fem_y,'-b','LineWidth',1)
hold on
plot(tib_x,tib_y,'-b','LineWidth',1)
hold on

set(gca,'fontsize',16)
title('Tensegrity Flexural Knee Joint');
xlabel('x (meters)');
ylabel('y (meters)');
legend('Knee Flexion', 'Hip Flexion')
% lgd = legend('Pelvic', 'Femorus', 'Tibia')
lgd.FontSize = 14;
axis([1.4, 2, 0.3, 1.5]); % axis([xmin, xmax, ymin, ymax]

% tibia_vector_beginning = [(P(7)-P(3)) (P(8)-P(4)) 0];
% tibia_vector_end = [(C(7)-P(3)) (C(8)-P(4)) 0];
% theta = rad2deg(atan2(norm(cross(tibia_vector_beginning, tibia_vector_end)), dot(tibia_vector_beginning,tibia_vector_end)))
% 
% prev_frame = 0;
% end_frame = 650;
% i = 1;
% 
% theta_tibia_human=[];
% theta_femur_human=[];
% theta_tibia=[];
% theta_femur=[];
% 
% O = csvread('hinged_gait_organized.csv', prev_frame+2);
% O = O';
% O = O(1:1:19);
% while prev_frame < end_frame
%     P = csvread('hinged_gait_organized.csv', prev_frame+2);
%     P = P';
%     P = P(1:1:19);
%     % -------------PREVIOUS--------------
%     % Hip x and y points
%     hip_x = [P(2) P(4) P(6)];
%     hip_y = [P(3) P(5) P(7)];
% 
%     % Femur x and y points
%     fem_x = [P(8) P(10) P(12)];
%     fem_y = [P(9) P(11) P(13)];
% 
%     % Tibia x and y points
%     tib_x = [P(14) P(16) P(18)];
%     tib_y = [P(15) P(17) P(19)];
% 
%     % Plot hip, femur, and tibia 
%     % Master Lawrence fix
%     %     plot(hip_x, hip_y, '-k', 'LineWidth',1)
%     %     hold on
%     %     plot(fem_x, fem_y, '-k', 'LineWidth',1)
%     %     hold on
%     %     plot(tib_x, tib_y, '-k', 'LineWidth',1)
%     %     hold on
%     
%     tibia_vector_beginning = [(O(18)-O(14)) (O(19)-O(15)) 0];
%     tibia_vector_end = [(P(18)-O(14)) (P(19)-O(15)) 0];
%     
%     femur_vector_beginning = [(O(12)-O(8)) (O(13)-O(9)) 0];
%     femur_vector_end = [(P(12)-O(8)) (P(13)-O(9)) 0];
%     
%     theta_tibia(i) = rad2deg(atan2(norm(cross(tibia_vector_beginning, tibia_vector_end)), dot(tibia_vector_beginning,tibia_vector_end)));
%     theta_femur(i) = rad2deg(atan2(norm(cross(femur_vector_beginning, femur_vector_end)), dot(femur_vector_beginning,femur_vector_end)));
%     i=i+1;
%     
%     prev_frame = prev_frame+10;  
% end
% 
% prev_frame = 650;
% end_frame = 1210;
% O = csvread('hinged_gait_organized.csv', prev_frame+2);
% O = O';
% O = O(1:1:19);
% while prev_frame < end_frame
%     P = csvread('hinged_gait_organized.csv', prev_frame+2);
%     P = P';
%     P = P(1:1:19);
%     % -------------PREVIOUS--------------
%     % Hip x and y points
%     hip_x = [P(2) P(4) P(6)];
%     hip_y = [P(3) P(5) P(7)];
% 
%     % Femur x and y points
%     fem_x = [P(8) P(10) P(12)];
%     fem_y = [P(9) P(11) P(13)];
% 
%     % Tibia x and y points
%     tib_x = [P(14) P(16) P(18)];
%     tib_y = [P(15) P(17) P(19)];
% 
%     % Plot hip, femur, and tibia 
%     % Master Lawrence fix
% %     plot(hip_x, hip_y, '-b', 'LineWidth',1)
% %     hold on
% %     plot(fem_x, fem_y, '-b', 'LineWidth',1)
% %     hold on
% %     plot(tib_x, tib_y, '-b', 'LineWidth',1)
% %     hold on
%     
%     tibia_vector_beginning = [(O(18)-O(14)) (O(19)-O(15)) 0];
%     tibia_vector_end = [(P(18)-O(14)) (P(19)-O(15)) 0];
%     
%     femur_vector_beginning = [(O(12)-O(8)) (O(13)-O(9)) 0];
%     femur_vector_end = [(P(12)-O(8)) (P(13)-O(9)) 0];
%     
%     theta_tibia(i) = -1*rad2deg(atan2(norm(cross(tibia_vector_beginning, tibia_vector_end)), dot(tibia_vector_beginning,tibia_vector_end)));
%     theta_femur(i) = -1*rad2deg(atan2(norm(cross(femur_vector_beginning, femur_vector_end)), dot(femur_vector_beginning,femur_vector_end)));
%     i=i+1;
%     
%     prev_frame = prev_frame+10;  
% end
% 
% prev_frame = 1210;
% end_frame = 1900;
% O = csvread('hinged_gait_organized.csv', prev_frame+2);
% O = O';
% O = O(1:1:19);
% while prev_frame < end_frame
%     P = csvread('hinged_gait_organized.csv', prev_frame+2);
%     P = P';
%     P = P(1:1:19);
%     % -------------PREVIOUS--------------
%     % Hip x and y points
%     hip_x = [P(2) P(4) P(6)];
%     hip_y = [P(3) P(5) P(7)];
% 
%     % Femur x and y points
%     fem_x = [P(8) P(10) P(12)];
%     fem_y = [P(9) P(11) P(13)];
% 
%     % Tibia x and y points
%     tib_x = [P(14) P(16) P(18)];
%     tib_y = [P(15) P(17) P(19)];
% 
%     % Plot hip, femur, and tibia 
%     % Master Lawrence fix
%     %     plot(hip_x, hip_y, '-m', 'LineWidth',1)
%     %     hold on
%     %     plot(fem_x, fem_y, '-m', 'LineWidth',1)
%     %     hold on
%     %     plot(tib_x, tib_y, '-m', 'LineWidth',1)
%     %     hold on
%     
%     tibia_vector_beginning = [(O(18)-O(14)) (O(19)-O(15)) 0];
%     tibia_vector_end = [(P(18)-O(14)) (P(19)-O(15)) 0];
%     
%     femur_vector_beginning = [(O(12)-O(8)) (O(13)-O(9)) 0];
%     femur_vector_end = [(P(12)-O(8)) (P(13)-O(9)) 0];r_end = [(P(18)-O(14)) (P(19)-O(15)) 0];
%     
%     theta_tibia(i) = rad2deg(atan2(norm(cross(tibia_vector_beginning, tibia_vector_end)), dot(tibia_vector_beginning,tibia_vector_end)));
%     theta_femur(i) = rad2deg(atan2(norm(cross(femur_vector_beginning, femur_vector_end)), dot(femur_vector_beginning,femur_vector_end)));
%     i=i+1;
%     
%     prev_frame = prev_frame+10;  
% end
% 
% prev_frame = 1900;
% end_frame = 2690;
% O = csvread('hinged_gait_organized.csv', prev_frame+2);
% O = O';
% O = O(1:1:19);
% while prev_frame < end_frame
%     P = csvread('hinged_gait_organized.csv', prev_frame+2);
%     P = P';
%     P = P(1:1:19);
%     % -------------PREVIOUS--------------
%     % Hip x and y points
%     hip_x = [P(2) P(4) P(6)];
%     hip_y = [P(3) P(5) P(7)];
% 
%     % Femur x and y points
%     fem_x = [P(8) P(10) P(12)];
%     fem_y = [P(9) P(11) P(13)];
% 
%     % Tibia x and y points
%     tib_x = [P(14) P(16) P(18)];
%     tib_y = [P(15) P(17) P(19)];
% 
%     % Plot hip, femur, and tibia 
%     % Master Lawrence fix
%     %     plot(hip_x, hip_y, '-g', 'LineWidth',1)
%     %     hold on
%     %     plot(fem_x, fem_y, '-g', 'LineWidth',1)
%     %     hold on
%     %     plot(tib_x, tib_y, '-g', 'LineWidth',1)
%     %     hold on
%     
%     tibia_vector_beginning = [(O(18)-O(14)) (O(19)-O(15)) 0];
%     tibia_vector_end = [(P(18)-O(14)) (P(19)-O(15)) 0];
%     
%     femur_vector_beginning = [(O(12)-O(8)) (O(13)-O(9)) 0];
%     femur_vector_end = [(P(12)-O(8)) (P(13)-O(9)) 0];
%     
%     theta_tibia(i) = -1*rad2deg(atan2(norm(cross(tibia_vector_beginning, tibia_vector_end)), dot(tibia_vector_beginning,tibia_vector_end)));
%     theta_femur(i) = -1*rad2deg(atan2(norm(cross(femur_vector_beginning, femur_vector_end)), dot(femur_vector_beginning,femur_vector_end)));
% 
%     i=i+1;
%     
%     prev_frame = prev_frame+10;  
% end
% 
% theta_tibia(i) = 0;
% theta_femur(i) = 0;
% i=1;
% %============HUMAN LEG====================================
% prev_frame = 50;
% end_frame = 323;
% 
% O = csvread('hinged_lawrence_organized.csv', prev_frame+2);
% O = O';
% O = O(1:1:19);
% while prev_frame < end_frame
%     P = csvread('hinged_lawrence_organized.csv', prev_frame+2);
%     P = P';
%     P = P(1:1:19);
%     % -------------PREVIOUS--------------
%     % Hip x and y points
%     hip_x = [P(2) P(4) P(6)];
%     hip_y = [P(3) P(5) P(7)];
% 
%     % Femur x and y points
%     fem_x = [P(8) P(10) P(12)];
%     fem_y = [P(9) P(11) P(13)];
% 
%     % Tibia x and y points
%     tib_x = [P(14) P(16) P(18)];
%     tib_y = [P(15) P(17) P(19)];
% 
%     % Plot hip, femur, and tibia 
%     % Master Lawrence fix
%     %     plot(hip_x, hip_y, '-g', 'LineWidth',1)
%     %     hold on
%     %     plot(fem_x, fem_y, '-g', 'LineWidth',1)
%     %     hold on
%     %     plot(tib_x, tib_y, '-g', 'LineWidth',1)
%     %     hold on
%     
%     tibia_vector_beginning = [(O(18)-O(14)) (O(19)-O(15)) 0];
%     tibia_vector_end = [(P(18)-O(14)) (P(19)-O(15)) 0];
%     
%     femur_vector_beginning = [(O(12)-O(8)) (O(13)-O(9)) 0];
%     femur_vector_end = [(P(12)-O(8)) (P(13)-O(9)) 0];
%     
%     theta_tibia_human(i) = rad2deg(atan2(norm(cross(tibia_vector_beginning, tibia_vector_end)), dot(tibia_vector_beginning,tibia_vector_end)));
%     theta_femur_human(i) = rad2deg(atan2(norm(cross(femur_vector_beginning, femur_vector_end)), dot(femur_vector_beginning,femur_vector_end)));
% 
%     i=i+1;
%     
%     prev_frame = prev_frame+4;  
% end
% 
% prev_frame = 323;
% end_frame = 603;
% 
% O = csvread('hinged_lawrence_organized.csv', prev_frame+2);
% O = O';
% O = O(1:1:19);
% while prev_frame < end_frame
%     P = csvread('hinged_lawrence_organized.csv', prev_frame+2);
%     P = P';
%     P = P(1:1:19);
%     % -------------PREVIOUS--------------
%     % Hip x and y points
%     hip_x = [P(2) P(4) P(6)];
%     hip_y = [P(3) P(5) P(7)];
% 
%     % Femur x and y points
%     fem_x = [P(8) P(10) P(12)];
%     fem_y = [P(9) P(11) P(13)];
% 
%     % Tibia x and y points
%     tib_x = [P(14) P(16) P(18)];
%     tib_y = [P(15) P(17) P(19)];
% 
%     % Plot hip, femur, and tibia 
%     % Master Lawrence fix
%     %     plot(hip_x, hip_y, '-g', 'LineWidth',1)
%     %     hold on
%     %     plot(fem_x, fem_y, '-g', 'LineWidth',1)
%     %     hold on
%     %     plot(tib_x, tib_y, '-g', 'LineWidth',1)
%     %     hold on
%     
%     tibia_vector_beginning = [(O(18)-O(14)) (O(19)-O(15)) 0];
%     tibia_vector_end = [(P(18)-O(14)) (P(19)-O(15)) 0];
%     
%     femur_vector_beginning = [(O(12)-O(8)) (O(13)-O(9)) 0];
%     femur_vector_end = [(P(12)-O(8)) (P(13)-O(9)) 0];
%     
%     theta_tibia_human(i) = -1*rad2deg(atan2(norm(cross(tibia_vector_beginning, tibia_vector_end)), dot(tibia_vector_beginning,tibia_vector_end)));
%     theta_femur_human(i) = -1*rad2deg(atan2(norm(cross(femur_vector_beginning, femur_vector_end)), dot(femur_vector_beginning,femur_vector_end)));
% 
%     i=i+1;
%     
%     prev_frame = prev_frame+4;  
% end
% 
% prev_frame = 603;
% end_frame = 945;
% 
% O = csvread('hinged_lawrence_organized.csv', prev_frame+2);
% O = O';
% O = O(1:1:19);
% while prev_frame < end_frame
%     P = csvread('hinged_lawrence_organized.csv', prev_frame+2);
%     P = P';
%     P = P(1:1:19);
%     % -------------PREVIOUS--------------
%     % Hip x and y points
%     hip_x = [P(2) P(4) P(6)];
%     hip_y = [P(3) P(5) P(7)];
% 
%     % Femur x and y points
%     fem_x = [P(8) P(10) P(12)];
%     fem_y = [P(9) P(11) P(13)];
% 
%     % Tibia x and y points
%     tib_x = [P(14) P(16) P(18)];
%     tib_y = [P(15) P(17) P(19)];
% 
%     % Plot hip, femur, and tibia 
%     % Master Lawrence fix
%     %     plot(hip_x, hip_y, '-g', 'LineWidth',1)
%     %     hold on
%     %     plot(fem_x, fem_y, '-g', 'LineWidth',1)
%     %     hold on
%     %     plot(tib_x, tib_y, '-g', 'LineWidth',1)
%     %     hold on
%     
%     tibia_vector_beginning = [(O(18)-O(14)) (O(19)-O(15)) 0];
%     tibia_vector_end = [(P(18)-O(14)) (P(19)-O(15)) 0];
%     
%     femur_vector_beginning = [(O(12)-O(8)) (O(13)-O(9)) 0];
%     femur_vector_end = [(P(12)-O(8)) (P(13)-O(9)) 0];
%     
%     theta_tibia_human(i) = rad2deg(atan2(norm(cross(tibia_vector_beginning, tibia_vector_end)), dot(tibia_vector_beginning,tibia_vector_end)));
%     theta_femur_human(i) = rad2deg(atan2(norm(cross(femur_vector_beginning, femur_vector_end)), dot(femur_vector_beginning,femur_vector_end)));
% 
%     i=i+1;
%     
%     prev_frame = prev_frame+4;  
% end
% 
% prev_frame = 945;
% end_frame = 1203;
% 
% O = csvread('hinged_lawrence_organized.csv', prev_frame+2);
% O = O';
% O = O(1:1:19);
% while prev_frame < end_frame
%     P = csvread('hinged_lawrence_organized.csv', prev_frame+2);
%     P = P';
%     P = P(1:1:19);
%     % -------------PREVIOUS--------------
%     % Hip x and y points
%     hip_x = [P(2) P(4) P(6)];
%     hip_y = [P(3) P(5) P(7)];
% 
%     % Femur x and y points
%     fem_x = [P(8) P(10) P(12)];
%     fem_y = [P(9) P(11) P(13)];
% 
%     % Tibia x and y points
%     tib_x = [P(14) P(16) P(18)];
%     tib_y = [P(15) P(17) P(19)];
% 
%     % Plot hip, femur, and tibia 
%     % Master Lawrence fix
%     %     plot(hip_x, hip_y, '-g', 'LineWidth',1)
%     %     hold on
%     %     plot(fem_x, fem_y, '-g', 'LineWidth',1)
%     %     hold on
%     %     plot(tib_x, tib_y, '-g', 'LineWidth',1)
%     %     hold on
%     
%     tibia_vector_beginning = [(O(18)-O(14)) (O(19)-O(15)) 0];
%     tibia_vector_end = [(P(18)-O(14)) (P(19)-O(15)) 0];
%     
%     femur_vector_beginning = [(O(12)-O(8)) (O(13)-O(9)) 0];
%     femur_vector_end = [(P(12)-O(8)) (P(13)-O(9)) 0];
%     
%     theta_tibia_human(i) = -1*rad2deg(atan2(norm(cross(tibia_vector_beginning, tibia_vector_end)), dot(tibia_vector_beginning,tibia_vector_end)));
%     theta_femur_human(i) = -1*rad2deg(atan2(norm(cross(femur_vector_beginning, femur_vector_end)), dot(femur_vector_beginning,femur_vector_end)));
% 
%     i=i+1;
%     
%     prev_frame = prev_frame+4;  
% end
% 
% i = 84;
% while i < 116
%     theta_tibia_human(i+1) = theta_tibia_human(i) - 0.35;
%     i = i+1;
% end
% 
% i = 257;
% while i < 282
%     theta_tibia_human(i+1) = theta_tibia_human(i) - 0.37;
%     i = i+1;
% end
% theta_tibia_human(290) = -26.54;
% 
% time  = 0:0.088:23.75;
% time_human = 0:0.082:23.75;
% 
% subplot(1,3,2);
% plot(time_human, theta_femur_human,'b-','LineWidth',1);
% hold on
% plot(time_human, theta_tibia_human,'r-','LineWidth',1);
% hold on 
% ylabel('Angle (degrees)')
% xlabel('Time (seconds)')
% set(gca,'fontsize',15) %axis font size
% lgd = legend('Femur', 'Tibia','Location','southeast')
% lgd.FontSize = 14;
% axis([0, 23.75, -120, 80]); % axis([xmin, xmax, ymin, ymax]
% title('(B) Human Leg')
% 
% subplot(1,3,3);
% plot(time, theta_femur,'b-','LineWidth',1);
% hold on
% plot(time, theta_tibia,'r-','LineWidth',1);
% hold on
% ylabel('Angle (degrees)')
% xlabel('Time (seconds)')
% set(gca,'fontsize',15) %axis font size
% lgd = legend('Femur','Tibia','Location','southeast')
% lgd.FontSize = 14;
% axis([0, 23.75, -120, 80]); % axis([xmin, xmax, ymin, ymax]
% title('(C) Tensegrity Flexural Structure')
% 
% suptitle('Angle Displacement: OpenSim Model vs. Human Leg vs. Tensegrity Flexural Structure')
