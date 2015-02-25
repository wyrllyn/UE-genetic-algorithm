#include "bandit.h"

//is OK
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

// IS OK
int choix_uniforme(int nba) {
    float ra = (float)rand()/(float)(RAND_MAX/1);
    return floor(1+(nba) * ra);
}

// IS OK
int tirage_aleatoire(float* proba, int sizeP) {
    float base = 0;
    int index = -1;
    float ra = (float)rand()/(float)(RAND_MAX/1);
    float* wheel = malloc(sizeof(float) * sizeP);
    for (int i = 0; i < sizeP; i++) {
       // printf("tirage_aleatoire : i = %d, base = %f, proba = %f \n", i, base, proba[i]);
        wheel[i] = base + proba[i];
        base += proba[i];
        if (wheel[i] > ra ) {
            return i+1;
        }
    }
    return 1;
}


//is OK
int UCB1(float* R, int sizeR, int iter, int* Actions, int sizeA) {
    float * tempReward = (float*)malloc(sizeof(float) * sizeR);
    for (int i = 0; i < sizeR; i++) {
        tempReward[i] = R[i] + sqrt((2*log10(iter))/(Actions[i]+1));
    }
    int * Amax = ActionMax(tempReward, sizeR); // choix équitable
    int a = Amax[choix_uniforme(sizeA)-1];
    //free(Amax);
   // printf(" UCB : a value is %d \n", a);
    return a + 1;
}


//IS OK
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
   // printf("adaptive_pursuit : Pmax = %f \n", Pmax );
    int a = -1;
    //best et nbst ??
    int best = max(R, sizeR);
    int Nbest = best;
  //  printf("Before nbest is %d, proba is %f \n", Nbest, (*Proba)[Nbest]);
    float add = alpha * (Pmax - (*Proba)[Nbest]);
    (*Proba)[Nbest] += add;
  //  printf("After nbest is %d, proba is %f \n", Nbest, (*Proba)[Nbest]);
  //  printf("add was %f \n", add);
    for (int i = 0; i < sizeR; i++) {
        if (i != Nbest) {
         //   printf("------ former value = %f \n", (*Proba)[i]);
            float add2 = alpha * (Pmin - (*Proba)[i]);
            (*Proba)[i] += add2;
         //   printf("-------------at iteration %d, add2 = %f \n", i, add2);
        }
    }
    a = tirage_aleatoire((*Proba), sizeR);
    return a;
}

int max(float* R, int sizeR) {
    float tmp_val = -1;
    int toReturn = -1;
    for (int i = 0; i < sizeR; i++) {
        if (R[i] >= tmp_val) {
            toReturn = i;
            tmp_val = R[i];
        }
    }
    return  toReturn;
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

    // r moyenne de récompenses depuis le début (voir fin de l algo du prof)
       //     for (int i = 0; i < n ; i++) Actions[i] = 0; // initialiser en dehors
       //     for (int i = 0; i < n ; i++) R[i] = 0; // intialiser en dehors, équivalent à chaque mutation
    switch(method) {
        case 1:
            //OK
            action = choix_uniforme(n);
            break;
        case 2:
            // OK TODO : check what iter must be
            action = UCB1(*R, n, iter, *Actions, n);
            break;
        case 3:
            // KO
            action = adaptive_pursuit(*R,n, proba, 0.01, 0.8);
            break;
        case 4:
            // OK
            action = roulette_adaptative(*R,n,proba,n,0.01);
            break;
    }
    (*Actions)[action-1]++;


    return action;
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
