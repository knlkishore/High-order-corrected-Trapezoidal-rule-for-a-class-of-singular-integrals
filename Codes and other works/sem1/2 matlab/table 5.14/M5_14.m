%By Kunal Kishore ,16093
% m = inital number of steps ,i.e degree of precision
% from where calculation should start
m=4;

% k ,largest value of steps,i.e  degree of precision 
% till which to calculate
k=2048;

%[a,b] is the interval over which function to be intregated
a=0;
b=1;
n=m;
i = 1 ;
N = ones(10,1);

while (n <= k)
    N(i) =n;
    
    n = n*2;
    i = i+1;
end


%function to be intregated
syms f(x)
f(x) =  x^3 + sin(x);
I_real = double(int(f(x),[a,b]))
%For calculating Trapeziodal Rule
n=m;
i = 1 ;
area_by_T = ones(10,1);
N = ones(10,1);
relative_error = ones(10,1);
j=1;
while (n <= k)
    N(j) = n;
    j =j+1;
    h=(b-a)/n ;
    x=a:h:b ;
    y = f(x) ;
    area_by_T(i) = trapz(x,y);
    n = n*2;
    i = i+1;
end


error =abs(area_by_T - ones(10,1)*I_real);

for i =1:10
    relative_error(i) = error(i) / error(1);
end




table(N, area_by_T , error ,relative_error)
