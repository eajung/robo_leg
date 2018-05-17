%Directions: Enter the value of the torque. Enter old_Units/need_Units as 
%'N.m', 'lb.ft', 'lb.in', 'oz.in'. 

function [new_Value, new_Units] = torqueConversion(value, old_Units, ...
          need_Units)
      if strcmp(old_Units, 'N.m') == 1
          if strcmp(need_Units, 'lb.in') == 1
              new_Value = value *  8.8507
          elseif strcmp(need_Units, 'lb.ft') == 1
              new_Value = value *  0.738
          elseif strcmp(need_Units, 'oz.in') == 1
              new_Value = value * 141.61193
          end
          new_Units = need_Units
      elseif strcmp(old_Units, 'lb.in') == 1
           if strcmp(need_Units, 'N.m') == 1
              new_Value = value * 0.113
          elseif strcmp(need_Units, 'lb.ft') == 1
              new_Value = value * 0.08333
          elseif strcmp(need_Units, 'oz.in') == 1
              new_Value = value * 16
           end
           new_Units = need_Units
      elseif strcmp(old_Units, 'lb.ft') == 1
           if strcmp(need_Units, 'N.m') == 1
              new_Value = value * 1.35582
          elseif strcmp(need_Units, 'lb.in') == 1
              new_Value = value *  12
          elseif strcmp(need_Units, 'oz.in') == 1
              new_Value = value * 192
           end
           new_Units = need_Units
       elseif strcmp(old_Units, 'oz.in') == 1
           if strcmp(need_Units, 'lb.ft') == 1
              new_Value = value * 0.00520833
          elseif strcmp(need_Units, 'lb.in') == 1
              new_Value = value *  0.0625
          elseif strcmp(need_Units, 'N.m') == 1
              new_Value = value * 0.0070615
           end
          new_Units = need_Units
      else 
          new_Value = 'Cannot recognize inputs'
      end
end
          