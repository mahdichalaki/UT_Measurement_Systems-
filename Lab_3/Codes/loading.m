clear; close all; clc;

freq1 = 5.34;
freq2 = 74.645;
R = 265.25;
C = 1e-4;
cte1 = 1/sqrt(1+(R*C*freq1*2*pi)^2);
cte2 = 1/sqrt(1+(R*C*freq2*2*pi)^2);

n = 200;

load('exf6.mat')
t = exf6(1:n,4);

original_signal = 1.25 * (sin(freq1*2*pi*t) + sin(freq2*2*pi*t));
expected_signal = 1.25 * (0.68 * sin(freq1*2*pi*t) + 0.06 * sin(freq2*2*pi*t));
experimental_signal = exf6(1:n,3)-2.5;

figure;
plot(t,original_signal)
hold on
plot(t,expected_signal)
hold on
plot(t,experimental_signal)
hold off

xlabel('Time (s)')
ylabel('Amplitude (v)')
title('5.34Hz - 74.64Hz Signal - f0 = 6Hz')
legend('original','expected','experimental')

%pks = findpeaks(experimental_signal,'MinPeakDistance',5)
%findpeaks(experimental_signal,'MinPeakDistance',50)