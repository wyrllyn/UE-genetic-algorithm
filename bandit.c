#include "bandit.h"


int* ActionMax(float* E, int sizeE) {
    int valmax = E[0];
    int* Amax = malloc(sizeof(int) * sizeE);
    Amax[0] = 1;
    int j = 0;
    for (int i = 1; i < sizeE; i++) {
        if (E[i] > valmax) {
            Amax[0] = i;
            valmax = E[i];
            j = 0;
        }
        else {
            if (E[i] == valmax) {
                j++;
                Amax[j] = i;
            }
        }
    }
    return Amax;
}

int choix_uniforme(int nba) {
    float ra = (float)rand()/(float)(RAND_MAX/1);
    return floor(1+(nba) * ra);
}

int tirage_aleatoire(float* proba, int sizeP) {
    float base = 0;
    int index = -1;
    float ra = (float)rand()/(float)(RAND_MAX/1);
    float* wheel = malloc(sizeof(float) * sizeP);
    for (int i = 0; i < sizeP; i++) {
        wheel[i] = base + proba[i];
        base += proba[i];
        if (wheel[i] > ra ) {
            return i;
        }
    }
    return index;
}

int select_greedy(float* R, int sizeR) {
    int toReturn = -1;
    int tmp = 0;
    for (int i = 0; i < sizeR; i++) {
        tmp += R[i];
    }
    if (tmp == 0) {
        toReturn = choix_uniforme(sizeR);
    }
    else {
        int * Amax = ActionMax(R, sizeR) ;
        toReturn = Amax[choix_uniforme(sizeR)];
        free(Amax);
    }
    return toReturn;
}

int select_egreedy(float* R, int sizeR, float epsilon) {
    int toReturn = -1;
    float tmp = (float)rand()/(float)(RAND_MAX/1);
    if (tmp > epsilon) {
        toReturn = select_greedy(R, sizeR);
    }
    else {
        toReturn = choix_uniforme(sizeR);
    }
    return toReturn;
}


int UCB1(float* R, int sizeR, int iter, int* Actions, int sizeA) {
    float * tempReward = (float*)malloc(sizeof(float) * sizeR);
    for (int i = 0; i < sizeR; i++) {
        tempReward[i] = R[i] + sqrt((2*log10(iter))/(Actions[i]+1));
    }
    int * Amax = ActionMax(tempReward, sizeR); // choix équitable
    int a = Amax[choix_uniforme(sizeA)];
    free(Amax);
    return a;
}


//warning proba = float*
int roulette_adaptative(float* R, int sizeR, float ** Proba, int sizeP, float Pmin) {
    int toReturn = 0;
    int tmp = 0;
    for (int i = 0; i < sizeR; i++) {
        tmp += R[i];
    }
    if (tmp == 0) {
        toReturn = tirage_aleatoire((*Proba), sizeP);
    }
    else {
        for (int i = 0; i < sizeR; i++) {
            (*Proba)[i] = Pmin + ((1-sizeR*Pmin)*(R[i]/tmp));
              for (int j = 0; j < sizeR; j++) {
                      tmp += R[j];
             }
        }
        toReturn = tirage_aleatoire((*Proba), sizeP);
    }
    return toReturn;
}

int adaptive_pursuit(float* R, int sizeR, float** Proba, float Pmin, float alpha) {
    float Pmax = 1 - ((sizeR - 1) * Pmin);
    int a = -1;
    //best et nbst ??
    int best = Pmax;
    int Nbest = Pmax;
    (*Proba)[Nbest] += alpha * (Pmax - (*Proba)[Nbest]);
    for (int i = 0; i < sizeR; i++) {
        if (i != Nbest) (*Proba)[i] += alpha * (Pmin - (*Proba[i]));
    }
    a = tirage_aleatoire((*Proba), sizeR);
    return a;
}


// n = nb actions possibles = taille de proba, R, Action


int choice(int n, float ** proba, float ** R, int ** Actions, int method, int iter) { //method en paramètre
    // PGAIN ?
    // N ? (length de pgain )

   // int n = 1; // TODO set real value 
   // float * proba = malloc(sizeof(float) * n); 
    //int * Actions = malloc(sizeof(int) * n);
   // float * R = malloc(sizeof(int) * n); // récompenses
    int action;

    for (int i = 0; i < n; i++){
        (*proba)[i] = 1/n;
    }

    // r moyenne de récompenses depuis le début (voir fin de l algo du prof)
       //     for (int i = 0; i < n ; i++) Actions[i] = 0; // initialiser en dehors
       //     for (int i = 0; i < n ; i++) R[i] = 0; // intialiser en dehors, équivalent à chaque mutation
    switch(method) {
        case 1:
            action = select_greedy(*R,n);
            break;
        case 2:
            action = select_egreedy(*R,n, 0.05);
            break;
        case 3:
            action = UCB1(*R, n, iter, *Actions, n);
            break;
        case 4:
            action = adaptive_pursuit(*R,n, proba, 0.01, 0.8);
            break;
        case 5:
            action = roulette_adaptative(*R,n,proba,n,0.01);
            break;
    }
    (*Actions)[action]++;
                //TODO : finish
                // Gain = total


    return 0;
}
/*

//A=[0,0,0,0,0,0,0,0]
//PGain=rand(A)
//N=length(PGain)
//for i=1:floor(N/2)
//    PGain(i)=0
//end

PGain=[0,1]
N=length(PGain)

T=5000;
nbruns=10;

for i=1:N
    Proba(i)=1/N
end

for method=1:5 

for run=1:nbruns 
//initialisation
for i=1:N
    Actions(i)=0
end
for i=1:N
    R(i)=0
end
// début des itérations
for i=1:T
    select method 
    case 1 then action=select_greedy(R),
    case 2 then action=select_egreedy(R,0.05),
    case 3 then action=UCB1(R,i,Actions),
    case 4 then [action,Proba]=adaptive_pursuit(R,Proba,0.01,0.8),
    case 5 then [action,Proba]=roulette_adaptative(R,Proba,0.01),
    end    
    //comptage de l'action choisie
    Actions(action)=Actions(action)+1;
    if (rand()<=PGain(action)) then 
        R(action)=(((Actions(action)-1)*R(action))+1)/Actions(action)
        if  (i>1) then
           //Gain(run,i)=(((i-1)*Gain(run,(i-1))+1))/i
           Gain(run,i)=Gain(run,(i-1))+1
        else 
           Gain(run,1)=1
        end
    else
        R(action)=((Actions(action)-1)*R(action))/Actions(action)
        if  (i>1) then
           //Gain(run,i)=((i-1)*Gain(run,(i-1)))/i
           Gain(run,i)=Gain(run,(i-1))
        else 
           Gain(run,1)=0
        end 
    end
end

//range_g=1:T;
//plot(range_g,Gain(range_g),'b');

end //run


for i=1:T
   somme=0
   for run=1:nbruns
    somme=somme+Gain(run,i)
   end
   Gain_moy(i)=somme/nbruns
end

range_g=1:T;

select method 
    case 1 then plot(range_g,Gain_moy(range_g),'y'),
    case 2 then plot(range_g,Gain_moy(range_g),'b'),
    case 3 then plot(range_g,Gain_moy(range_g),'r'),
    case 4 then plot(range_g,Gain_moy(range_g),'g'),
    case 5 then plot(range_g,Gain_moy(range_g),'c'),
    end 

end //method


*/
