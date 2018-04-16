
x = [0 23.75]
y = [74.9 74.9]

A = csvread('actual_force_vs_time.csv', 2);
A = A';
time = A(1,:);
hamstring = A(2,:);
front_hip = A(4,:);
back_hip = A(6,:);

% plot(x,y, '--b', 'LineWidth',2)
% hold on
plot(time, hamstring, 'r--', 'LineWidth',0.5);
hold on
plot(time, front_hip, 'm--' , 'LineWidth',0.5);
hold on
plot(time, back_hip,'b--' , 'LineWidth',0.5);
hold on

% lgd = legend('Hamstring Limit','Front\_Hip Limit', 'Back\_Hip Limit')

% To run this, you must download the patch
% https://www.mathworks.com/support/bugreports/1283854/



ham_x = [0.48 5.60 16.30] 
ham_y = [28.2 28.2 22.95] 

hipf_x = [9.60   19.300]
hipf_y = [70.575 35.025]

hipb_x = [16.30]
hipb_y = [35.325]


% plot(x,y, '--b', 'LineWidth',2)
% hold on
% scatter(ham_x,ham_y, 'm','LineWidth',2, 'MarkerFaceColor','magenta')
% hold on
% scatter(hipf_x,hipf_y, 'g','LineWidth',2, 'MarkerFaceColor','green')
% hold on
% scatter(hipb_x,hipb_y,'k','LineWidth',2, 'MarkerFaceColor','black')
% hold on




% set(gcf,'color','w'); %grid color white
% title('Gait Force','FontWeight','Normal')


% ylabel('Muscle Force (N)')
% xlabel('Time (sec)')
% set(gca,'fontsize',10)
% hold on

% set(gca, 'xtick',[0,0.00720000000000000,5.47000000000000,5.72000000000000, 9.48000000000000, 9.61720000000000,16.1700000000000,16.3072000000000,19.1700000000000,19.3000000000000,23.7500000000000]);
% set(gca, 'xtick', [0.00720000000000000,5.47000000000000, 9.48000000000000,16.1700000000000,19.1700000000000,23.7500000000000]);
% set(gca, 'XTickLabelStyle', 'shifted')
% set(gca, 'XTickLabelRotation', 60);
% axis([0, 23.75, 0, 76]); % axis([xmin, xmax, ymin, ymax]


% lgd = legend('Maximum','Hamstring','Front\_Hip', 'Back\_Hip')
% lgd.FontSize = 12;