%frame 192 (1.6 seconds) start

%i = 731 - lowest squat (end of squat) (6.091 seconds)

%frame 1150 - end of stand(9.5833 seconds)


close all
clear all
clc

A = csvread('REV5_squat.csv', 5);
time = A(1,1:1:24)/1000;
     i = 782.6;
  for i=1:400:1544  
    time = A(i,1:1:24)/1000; % in millimeters
    % Time reads the large matrix A and takes the row, i, and stores all the columns for that specified row
    pelvis_1 = time(1:3);
    pelvis_2 = time(4:6);
    femur_1 = time(7:9);
    femur_2 = time(10:12);
    tibia_1 = time(13:15);
    tibia_2 = time(16:18);
    ankle_1 = time(19:21);
    ankle_2 = time(22:24);
  end
  
lowest_value = 100000;
  for frame = 1:1:1543
    femur_y = A(frame,11)/1000;
    if femur_y < lowest_value
        lowest_value = femur_y;
        frame
    end
      
      
  end
 
disp(lowest_value)


 
%  hold on
%  plot([pelvis_1(1) pelvis_2(1)], [pelvis_1(2) pelvis_2(2)])
%  plot([femur_1(1) femur_2(1)], [femur_1(2) femur_2(2)])
%  plot([tibia_1(1) tibia_2(1)], [tibia_1(2) tibia_2(2)]) 
%  plot([ankle_1(1) ankle_2(1)], [ankle_1(2) ankle_2(2)])
%  hold off
%  axis([0 0.5 0 1.6])
