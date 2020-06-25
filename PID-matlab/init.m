s = tf('s');
p = 10.275/(s*(0.001*s + 1));
kp = 0.001/(10.275*0.001/4);
ki=0;
kd=0;
ts = 0.01;

pAulaTeorica = 1/(1+s);
Kr = 0.9828;
Tr = 0.9708;
pAulaReal = 0.9828/(1+ 0.9708*s);

%calculo Sintese Direta para planta Teorica
%Kp = TalProcesso  / TalDesejado.KProcesso
%TalDesejado = TalProcesso/4 (pode ser de 1 a 4 vezes mais tapido sem obter
%overshoot
%Ki = 1/ TalProcesso

%ganhos do processo Teorico
KpT = 1 / ((1/4)*1);
KiT = 1 / 1;
KdT = 0;
%ganhos processo Real
KpR = Tr / ((Tr/4)*Kr);
KiR = 1 / Tr;
KdR = 0;

ts = 0.1;


