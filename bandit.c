#include "bandit.h"

/*
function [a]=select_greedy(R)
    K=length(R);
     if sum(R)==0 then 
        a = choix_uniforme(K),
        else
        Amax=ActionMax(R); // choix équitable
      a=Amax(choix_uniforme(length(Amax)));
     end;
endfunction


function [a]=select_egreedy(R,epsilon)
    K=length(R);
    greedy = rand()>epsilon;
    if greedy then
    a=select_greedy(R),
    else 
    a = choix_uniforme(K),
    end;
endfunction

function [a]=UCB1(R,iter,Actions)
    for i=1:length(R)
       TempReward(i)=R(i)+sqrt((2*log10(iter))/(Actions(i)+1)),
    end;
      Amax=ActionMax(TempReward); // choix équitable
      a=Amax(choix_uniforme(length(Amax)));
endfunction

function[a,NewProba]=roulette_adaptative(R,Proba,Pmin)
    K=length(R);
    if sum(R)==0 then 
        a = tirage_aleatoire(Proba),
        NewProba = Proba,
        else
        for i=1:K
            NewProba(i)= Pmin + ((1-K*Pmin)*(R(i)/sum(R))),
        end,
        a = tirage_aleatoire(NewProba),
     end;    
endfunction

function [a,NewProba]=adaptive_pursuit(R,Proba,Pmin,alpha)
    K=length(Proba);
    Pmax=1-((K-1)*Pmin);
    // m à j des probabilités de sélection
    [Best,Nbest]=max(R);
    NewProba(Nbest)= Proba(Nbest) + alpha*(Pmax-Proba(Nbest));
    for i=1:K
        if i<>Nbest then 
            NewProba(i)= Proba(i)  + alpha*(Pmin - Proba(i))
        end
    end;
    // tirage aléatoire
    a=tirage_aleatoire(NewProba);
endfunction

function [a]=choix_uniforme(nba)
    a = floor(1+(nba)*rand()),
endfunction

function Amax=ActionMax(E)
    valmax=E(1);
    Amax(1)=1;
    j=1;
    for i=2:length(E)
        if E(i)>valmax then
            clear Amax,
            Amax(1)=i,
            valmax=E(i),
            j=1,
        else
            if E(i)==valmax then
                j=j+1;
            Amax(j)=i;
            end,
        end;
    end;
endfunction;

function [a]=tirage_aleatoire(Proba)
    nba=length(Proba),
    base=0;
    for i=1:nba,
            Wheel(i)=base+Proba(i),
            base=base+Proba(i),
        end; 
    candidats=find(Wheel>rand());
    a=candidats(1);
endfunction

*/