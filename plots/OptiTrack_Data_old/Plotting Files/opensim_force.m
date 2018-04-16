clear all
close all
clc

front_hip_2_force = csvread('stage2_front_hip_force.csv', 0);
front_hip_2_force = front_hip_2_force(1:989:end)*0.75;

back_hip_3_force = csvread('stage3_back_hip_force.csv', 0);
back_hip_3_force = back_hip_3_force(1:459:end);

hamstring_1_force = csvread('stage1_hamstring_force.csv', 0);
hamstring_1_force = hamstring_1_force(1:end)*500;

stage_1 = 0:0.0297:5.9103;
stage_2 = 5.94:0.0297:11.8503;
stage_3 = 11.88:0.0297:17.7903;
stage_4 = 17.82:0.0297:23.7303;

plot(stage_1, hamstring_1_force, 'r', 'LineWidth', 1.5);
hold on
plot(stage_2, front_hip_2_force, 'm', 'LineWidth', 1.5);
hold on
plot(stage_3, back_hip_3_force, 'b', 'LineWidth', 1.5);
hold on

set(gca,'fontsize',16)
title('Force on Active Muscles');
xlabel('Time (seconds)');
ylabel('Force (Newtons)');
lgd = legend('Bicep femoris long-head', 'Iliopsoas', 'Semimembranosus');
lgd.FontSize = 14;
axis([0, 18, 5, 80]); % axis([xmin, xmax, ymin, ymax]
