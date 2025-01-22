clear; close all; clc;

%% Circuit properties
freq1 = 5.34;       %Hz
freq2 = 74.645;     %Hz
R = 15915;          %ohm
C = 1e-6;           %F
cte1 = 1/sqrt(1+(R*C*freq1*2*pi)^2);    %attenuation
cte2 = 1/sqrt(1+(R*C*freq2*2*pi)^2);

%% Sampling properties
Fs = 150;                 % Sampling frequency                    
T = 1/Fs;                 % Sampling period  
SampleNumber = Fs * 5;
t = (0:SampleNumber-1)*T;     %Arduino's signal time vector
f = 0:Fs/SampleNumber:Fs/2;   %FFT x-axis
t1 = 0:0.01:5;                %Theory signal time vector

%% Receiving data

a = zeros(SampleNumber,1);
s = serialport ("COM5", 57600);
configureTerminator(s,"CR/LF");

for i = 1:SampleNumber
a(i) = readline(s);
end

b = double(a);
clear s

experimental_signal = b;
expected_signal = 1.25 * (cte1 * sin(freq1*2*pi*t1) + cte2 * sin(freq2*2*pi*t1)) + 2.5;
%% Plotting without Hanning window
figure
plot(t1(1:100),expected_signal(1:100),'Color','#0072BD')
hold on
plot(t(1:150),experimental_signal(1:150),'b--o','Color','r')
hold off
xlabel('time(sec)')
title('Signals without Hanning window')
legend('Expected Signal','Experimental Signal')


%% FFT
% experimental_signal
x_m = mean(experimental_signal);
experimental_signal = experimental_signal - x_m;
w = hann(SampleNumber);
experimental_signal = w.*experimental_signal;

xf = fft(experimental_signal);
Mf = abs(xf);
Mfs = 2*Mf/(SampleNumber/2); %Scaling
Mfs(1) = Mfs(1) + x_m;

% Theory_signal
expected_signal = hann(length(t1)).*(expected_signal' - mean(expected_signal));

%% Plotting after Hanning window
figure
subplot (2,1,1) %Time-domain
plot(t,experimental_signal,'b--o','Color','r')
hold on
plot(t1,expected_signal,'Color','#0072BD')
hold off
xlabel('time(sec)')
title('Signals after Hanning window')
legend('experimental signal','Theorical Signal')

subplot (2,1,2) %FFT
stem (f,Mfs(1:SampleNumber/2+1))
xlabel('Fq(Hz)')
ylabel('|X|')
title('Signal Freq Spectrum')