if ~(exist('s','var'))
    s = serial('/dev/ttyUSB0');
    s.BaudRate = 57600;
end
    if ~strcmp(s.status,'open')
    fopen(s);
    pause(1);
    s.status
    end

disp('Ready')
x1 = 0;
y1 = 3;

x2 = 0;
y2 = 6;

x3 = 2.5;
y3 = 4.5;

%Przykadowy pkt wewnatrz przestrzeni roboczej
xc = 1;
yc = 5;
zc = 2;

r = 3;

%Rownanie sfery (x-x0)^2 + (y-y0)^2 + (z-z0)^2 = r^2
z1 = zc + sqrt(  (r*r)  -  ((x1-xc)^2) - ((y1-yc)^2)  );
z2 = zc + sqrt((r*r)-((x2-xc)^2)-((y2-yc)^2));
z3 = zc + sqrt((r*r)-((x3-xc)^2)-((y3-yc)^2));

% rysowanie linii
col1=line([x1 x1], [y1 y1], [0 5]);
col2=line([x2 x2], [y2 y2], [0 5]);
col3=line([x3 x3], [y3 y3], [0 5]);
arm1=line([x1 xc], [y1 yc], [z1 zc]);
arm2=line([x2 xc], [y2 yc], [z2 zc]);
arm3=line([x3 xc], [y3 yc], [z3 zc]);
view(27,10);

%rysowanie kolka
%xc = 0.1 * sin(t) + 1%poczatkowa wartosc xc
xc0 = xc;
yc0 = yc;
zc0 = zc;
clear staraZ1 staraZ2 staraZ3

for t=0:0.05:100
    xc = 0.05 * sin(t) + xc0;
    yc = 0.05 * cos(t) + yc0;
    zc = zc+ 0.001;
    z1 = zc + sqrt(  (r*r)  -  ((x1-xc)^2) - ((y1-yc)^2)  );
    z2 = zc + sqrt((r*r)-((x2-xc)^2)-((y2-yc)^2));
    z3 = zc + sqrt((r*r)-((x3-xc)^2)-((y3-yc)^2));
    set(arm1,'XData',[x1,xc],'YData',[y1,yc],'ZData',[z1,zc]);
    set(arm2,'XData',[x2,xc],'YData',[y2,yc],'ZData',[z2,zc]);
    set(arm3,'XData',[x3,xc],'YData',[y3,yc],'ZData',[z3,zc]);
    %set(col1,'ZData',[z1,zc+5]);
    %set(col2,'ZData',[z1,zc+5]);
    %set(col3,'ZData',[z1,zc+5]);
    if exist('staraZ1')
        Z1Send = z1 - staraZ1;
        Z1Send = Z1Send*10000;
    end
    staraZ1 = z1;
    
    if exist('staraZ2')
        Z2Send = z2 - staraZ2;
        Z2Send = Z2Send*10000;
    end
    staraZ2 = z2;
    
    if exist('staraZ3')
        Z3Send = z3 - staraZ3;
        Z3Send = Z3Send*10000;
        string = ['x ' num2str(ceil(Z1Send)) ' y ' num2str(ceil(Z2Send)) ' z ' num2str(ceil(Z3Send)) '\n'];
        fprintf(s,string);
        while s.bytesavailable == 0 %Tu sobie program czeha na ok, czeka czeka czeka
        end
        while s.bytesavailable 
          a=fscanf(s,'%s',3) ; %co my tam mamy w tym streamie?
          if strcmp(a,'PSA')
             disp('Koniec programu, wcisnieto PSA!!')
             clearvars a
             fclose(s);
            return
          end
        end
    end
    staraZ3 = z3;
    
    
    hold on
    plot3(xc,yc,zc,'o')
end

fclose(s);




