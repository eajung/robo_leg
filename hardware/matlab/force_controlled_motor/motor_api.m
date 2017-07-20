classdef motor_api
    methods(Static)
        
        function [x] = increase(dcm)
            for i = 0:100
                dcm.Speed = dcm.Speed + .00392;
                pause(.005);
            end
            S = 'Finished increase.';
            disp(S)
        end

        function [x] = decrease(dcm)
            for i = 0:100
                dcm.Speed = dcm.Speed - .00392;
                pause(.005);
            end
            S = 'Finished decrease speed';
            disp(S)
        end

        function [x] = stop(dcm)
            S = 'Stopped motor.';
            dcm.Speed = 0;
            pause(1);
            disp(S)
        end
        
    end
end

