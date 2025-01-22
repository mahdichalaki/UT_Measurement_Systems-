clear; close all; clc;

%% Circuit properties
freq1 = 5.34;       %Hz
freq2 = 74.645;     %Hz
R = 265.258;        %Ohm
C = 1e-4;           %F
cte1 = 1/sqrt(1+(R*C*freq1*2*pi)^2);
cte2 = 1/sqrt(1+(R*C*freq2*2*pi)^2);

%% Receiving data
SampleNumber = 1000;
a=strings(SampleNumber,2);
s = serialport ("COM5", 57600);
configureTerminator(s,"CR/LF");

for i = 1:SampleNumber
a(i,:) = strsplit(readline(s));
end

b = double(a);
clear s

% timestamps
t = b(:,1)/10000;

% Signal read from Arduino
experimental_signal = b(:,2);

% Theoritical signal without filter
original_signal = 1.25 * (sin(freq1*2*pi*t) + sin(freq2*2*pi*t)) + 2.5;

% Theoritical signal with filter
expected_signal = 1.25 * (cte1 * sin(freq1*2*pi*t) + cte2 * sin(freq2*2*pi*t)) + 2.5;

figure;
plot(t,original_signal)
%hold on

%% Plotting
figure
plot(t,original_signal)
hold on
plot(t,expected_signal)
hold on
plot(t,experimental_signal)
hold off
legend('original','expected','experimental')
xlabel('Time (s)')
ylabel('Amplitude (v)')
title('5.34Hz - 74.64Hz Signal - f0 = 6Hz')



