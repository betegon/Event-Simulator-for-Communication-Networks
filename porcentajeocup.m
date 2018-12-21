clear all
close all
clc
clear all
close all

data=importdata('re_ocu.txt');
tiempo=data(:,1);
estado=data(:,2);
t_total=10000;
ocupado=0;
tiempoocupado=0;
itera=0;
j=0;
for k=1:length(tiempo)
    
    if tiempo(k)==t_total 
        itera=itera+1;
        porocu=(tiempoocupado/t_total)*100; %%porcentaje del tiempo ocupado
        tiempos(itera)=porocu;
        tiempoocupado=0;
    end
    
    if estado(k)==0;%Ocupado
        tiempoini=tiempo(k);
        j=0;
        while j~=1
            %Problema cuando el que esta ocupado es el ultimoooooo
            k=k+1;
            j=estado(k); %comprobamos si se ha liberado
            
            if tiempo(k)<tiempo(k-1)
             tiempoliberacion=tiempo(k-1); %Tiempo en que se ha liberado el recurso
             j=1;
             k=k-1;
            else
            tiempoliberacion=tiempo(k); %Tiempo en que se ha liberado el recurso
            end
        end
        
        tiempoocupado=(tiempoliberacion-tiempoini)+tiempoocupado;
        
    end
    
end

M = 40; %numero de fuentes
n = 10; % numero de medidas, cantidad de veces que se ha realizado el experimento
A=tiempos;
total=zeros(1,40);
for g=0:9
    total=tiempos(((g*40)+1):((g*40)+40))+total;

end
total=total/10;
N=1:40;
figure()
plot(N,total)
%xlabel('Numero de Fuentes');
%ylabel('% Tiempo con todos los recursos ocupados')






%%parte de miguel, añadida a lo de pablo
y=total;
x=1:40;



figure()
breaks = linspace (0, 40, 41); % 41 breaks, 40 pieces
pp1 = splinefit (x, y, breaks);
%% Breaks interpolated from data
pp2 = splinefit (x, y, 10);  % 11 breaks, 10 pieces


% PLOTTTTTTTTTTTTTTTTT
%  In situations where a single polynomial isn’t good enough, a solution is to use several polynomials pieced together.
% The function splinefit fits a piecewise polynomial (spline) to a set of data. 
% ref:  https://octave.org/doc/v4.4.0/Polynomial-Interpolation.html
xx = linspace (0, 40, 400);
y1 = ppval (pp1, xx);
y2 = ppval (pp2, xx);
%plot (x, y,'ro','markersize',4,'markerfacecolor','r', xx, [y1; y2])
plot (x, y,'.', xx, [y1; y2]) % para ver mejor las aproximaciones, ponemos un "."
% en cada punto, en vez de circulos rellenos.

axis tight
ylim auto
legend ({"data", "41 breaks, 40 pieces", "11 breaks, 10 pieces"})



