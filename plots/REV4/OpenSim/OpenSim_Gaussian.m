clear all
close all
clc


subplot(2,1,1);
x = 0:0.01:2;
y = normpdf(x,1,.25)/1.55;
plot(x,y,'r','LineWidth',2)
hold on
plot(x, 1000.^(x-1.5),'b','LineWidth',2)
title('Muscle Normalized Force x Normalized Length')
legend('Active','Passive','Location','southwest')
xlabel('Normalized Length')
ylabel('Normalized Force')
axis([0 inf 0 1.2]);
set(gca,'FontSize',16)

subplot(2,1,2);
x = -1:0.01:1;
y = sigmf(x,[50 0])*1.25;
plot(x,y,'r','LineWidth',2)
hold on
y = sigmf(x,[50 0])*.75;
plot(x, y,'b','LineWidth',2)
title('Muscle Normalized Force x Normalized Velocity')
legend('Acceleration = 1','Acceleration = 0.5','Location','southwest')
xlabel('Normalized Velocity')
ylabel('Normalized Force')
axis([-1 1 0 1.4]);
set(gca,'FontSize',16)


