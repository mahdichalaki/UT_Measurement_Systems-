clear; close all; clc;

z = [];
freq = 20:10:150;

SampleNumber = 16600;
a=strings(SampleNumber,2);
s = serialport ("COM5", 57600);
configureTerminator(s,"CR/LF");

for i = 1:SampleNumber
a(i,:) = strsplit(readline(s));
end

b = double(a);
clear s

t = b(:,1)/10000;

experimental_signal = b(:,2);
plot(t,experimental_signal)
%experimental_signal = ones(1,15600);

for j = 0:14
    s = experimental_signal(1000*j+1:1000*(j+1));
    pks = findpeaks(s,'MinPeakDistance',300);
    z = [z; [ j , median(pks) ]];
end

for j = 1:numel(freq)
    s = experimental_signal(15001+100*(j-1):15000+100*j);
    pks = findpeaks(s,'MinPeakDistance',15);
    z = [z; [ freq(j) , median(pks) ]];
end

semilogx(z(:,1),20*log10((z(:,2)-2.5)/2.5))

    
    
    
    