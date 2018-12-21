clear all
close all

%% se carga el fichero con las probabilidades de perdida
filename = 'prob_perdida.txt';
[A,delimiterOut]=importdata(filename);

% Parametros del grupo
M = 40; %numero de fuentes
n = 10; % numero de medidas, cantidad de veces que se ha realizado el experimento
a=1;    % inicializacion

%formula de engset con una fuente más.
 
for i=1:M:M*n
  B(:,a)=A(i:i+(M-1));
  a=a+1;
 end

for i = 1:M
  prob_medias(i) = mean(B(i,:));
end 

% grafica prob perdida
plot(prob_medias);

x=[1:40]; % fuentes
y=prob_medias;
figure(1)
plot(x,y)
figure(2)
%% aproximacion con varios polinomios (piecewise polynomial).
breaks = linspace (0, 40, 41); 
pp1 = splinefit (x, y, breaks);
pp2 = splinefit (x, y, 10);  
xx = linspace (0, 40, 400);
y1 = ppval (pp1, xx);
y2 = ppval (pp2, xx);
%plot (x, y,'ro','markersize',4,'markerfacecolor','r', xx, [y1; y2])
plot (x, y,'.', xx, [y1; y2]) 
% para ver mejor las aproximaciones, se pone un "."
% en cada punto, en vez de circulos rellenos.
axis tight
ylim auto
legend ({"data", "41 breaks, 40 pieces", "11 breaks, 10 pieces"})

x=[1:40];
y=prob_medias(20:end);
x=x(20:end);
p=polyfit(x,log(y),1);
x=[1:40];
y =prob_medias;
fprintf('exponente a= %2.3f\n',p(1));
fprintf('coeficiente c = %3.3f\n',exp(p(2)));
figure(3)
hold on
plot(x,y,'ro','markersize',4,'markerfacecolor','r')
z=@(x) exp(p(2))*exp(x*p(1)); % aproximacion con una exponencial
fplot(z,[x(1),x(end)])
xlabel('x')
ylabel('y')
grid on
title('Regresion exponencial')
hold off


%% se carga el fichero.
data=importdata('re_ocu.txt');
tiempo=data(:,1);
estado=data(:,2);
t_total=10000; % tiempo total.
ocupado=0;
tiempoocupado=0;
itera=0;
j=0;
for k=1:length(tiempo)    
    if tiempo(k)==t_total 
        itera=itera+1;
        porocu=(tiempoocupado/t_total)*100; %porcentaje del tiempo ocupado
        tiempos(itera)=porocu;
        tiempoocupado=0;
    end
    
    if estado(k)==0;% Ocupado
        tiempoini=tiempo(k);
        j=0;
        while j~=1
            %Problema cuando el que esta ocupado es el ultimo
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


%% se recuerdan los valores del grupo:
M = 40; %numero de fuentes
n = 10; % numero de medidas, cantidad de veces que se ha realizado el experimento
A=tiempos;
total=zeros(1,40);
for g=0:9
    total=tiempos(((g*40)+1):((g*40)+40))+total;

end
total=total/10;
N=1:40;
figure(4)
plot(N,total)
%xlabel('Numero de Fuentes');
%ylabel('% Tiempo con todos los recursos ocupados')



y=total;
x=1:40;
figure(5)
breaks = linspace (0, 40, 41); 
pp1 = splinefit (x, y, breaks);
pp2 = splinefit (x, y, 10); 
xx = linspace (0, 40, 400); % 10 medidas x 40 fuentes
y1 = ppval (pp1, xx);
y2 = ppval (pp2, xx);
plot (x, y,'.', xx, [y1; y2]) 
% para ver mejor las aproximaciones, se pone un "."
% en cada punto, en vez de circulos rellenos.
axis tight
ylim auto
legend ({"data", "41 breaks, 40 pieces", "11 breaks, 10 pieces"})
