clear all
close all
clc

N=20; %Puntos para el histograma
% Importamos el archivo que contiene los tiempos en que llega el paquete al
% sistema
A = importdata('tllegadas.txt');

for i=1:length(A)-2
    dif(i)=abs(A(i)-A(i+1));    % Diferencia entre cada llegada para calcular el tiempo entre llegadas
end
subplot(1,2,1)
hist(dif,N);
grid on
title('Tiempo entre llegadas')

% Importamos los tiempos que estan los paquetes en el sistema
B = importdata('tsistema.txt');

subplot(1,2,2)
hist(B,N)
title('Tiempo en el sistema')