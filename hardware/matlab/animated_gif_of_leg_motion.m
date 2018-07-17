close all
clear all
clc

A = csvread('../../../MATLAB/OptiTrack_Data/Data/REV5_squat.csv', 5);

step_size = 50;
indexing_frame = 192;
 fig = figure;
 difference = 958;
 incremental_value = fix(difference/step_size);
 idx = 1;
 
for indexing_frame = 192:step_size:1150
    
  
    time = A(indexing_frame,1:1:24)/1000; % in millimeters
      % Time reads the large matrix A and takes the row, i, and stores all the columns for that specified row
      pelvis_1 = time(1:3);
      pelvis_2 = time(4:6);
      femur_1 = time(7:9);
      femur_2 = time(10:12);
      tibia_1 = time(13:15);
      tibia_2 = time(16:18);
      ankle_1 = time(19:21);
      ankle_2 = time(22:24);

      
%         hold on
        plot([pelvis_1(1) pelvis_2(1)], [pelvis_1(2) pelvis_2(2)])
        hold on
        plot([femur_1(1) femur_2(1)], [femur_1(2) femur_2(2)])
        hold on
        plot([tibia_1(1) tibia_2(1)], [tibia_1(2) tibia_2(2)])
        hold on
        plot([ankle_1(1) ankle_2(1)], [ankle_1(2) ankle_2(2)])
        hold off
        axis([0 0.22 0 1.6])
        xlabel('x(m)') % x-axis label
        ylabel('y(m)') % y-axis label
        
        drawnow
        
        
        frame = getframe(fig);
        im{idx} = frame2im(frame);
        idx = idx+1;
end

% for idx = 1:incremental_value
%     subplot(3,3,idx)
%     imshow(im{idx});
% end

filename = 'testAnimated.gif'; % Specify the output file name
for idx = 1:incremental_value
    [X,map] = rgb2ind(im{idx},256);
    delay=0.2;
    if idx == 1
        imwrite(X,map,filename,'gif','LoopCount',Inf,'DelayTime',delay);
    else
        imwrite(X,map,filename,'gif','WriteMode','append','DelayTime',delay);
    end
end

