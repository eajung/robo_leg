%frame 192 (1.6 seconds) start

%i = 731 - lowest squat (end of squat) (6.091 seconds)

%frame 1150 - end of stand(9.5833 seconds)


close all
clear all
clc

A = csvread('REV5_squat.csv', 5);

current_frame = 1;
start_frame = 192;
middle_frame = 731;
end_frame = 1150;


while(current_frame < end_frame)
    if(current_frame == 1)
        current_frame = start_frame;
        time = A(current_frame,1:1:24)/1000; % in millimeters
      % Time reads the large matrix A and takes the row, i, and stores all the columns for that specified row
      pelvis_1 = time(1:3);
      pelvis_2 = time(4:6);
      femur_1 = time(7:9);
      femur_2 = time(10:12);
      tibia_1 = time(13:15);
      tibia_2 = time(16:18);
      ankle_1 = time(19:21);
      ankle_2 = time(22:24);

        subplot(1,3,1)
        hold on
        plot([pelvis_1(1) pelvis_2(1)], [pelvis_1(2) pelvis_2(2)])
        plot([femur_1(1) femur_2(1)], [femur_1(2) femur_2(2)])
        plot([tibia_1(1) tibia_2(1)], [tibia_1(2) tibia_2(2)]) 
        plot([ankle_1(1) ankle_2(1)], [ankle_1(2) ankle_2(2)])
        hold off
        axis([0 0.22 0 1.6])
        title('Start of Squat')
        xlabel('x(m)') % x-axis label
        ylabel('y(m)') % y-axis label
    end
    
    if(current_frame == start_frame)
        current_frame = middle_frame;
        time = A(current_frame,1:1:24)/1000; % in millimeters
      % Time reads the large matrix A and takes the row, i, and stores all the columns for that specified row
        pelvis_1 = time(1:3);
        pelvis_2 = time(4:6);
        femur_1 = time(7:9);
        femur_2 = time(10:12);
        tibia_1 = time(13:15);
        tibia_2 = time(16:18);
        ankle_1 = time(19:21);
        ankle_2 = time(22:24);

        subplot(1,3,2)
        hold on
        plot([pelvis_1(1) pelvis_2(1)], [pelvis_1(2) pelvis_2(2)])
        plot([femur_1(1) femur_2(1)], [femur_1(2) femur_2(2)])
        plot([tibia_1(1) tibia_2(1)], [tibia_1(2) tibia_2(2)]) 
        plot([ankle_1(1) ankle_2(1)], [ankle_1(2) ankle_2(2)])
        hold off
        axis([0 0.22 0 1.6])
        title('End of Squat')
        xlabel('x(m)') % x-axis label
        ylabel('y(m)') % y-axis label
    end
    
    if(current_frame == middle_frame)
        current_frame = end_frame;
        time = A(current_frame,1:1:24)/1000; % in millimeters
        % Time reads the large matrix A and takes the row, i, and stores all the columns for that specified row
        pelvis_1 = time(1:3);
        pelvis_2 = time(4:6);
        femur_1 = time(7:9);
        femur_2 = time(10:12);
        tibia_1 = time(13:15);
        tibia_2 = time(16:18);
        ankle_1 = time(19:21);
        ankle_2 = time(22:24);

        subplot(1,3,3)
        hold on
        plot([pelvis_1(1) pelvis_2(1)], [pelvis_1(2) pelvis_2(2)])
        plot([femur_1(1) femur_2(1)], [femur_1(2) femur_2(2)])
        plot([tibia_1(1) tibia_2(1)], [tibia_1(2) tibia_2(2)]) 
        plot([ankle_1(1) ankle_2(1)], [ankle_1(2) ankle_2(2)])
        hold off
        axis([0 0.22 0 1.6])
        title('End of Stand')
        xlabel('x(m)') % x-axis label
        ylabel('y(m)') % y-axis label
        
    end
    
    if(current_frame == end_frame)
        current_frame = 1000000;
    end
    

    

     
 
      
        
      
        
 
 
end
 
 %Finding the lowest point of the squat - frame value is 731

% lowest_value = 100000;
%   for frame = 1:1:1543
%     femur_y = A(frame,11)/1000;
%     if femur_y < lowest_value
%         lowest_value = femur_y;
%         frame
%     end
%       
%       
%   end
 
% disp(lowest_value)



 