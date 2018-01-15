s = serial('/dev/ttyUSB0');
s.BaudRate = 57600;
fopen(s);
fprintf(s,'x 200 y 200 z 200'); % na poczatku zeby sprawdzic