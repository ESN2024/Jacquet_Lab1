#include <stdio.h>
#include "system.h"
#include "alt_types.h"
#include "io.h"
#include "altera_avalon_pio_regs.h"
#include <stdlib.h>
#include <unistd.h> // Pour la fonction usleep
#include "sys/alt_stdio.h"

#define DELAI 200000

static void irqhandler(void* context) {
    // Vérifiez l'état du bouton poussoir (5ème bit)
    if ((IORD_ALTERA_AVALON_PIO_EDGE_CAP(PIO_1_BASE) & 0x010) == 0x010) {
        start = 1; // Activer le chenillard
    } else {
        start = 0; // Désactiver le chenillard
    }

    // Effacer le registre de capture d'événement d'interruption
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_1_BASE, 0);
}


int main()
{
    alt_printf("main() started\n");

    // Configurer le switch key pour générer des interruptions
    IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PIO_1_BASE, 0x10);
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_1_BASE, 0x10);

    // Enregistrer l'interruption
    alt_irq_register(PIO_1_IRQ, NULL, irqhandler);

    // Boucle principale
    while(1) {
        // Logique principale ici (si nécessaire)
        IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE, 0x0);
    }

    return 0;
}