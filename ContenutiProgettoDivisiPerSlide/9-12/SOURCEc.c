// basic file operations
#include <iostream>
#include <fstream>
// srand, rand
#include <stdlib.h>
// time
#include <time.h>
using namespace std;

// Number of people in each dataFile (rows)
#define N_PEOPLE 1000
// Number of life challenges for each person (columns)
#define N_CHALLENGES 10000

// Create 4 data files:
// - Full fail(0)&success(1) file - stringFull
// - Abridged fail(0)&success(1) file - stringAbr
// - Full motivation(0-100) file - stringFullM
// - Abridged motivation(0-100) file - stringAbrM
// The int indicate what happen when the person fail:
// - '-1' (negative attitude) their motivation decrease;
// - '0' (indifferent attitude) their motivation doesn't change;
// - '1' (positive attitude) their motivation increase.
void createData(string, int);

int main()
{
    // Initialize casual numbers
    srand(time(NULL));
    // Create data files for people with a negative attitude
    createData("negative", -1);
    // Create data files for people with a indifferent attitude
    createData("indifferent", 0);
    // Create data files for people with a positive attitude
    createData("positive", 1);
    return 0;
}

void createData(string name, int attitude)
{
    // Data stream for writing files
    ofstream Full, Abr, FullM, AbrM;
    // Creating all files
    Full.open("C:\\Users\\Utente\\Desktop\\Project\\C_PROGRAM\\Data\\"
    + name + "\\" + name + "Full.csv");
    Abr.open("C:\\Users\\Utente\\Desktop\\Project\\C_PROGRAM\\Data\\"
    + name + "\\" + name + "Abr.csv");
    FullM.open("C:\\Users\\Utente\\Desktop\\Project\\C_PROGRAM\\Data\\"
    + name + "\\" + name + "FullM.csv");
    AbrM.open("C:\\Users\\Utente\\Desktop\\Project\\C_PROGRAM\\Data\\"
    + name + "\\" + name + "AbrM.csv");
    // Constant for each person
    int environment;
    // Variable for each person (depends on fail&success)
    int motivation;
    // A higher weighted average of these two
    // (1 for environment, 3 for motivation) mean more success probability
    
    // Creating header for each column of Full files
    FullM << ',' << 0;
    for (int i = 1; i <= N_CHALLENGES; i++){
        Full << ',' << i;
        FullM << ',' << i;
    }
    Full << ',' << "Success%";
    // Creating header for each column of Abr files
    AbrM << ',' << 0;
    for (int i = N_CHALLENGES / 5; i <= N_CHALLENGES; i = i + N_CHALLENGES / 5){
        Abr << ',' << i;
        AbrM << ',' << i;
    }

    for (int i = 1; i <= N_PEOPLE; i++){
        // i-th person
        Full << '\n' << i;
        FullM << '\n' << i;
        Abr << '\n' << i;
        AbrM << '\n' << i;
        // constant value of the person's environment
        environment = rand() % 101;
        // starting value of the person's motivation
        motivation = N_CHALLENGES * 5 * 3 / 2;
        // Adding the motivation that the person
        // has before the first life challenge
        FullM  << ',' << motivation;
        AbrM  << ',' << motivation;
        // number of successes of a person
        int successes = 0;
        // number of successes of a person that are reset each N_CHALLENGES / 5
        // for Abridged fail(0)&success(1) file
        int successesAbr = 0;
        // life challenges of the person and their effects
        for (int j = 1; j <= N_CHALLENGES; j++){
	    int personValue = (environment + 3 * motivation * 10 / N_CHALLENGES) / 4;
	    int challengeValue = rand() % 101;
            if (personValue > challengeValue){
                // success
                successes++;
                successesAbr++;
                Full << ',' << 1;
                motivation += 6;
            } else {
                // fail
                Full << ',' << 0;
                motivation += 6 * attitude;
            }
            if (motivation > N_CHALLENGES * 10){
                motivation = N_CHALLENGES * 10;
            }
            if (motivation < 0){
                motivation = 0;
            }
            FullM << ',' << motivation;
            if (j % (N_CHALLENGES / 5) == 0){
                if (successesAbr > N_CHALLENGES / 10){
                    Abr << ',' << 1;
                } else {
                    Abr << ',' << 0;
                }
                successesAbr = 0;
                AbrM << ',' << motivation;
            }
        }
    Full << ',' << (float) successes * 100 / N_CHALLENGES;
    }
// Closing data steam for all files
Full.close();
Abr.close();
FullM.close();
AbrM.close();
}