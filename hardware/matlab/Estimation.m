% Chris Cheney
% May 16, 2018
% DANSER Lab - Sit To Stand Exoslkeleton
% Matlab Force Estimation

% This function takes in an actuator's maximun torque in N.m (Newton.meter) 
% and it returns three statements, saying if this torque is enough to
% support a human undergoing a sit-to-stand motion.

% Directions: Enter the value of the torque in N.m.
% Call this funtion by typing something like: 
%     [hip_check, knee_check, ankle_check] = Estimation(# in N.m)

function [pass_hip, pass_knee, pass_ankle] = Estimation(torque)
    max_ankle_plantarflexion = 24.05; % Newton-meter
    max_hip = 64.82; % Newton-meter
    max_knee = 75.11; % Newton-meter
    % max_hip_deviation = 24.21; % Newton-meter
    % max_knee_deviation = 22.02; % Newton-meter
    % max_ankle_plantarflexion_deviation  = 8.20; % Newton-meter
    if (torque >= max_knee)
        pass_knee = 'The actuator can support the average knee''s force.';
        pass_hip = 'The actuator can support the average hip''s force.';
        pass_ankle = 'The actuator can support the average ankle plantarflexion''s force.';

    elseif ((torque >= max_hip) && (torque < max_knee))
        pass_knee = 'The actuator cannot support the average knee''s force.';
        pass_hip = 'The actuator can support the average hip''s force.';
        pass_ankle = 'The actuator can support the average ankle plantarflexion''s force.';

    elseif ((torque >= max_ankle_plantarflexion) && (torque < max_hip))
        pass_hip = 'The actuator cannot support the average hip''s force.';
        pass_knee = 'The actuator cannot support the average knee''s force.';
        pass_ankle = 'The actuator can support the average ankle plantarflexion''s force.';

    else
        pass_hip = 'The actuator cannot support the average hip''s force.';
        pass_knee = 'The actuator cannot support the average knee''s force.';
        pass_ankle = 'The actuator cannot support the average ankle plantarflexion''s force.';
    end
end