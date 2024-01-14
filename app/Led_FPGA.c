#include <stdio.h>
#include "system.h"
#include "sys/alt_sys_init.h"
#include <io.h>
#include <alt_types.h>
#include <sys/alt_irq.h>
#include "altera_avalon_pio_regs.h"


volatile __uint8_t data = 0x01; 
volatile __uint8_t chaser_speed;

// Gestionnaire d'interruption pour un bouton switch key
static void irqhandler_switch_key1(void* context, alt_u32 id)
{     
    // lorsqu'on atteint data = 0x80, la 8ème led est allumé et on revient à la première (chenillard)
    //Cette méthode évite une boucle for coûteuse
    if (data == 0x80){
        data = 0x01;
    }
    // Envois la valeur de data au PIO_0_BASE et allume ainsi la led voulu
    IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE,data);

    // Pause dépendante de 'chaser_speed' pour contrôler la vitesse d'animation
    usleep((16-chaser_speed)*10000); //Plus chaser_speed augmente plus le temps entre chaque led raccourci

    // Décaler 'data' d'un bit vers la gauche pour la prochaine utilisation
    data = data << 1;
}

// Gestionnaire d'interruption pour un switch
static void irqhandler_switch(void* context, alt_u32 id)
{
    // Lire la valeur actuelle du switch 
    chaser_speed = IORD_ALTERA_AVALON_PIO_DATA(PIO_2_BASE); 

    // Afficher l'état actuel du switch et la vitesse du chenillard
    alt_printf("chaser_speed = %x\n", chaser_speed);

    // Réinitialise le registre pour effacer l'interruption
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_2_BASE, 0x0F);
}

// Point d'entrée principal du programme
int main()
{   // Affiche un message au démarrage ou au reset du programme
    alt_printf("Le chenillard est prêt à être lancé, cliquez sur SwitchKey1\n");
    chaser_speed = 0x01;
    // Activation des interruptions pour PIO_1_BASE (Switch Key 1) 
    IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PIO_1_BASE, 0x1);
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_1_BASE, 0x1);

   // Activation des interruptions pour les 4 premiers bits de PIO_2_BASE (Switch) pour ajuster la vitesse
    IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PIO_2_BASE, 0x0F); 
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_2_BASE, 0x0F);

    // Enregistre les gestionnaires d'interruption pour les boutons et switchs
    alt_irq_register(PIO_2_IRQ, NULL, irqhandler_switch);
    alt_irq_register(PIO_1_IRQ, NULL, irqhandler_switch_key1);
    // Exécute le programme en boucle
    while(1) {}
    return 0;
}




