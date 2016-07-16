#!/usr/bin/octave
# Plotting simppenadj.txt
A      = importdata('simppenadj.txt');
B      = importdata('simppenadjdx.txt');
t      = A(:,1);
theta  = A(:,2);
dtheta = B(:,2);
figure(1)
plot(t,theta)
H1 = xlabel('t','FontSize',16,'FontWeight','bold')
set(H1, 'interpreter', 'latex')
J1 = ylabel('\theta','FontSize',16,'FontWeight','bold')
set(J1, 'interpreter', 'latex')
K1 = title('{d^{2}\theta}/{d{t^{2}}} = -9.8 cos({\theta + {d\theta}/{dt}})','FontSize',18,'FontWeight','bold')
set(K1, 'interpreter', 'latex')
saveas(1,"simppenadj-standard-plot.png")
figure(2)
plot(theta,dtheta)
H2 = xlabel('\{theta}','FontSize',16,'FontWeight','bold');
set(H2, 'interpreter', 'latex');
J2 = ylabel('d\{theta}/dt','FontSize',16,'FontWeight','bold');
set(J2, 'interpreter', 'latex');
K2 = title('{d^{2}\{theta}}/{d{t^{2}}} = -9.8 cos({\{theta} + {d\{theta}}/{dt}})','FontSize',18,'FontWeight','bold');
set(K2, 'interpreter', 'latex');
saveas(2,"simppenadj-phase-plot.png")
