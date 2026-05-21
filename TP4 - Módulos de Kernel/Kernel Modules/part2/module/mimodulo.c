#include <linux/module.h>							/* Requerido por todos los módulos */
#include <linux/kernel.h>							/* Definición de KERN_INFO */
#include <linux/utsname.h>
MODULE_LICENSE("GPL"); 								/*  Licencia del modulo */
MODULE_DESCRIPTION("Segundo modulo ejemplo");
MODULE_AUTHOR("Grupo 2V 1B");


int init_module(void)
{
    printk(KERN_INFO "Módulo cargado exitosamente.\n");
    printk(KERN_INFO "Desarrollado por el equipo: 2V 1B.\n");
    printk(KERN_INFO "Nombre del equipo anfitrión: %s\n", init_uts_ns.name.nodename);

    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "Módulo de '2V 1B' descargado del Kernel. ¡Hasta luego!\n");
}


/* Declaración de funciones init y exit */
// module_init(modulo_lin_init);
// module_exit(modulo_lin_clean);