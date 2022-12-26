q = pi ; 
alpha = 1.3;

a = 0;
b = 2*pi;
h = (b-a)/2;
n = 200;
X = linspace(q-alpha,q+alpha,n) ;
%% step-1-------------------------------------------------------------------------------------------

syms f(x,t) v(x) k(x,t) singular(x,t)
w=2;
k(x,t) = 1;
v(x) = exp( 2*cos(8*x)+sin(9*x) );
singular(x,t) = log( w* (1 - cos(t-x) ) );
f(x,t) = v(x)*k(x,t)*singular(x,t);

F(x) = f(x,q) ;


X_c = ones(1,length(X))* X(1); 
F_c = ones(1,length(X))* F(X(1));
%% step-2-------------------------------------------------------------------------------------------


for k = 1: length(X)
    
    %to clean the previous frame
    clf('reset')

    
    X_k = X(k);
    F_k = F(X_k);
    
    plot(X_k,F_k,'mo','LineWidth',2)  %to draw current plot in animation
    ylim([-105 10])
    xlim([  q-(alpha + 0.1)    q+(alpha + 0.1)    ] )
    txt = ['|t-\theta| ='  num2str( abs( q-X_k ) )];
    text(q+alpha/2,5,txt)
    %title(txt)
    hold on
    %till this plot
    X_c(k) = X_k;
    F_c(k) = F_k;
   
    plot(X_c(1:k),F_c(1:k),'k-')
    

    
    movievector(k) = getframe ;
end
%% step-3 Save the movie
hold off

curve = ['Curve_alpha'  num2str(alpha) '_points_' num2str(n)];

mywriter = VideoWriter(curve);
mywriter.FrameRate = 30 ;


open(mywriter);
writeVideo(mywriter , movievector);
close(mywriter);

close all