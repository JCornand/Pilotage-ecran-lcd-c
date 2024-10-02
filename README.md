# Pilotage-ecran-lcd-c

Il s’agit d’écrire un programme qui permet de saisir une valeur au clavier sur le PC pour afficher sa
représentation décimale, hexadécimale et binaire sur un écran lcd connecté au port série du PC. L’heure
locale du PC sera en même temps affichée périodiquement toutes les secondes sur cet écran lcd.
L’écran est interfacé via une ligne série (/dev/ttyS0), on suppose connues les techniques d’accès à cetteligne.

## Objectifs

• Programmation en langage C sous Linux.
• Configurer et piloter le port série d’un PC.
• Mise en œuvre d’une communication sur le port série, création de processus, de tubes decommunication entre processus, gestion d’un segment de mémoire partagée, gestion d’unsémaphore et gestion de signal.
• Exploitation d’une documentation technique.
