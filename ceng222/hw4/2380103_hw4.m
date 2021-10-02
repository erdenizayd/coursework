N = 21135;
n = 250;
p = 0.62;
TotalWeight = zeros(N,1);
for k = 1 : N
    U = rand(n,1);
    X = sum(U < p);
    weight = 0;

    s = 0; t = 8; m = 0.22;
    for j = 1 : X
        CX = 0; CY = m;
        f = 0;
        while(CY > f)
            D = rand; V = rand;
            CX = s+(t-s)*D; CY = m*V;

            if(CX <= 2)
                f = 0.07*CX;
            elseif(CX <= 5)
                f = -0.02*(CX - 4)*(CX - 4) + 0.22;
            elseif(CX <= 7)
                f = 0.08*(5-CX) + 0.2;
            else
                f = -0.04*CX + 0.32;
            end
        end
        weight = weight + CX;
    end
    TotalWeight(k) = weight;
end

p_est = mean(TotalWeight>640);
expectedWeight = mean(TotalWeight);
stdWeight = std(TotalWeight);
fprintf('Estimated probability = %f\n',p_est);
fprintf('Expected weight = %f\n',expectedWeight);
fprintf('Standard deviation = %f\n',stdWeight);
