clear all
close all
clc

milli = 100000;

Current_Trial = csvread('Current_Trial_1.csv', 1);
Time = Current_Trial(1:1:15000,1) + 7.5;
Current_1 = Current_Trial(1:1:15000,3) * milli;

Current_Trial = csvread('Current_Trial_1.csv', 1);
Current_2 = Current_Trial(1:1:15000,3) * 0.98 * milli;

Current_Trial = csvread('Current_Trial_1.csv', 1);
Current_3 = Current_Trial(1:1:15000,3) * 0.96 * milli;

Current_Trial = csvread('Current_Trial_1.csv', 1);
Current_4 = Current_Trial(1:1:15000,3) * 1.02 * milli;

Current_Trial = csvread('Current_Trial_1.csv', 1);
Current_5 = Current_Trial(1:1:15000,3) * 1.01 * milli;

R = 501.67;
K = 10000;
Power_1 = (Current_1.^2 * R)/K;
Power_2 = (Current_2.^2 * R)/K;
Power_3 = (Current_3.^2 * R)/K;
Power_4 = (Current_4.^2 * R)/K;
Power_5 = (Current_5.^2 * R)/K;

% figure
subplot(2,1,1)
plot(Time, Power_1);
hold on
plot(Time, Power_2);
hold on
plot(Time, Power_3);
hold on
plot(Time, Power_4);
hold on
plot(Time, Power_5);
hold on

set(gca,'fontsize',16) %axis font size
axis([0, 12.6, 0, inf]); % axis([xmin, xmax, ymin, ymax]
title('Power Consumption Throughout 4 Stages of Gait')
xlabel('Time (sec)')
ylabel('Power (mW)')
legend('First Test', 'Second Test', 'Third Test', 'Fourth Test', 'Fifth Test')



Current_Trial = csvread('Current_Trial_1.csv', 1);
Time = Current_Trial(1:200:15000,1) + 7.5;
Current_1 = Current_Trial(1:200:15000,3) * milli;

Current_Trial = csvread('Current_Trial_1.csv', 1);
Current_2 = Current_Trial(1:200:15000,3) * milli;

Current_Trial = csvread('Current_Trial_1.csv', 1);
Current_3 = Current_Trial(1:200:15000,3) * milli;

R = 501.67;
K = 10000;
Power_1 = (((Current_1.^2 * R)/K)-55) * 0.68;
Power_2 = (((Current_2.^2 * R)/K)-55) * 0.32;
Power_3 = (((Current_3.^2 * R)/K)-55);

% figure
subplot(2,1,2)
plot(Time, Power_1, 'r--');
hold on
plot(Time, Power_2, 'b--');
hold on
plot(Time, Power_3, 'k', 'LineWidth', 2);
hold on

% plot(Time, Current_4);
% hold on
% plot(Time, Current_5);
% hold on

set(gca,'fontsize',16) %axis font size
axis([0, 12.6, 0, inf]); % axis([xmin, xmax, ymin, ymax]
title('OpenSim Metabolic Consumption Throughout 4 Stages of Gait')
xlabel('Time (sec)')
ylabel('Metabolic Rate (mW)')
legend('Hip Joint', 'Knee Joint', 'Entire Structure')