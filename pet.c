#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//constants
#define name_length 50
#define max_hunger 100
#define max_boredom 100
#define max_fatigue 100

struct Pet
{
    char name[name_length];
    char type[10];
    int hunger;
    int boredom;
    int fatigue;
    char favoriteFood[20];
    int treatsGiven;
};

// Function prototypes
void displayPet(struct Pet *pet);
void feedPet(struct Pet *pet);
void playWithPet(struct Pet *pet);
void letPetSleep(struct Pet *pet);
void giveTreat(struct Pet *pet);
void updateStatsOverTime(struct Pet *pet);

// Stats
void displayPet(struct Pet *pet)
{
    printf("\n--- Meet Your Pet ---\n");
    printf("%s the %s\n", (*pet).name, (*pet).type);

    if (strcmp((*pet).type, "dog") == 0)
    {
        printf("      / \\__\n");
        printf("    (    @\\___\n");
        printf("    /         O\n");
        printf("   /   (_____/ \\\n");
        printf("  /_____/   U  |\n");
    }
    else
    {
        printf("\n   /\\_/\\\n");
        printf("  ( o.o )\n");
        printf("   > ^ <\n");
    }

    printf("\nHunger: %d%%\n", (*pet).hunger);
    printf("Boredom: %d%%\n", (*pet).boredom);
    printf("Fatigue: %d%%\n", (*pet).fatigue);
    printf("Treats Left: %d\n", 3 - (*pet).treatsGiven);
}

// Feeding
void feedPet(struct Pet *pet)
{
    char food[20];
    printf("What will you feed %s? (Options: meat, fish, milk): ", (*pet).name);
    scanf("%s", food);

    int hungerReduction = rand() % 21 + 20;  // Reduction between 20 and 40

    if (strcmp(food, "meat") == 0)
    {
        hungerReduction += 10;
    }
    else if (strcmp(food, "fish") == 0)
    {
        hungerReduction += 5;
    }

    if (strcmp((*pet).favoriteFood, food) == 0)
    {
        printf("%s happily munches on their favorite food: %s! Hunger reduced more effectively!\n", (*pet).name, food);
        hungerReduction = hungerReduction * 1.5;  // Multiply effectiveness
    }
    else
    {
        printf("%s eats the %s. They seem satisfied.\n", (*pet).name, food);
    }

    if ((*pet).hunger >= hungerReduction)
    {
        (*pet).hunger -= hungerReduction;
    }
    else
    {
        (*pet).hunger = 0;
    }

    if ((*pet).favoriteFood[0] == '\0')
    {  // Assign favorite food if not set
        strcpy((*pet).favoriteFood, food);
        printf("%s's favorite food is now %s!\n", (*pet).name, food);
    }
}

// Boredom
void playWithPet(struct Pet *pet)
{
    char activity[20];
    printf("How do you want to play with %s? ", (*pet).name);
    if (strcmp((*pet).type, "dog") == 0)
    {
        printf("(Options: fetch, tug, chase): ");
    }
    else
    {
        printf("(Options: string, box, laser): ");
    }
    scanf("%s", activity);

    int boredomReduction = rand() % 21 + 10;  // boredom reduction between 10 and 30

    if (strcmp((*pet).type, "dog") == 0)
    {
        if (strcmp(activity, "fetch") == 0)
        {
            boredomReduction += 10;
        }
        else if (strcmp(activity, "tug") == 0)
        {
            boredomReduction += 5;
        }
    }
    else
    {
        if (strcmp(activity, "laser") == 0) {
            boredomReduction += 10;
        }
        else if (strcmp(activity, "string") == 0)
        {
            boredomReduction += 5;
        }
    }

    if ((*pet).boredom >= boredomReduction)
    {
        (*pet).boredom -= boredomReduction;
    }
    else
    {
        (*pet).boredom = 0;
    }

    printf("%s has fun playing %s! Boredom decreases by %d%%.\n", (*pet).name, activity, boredomReduction);
}

// Fatigue
void letPetSleep(struct Pet *pet)
{
    int sleepReduction = rand() % 31 + 30;  // Fatigue recovery between 30 and 60

    if ((*pet).fatigue >= sleepReduction)
    {
        (*pet).fatigue -= sleepReduction;
    }
    else
    {
        (*pet).fatigue = 0;
    }

    printf("%s takes a nap and feels much better! Fatigue decreases by %d%%.\n", (*pet).name, sleepReduction);
}

// Treat
void giveTreat(struct Pet *pet)
{
    if ((*pet).treatsGiven >= 3)
    {
        printf("No more treats left! %s has had enough for today.\n", (*pet).name);
        return;
    }

    int hungerReduction = rand() % 21 + 20;  // Reduction between 20 and 40
    int boredomReduction = rand() % 21 + 20; // Reduction between 20 and 40

    if ((*pet).hunger >= hungerReduction)
    {
        (*pet).hunger -= hungerReduction;
    }
    else
    {
        (*pet).hunger = 0;
    }

    if ((*pet).boredom >= boredomReduction)
    {
        (*pet).boredom -= boredomReduction;
    }
    else
    {
        (*pet).boredom = 0;
    }

    if ((*pet).fatigue >= 30)
    {
        (*pet).fatigue -= 30;
    }
    else
    {
        (*pet).fatigue = 0;
    }

    (*pet).treatsGiven++;
    printf("%s enjoys a tasty treat! Hunger, boredom, and fatigue are all reduced.\n", (*pet).name);
}

// Gradually increase stats over time
void updateStatsOverTime(struct Pet *pet)
{
    (*pet).hunger += rand() % 11 + 5;  // Hunger increases by 5-15
    if ((*pet).hunger > max_hunger)
    {
        (*pet).hunger = max_hunger;
    }

    (*pet).boredom += rand() % 11 + 5; // Boredom increases by 5-15
    if ((*pet).boredom > max_boredom)
    {
        (*pet).boredom = max_boredom;
    }

    (*pet).fatigue += rand() % 6 + 5;  // Fatigue increases by 5-10
    if ((*pet).fatigue > max_fatigue)
    {
        (*pet).fatigue = max_fatigue;
    }
}

int main()
{
    struct Pet pet;
    char choice[10];
    int action;

    srand(time(NULL));  // Seed the random number generator

    printf("Do you want a dog or a cat? ");
    scanf("%s", choice);

    if (strcmp(choice, "dog") != 0 && strcmp(choice, "cat") != 0) {
        printf("Hmm, we only have dogs and cats for now. Defaulting to dog!\n");
        strcpy(choice, "dog");
    }

    strcpy(pet.type, choice);
    printf("What will you name your %s? ", choice);
    scanf("%s", pet.name);
   //random stats 50-100
    pet.hunger = rand() % 51 + 50;
    pet.boredom = rand() % 51 + 50;
    pet.fatigue = rand() % 51 + 50;
    pet.treatsGiven = 0;

    while (1)
    {
        displayPet(&pet);
        printf("\nActions:\n1. Feed\n2. Play\n3. Sleep\n4. Give Treat\n5. Exit\n");
        printf("Choose an action: ");
        scanf("%d", &action);

        switch (action)
        {
            case 1:
                feedPet(&pet);
                break;
            case 2:
                playWithPet(&pet);
                break;
            case 3:
                letPetSleep(&pet);
                break;
            case 4:
                giveTreat(&pet);
                break;
            case 5:
                printf("Goodbye! %s waves goodbye with their paw.\n", pet.name);
                return 0;
            default:
                printf("Hmm, that doesn't seem right. Try again!\n");
        }

        updateStatsOverTime(&pet);  // increasing stats
    }
}
