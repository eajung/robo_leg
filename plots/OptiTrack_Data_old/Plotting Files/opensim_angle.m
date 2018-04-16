clear all
close all
clc


y_offset = -50;
stage_1_hip_angle = csvread('stage_1_hip.csv',0,0);
H_S1 = stage_1_hip_angle(1:1.87:end,:); % H=Hip & S=Stage#

stage_1_hip_angle_2 = csvread('stage_1_hip_pt2.csv',0,0);
H2_S1= stage_1_hip_angle_2(1:1.47:end,:);

stage_2_knee_angle = csvread('stage_2_knee.csv',0,0);
K_S2 = stage_2_knee_angle(1:1000:end,:); % H=Hip & S=Stage#

stage_2_hip_angle = csvread('stage_2_hip.csv',0,0);
H_S2 = stage_2_hip_angle(1:1000:end,:); % H=Hip & S=Stage#
H2_S2 = H_S2(230:1:716,:);
H_S2 = H_S2(1:1:230,:);

stage_3_knee_angle = csvread('stage_3_knee.csv',0,0);
K_S3 = stage_3_knee_angle(1:413:end,:); % H=Hip & S=Stage#

stage_3_hip_angle = csvread('stage_3_hip.csv',0,0);
H_S3 = (stage_3_hip_angle(1:413:end,:)); % H=Hip & S=Stage#

H_S4 = -1*stage_3_hip_angle(1:600:end,:);
K_S4 = -1*stage_3_knee_angle(1:413:end,:);

Femur = -1*cat(1, H_S1, H2_S1, H_S2, (H2_S2-50.2), -1*H_S3-45, -1*H_S4+30);
time_femur = 0:0.011375:23.75;
Tibia = -1*cat(1, K_S2, K_S3, 0.5*K_S4-75);
time_tibia = 0:0.0110568:23.75;

subplot(1,3,1);
plot(time_femur+1, Femur/2, 'b-', 'LineWidth', 1);
hold on
plot(time_tibia+1, (Tibia-50), 'r-', 'LineWidth', 1);
hold on
ylabel('Angle (degrees)')
xlabel('Time (seconds)')
set(gca,'fontsize',15) %axis font size
axis([0, 23.75, -120, 80]); % axis([xmin, xmax, ymin, ymax]
title('(A) OpenSim Model')
lgd = legend('Femur', 'Tibia','Location','southeast')
lgd.FontSize = 14;
