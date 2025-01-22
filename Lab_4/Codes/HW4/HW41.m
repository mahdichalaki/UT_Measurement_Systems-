clear; close all; clc;

%% Circuit properties
freq = 23;  %Hz
R = 5305;   %ohm
C = 1e-6;   %F
cte = 1/sqrt(1+(R*C*freq*2*pi)^2); %attenuation

%% Sampling properties
Fs = 46;         % Sampling frequency                    
T = 1/Fs;         % Sampling period  
SampleNumber = Fs * 2;
t = (0:SampleNumber-1)*T;    %Arduino's signal time vector
f = 0:Fs/SampleNumber:Fs/2;  %FFT x-axis
t1 = 0:0.001:2;              %Theory signal time vector

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
%% FFT
xf = fft(experimental_signal);
Mf = abs(xf);
Mfs = Mf/(SampleNumber/2); %Scaling
Mfs(1) = Mfs(1)/2;
Mfs(SampleNumber/2+1) = Mfs(SampleNumber/2+1)/2;

%% Plotting
figure
subplot (2,1,1)                     %Time-domain
plot(t(1:10),experimental_signal(1:10),'b--o','Color','r')
hold on
plot(t1(1:200),cte * 2.5*sin(2*pi*freq*t1(1:200))+2.5,'Color','#0072BD')
hold off
xlabel('time(sec)')
title('Fs = 46 Hz')
legend('experimental signal','Theorical Signal')

subplot (2,1,2)                     %FFT
stem (f,Mfs(1:SampleNumber/2+1))
xlabel('Fq(Hz)')
ylabel('|X|')
title('Signal Freq Spectrum')