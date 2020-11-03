#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Element Element;
struct Element{
    char site[100];
    Element *suivant;
};

typedef struct Pile Pile;
struct Pile{
    Element *premier;
};

Pile *initialiser(){
    Pile *pile = malloc(sizeof(*pile));
    pile->premier = NULL;
}

void empiler(Pile *pile, char toSite[]){
    Element *nouveau = malloc(sizeof(*nouveau));
    if (pile == NULL || nouveau == NULL)
        exit(EXIT_FAILURE);

    strcpy(nouveau->site, toSite);
    nouveau->suivant = pile->premier;
    pile->premier = nouveau;
}

char* depiler(Pile *pile){
    if (pile == NULL)
        exit(EXIT_FAILURE);

    char *siteDepile;
    Element *elementDepile = pile->premier;

    if (pile != NULL && pile->premier != NULL){
        siteDepile = elementDepile->site;
        pile->premier = elementDepile->suivant;
        // free(elementDepile);
    }

    return siteDepile;
}

void last(Pile *pile){
    if (pile == NULL)
        exit(EXIT_FAILURE);

    Element *actuel = pile->premier;
    if(actuel == NULL)
        printf("Ignored\n");
    else
        printf("%s\n", actuel->site);
}

void back(Pile *masterPile, Pile *slavePile){
    Element *actuel = masterPile->premier;
    if(actuel != NULL)
        empiler(slavePile, depiler(masterPile));
    last(masterPile);
}

void forward(Pile *masterPile, Pile *slavePile){
    Element *actuel = masterPile->premier;
    Element *slaveActuel = slavePile->premier;

    if(slaveActuel == NULL){
        last(slavePile);
        return ;
    }
    if(actuel == NULL){
        empiler(masterPile, depiler(slavePile));
        empiler(masterPile, depiler(slavePile));
    }else{
        empiler(masterPile, depiler(slavePile));
    }
    last(masterPile);
}

int main(){
    Pile *masterPile = initialiser();
    Pile *slavePile = initialiser();
    char command[100];
    char site[100];
    
    empiler(masterPile, "http://www.acm.org/");

    /* Get the command, with size limit. */
    fgets(command, sizeof(command), stdin);
    /* Remove trailing newline, if there. */
    if ((strlen(command) > 0) && (command[strlen (command) - 1] == '\n'))
        command[strlen (command) - 1] = '\0';

    while(strcmp(command, "QUIT") != 0){
        if(command[0] == 'V'){
            slavePile = initialiser();
            strncpy(site, command+6, (strlen(command)+6));
            empiler(masterPile, site);
            last(masterPile);
        }
        else if(command[0] == 'B')
            back(masterPile, slavePile);
        else if(command[0] == 'F')
            forward(masterPile, slavePile);
        
        /* Get the command, with size limit. */
        fgets(command, sizeof(command), stdin);
        /* Remove trailing newline, if there. */
        if ((strlen(command) > 0) && (command[strlen (command) - 1] == '\n'))
            command[strlen (command) - 1] = '\0';
    }
    
    return 0;
}
