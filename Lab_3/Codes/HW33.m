clear; close all; clc;

z = [];             %Holds Freqs and Responses
freq = 20:10:170;

%% Receiving data
SampleNumber = 16600;
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

%% Plotting
figure
plot(t,experimental_signal)
xlabel('Time (s)')
ylabel('Amplitude (v)')
title('Time-variant signal - f0 = 6Hz')

% For 1-15Hz, find peaks ans stores them
for j = 0:14
    s = experimental_signal(1000*j+1:1000*(j+1));
    pks = findpeaks(s,'MinPeakDistance',300);
    z = [z; [ j , median(pks) ]];
end

% For 20:10:170 Hz, find peaks ans stores them
for j = 1:numel(freq)
    s = experimental_signal(15001+100*(j-1):15000+100*j);
    pks = findpeaks(s,'MinPeakDistance',15);
    z = [z; [ freq(j) , median(pks) ]];
end

% Frequency response
figure
 %Actual signal freq response
semilogx(z(:,1),20*log10((z(:,2)-2.5)/2.5))
ylabel('Attenuation (dB)')
xlabel('frequency (Hz)')
title('Attenuation-Freq')

hold on
%Theoritical signal freq response
semilogx(z(:,1),20*log10((1./sqrt(1+(z(:,1)/6).^2))))
legend('Actual','Theory')

    
    
    
    