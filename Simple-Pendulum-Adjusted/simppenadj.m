#!/usr/bin/octave
# Plotting simppenadj.txt
A      = importdata('simppenadj.txt');
B      = importdata('simppenadjdx.txt');
t      = A(:,1);
theta  = A(:,2);
dtheta = B(:,2);
figure
plot(t,theta)
xlabel('t','FontSize',16,'FontWeight','bold')
ylabel('\theta','FontSize',16,'FontWeight','bold')
title('{d^{2}\theta}/{d{t^{2}}} = -9.8 cos({\theta + {d\theta}/{dt}})','FontSize',18,'FontWeight','bold')
figure
plot(theta,dtheta)
xlabel('\theta','FontSize',16,'FontWeight','bold')
ylabel('d\theta/dt','FontSize',16,'FontWeight','bold')
title('{d^{2}\theta}/{d{t^{2}}} = -9.8 cos({\theta + {d\theta}/{dt}})','FontSize',18,'FontWeight','bold')
