clear; close all; clc;

%% Circuit properties
freq = 175; %Hz
R = 909.73; %ohm
C = 1e-6;   %F
cte = 1/sqrt(1+(R*C*freq*2*pi)^2);

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

% Theoritical signal without filter
original_signal = 2.5 * sin(freq*2*pi*t) + 2.5;

% Theoritical signal with filter
expected_signal = cte * (2.5 * sin(freq*2*pi*t) + 2.5);

% Signal read from Arduino
experimental_signal = b(:,2);

%% Plotting
figure;
plot(t,original_signal)
hold on
plot(t,expected_signal)
hold on
plot(t,experimental_signal)
hold off
legend('original','expected','experimental')
xlabel('Time (s)')
ylabel('Amplitude (v)')
title('175Hz Signal')