function [ f ] = leg_slope( r )
f = 0.759096*exp(0.00178499*r) - 1.26725
x = [0:1100];
f_plot = 0.759096*exp(0.00178499*x) - 1.26725
plot(x,f_plot)
title('Hamstring Force')
xlabel('Resistance (Ohms)')
ylabel('Force (N)')

end

