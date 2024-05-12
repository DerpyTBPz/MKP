clear;
close all;

com = serialport("COM4", 2400);

N = 250;
signal = zeros(1,N);

for i = 1:10000
    plot(signal);
    ylim([0 1024]);
    drawnow;
    %pause(0.01);
    signal = circshift(signal, -1);
    signal(end) = readline(com);
end



% 
% i = 0;
% signal = 1:150;
% 
% figure;
% plot(signal);
% 
% com = serialport("COM3", 2400);
% data = uint8(10);
% 
% while (i < 10) 
%     i = i + 1;
%     data = data + 1;
%     write(com, uint8(i), 'uint8');
%     dataR = read(com, 1, 'uint8');
%     % write(com, data, 'uint8');
% end
% 
% % dataR = read(com, 10, 'uint8');
