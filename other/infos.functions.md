Documentation des Fonctions Système en C

Sommaire

open

close

read

write

malloc

free

perror

strerror

access

dup

dup2

execve

exit

fork

pipe

unlink

wait

waitpid

open

Description : Ouvre un fichier et retourne un descripteur de fichier.

Prototype :

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int open(const char *pathname, int flags, mode_t mode);

Arguments :

pathname : chemin du fichier

flags : options d'ouverture (O_RDONLY, O_WRONLY, O_RDWR, etc.)

mode : permissions du fichier (utilisé si le fichier est créé)

Exemple :

int fd = open("test.txt", O_CREAT | O_WRONLY, 0644);
if (fd == -1) {
    perror("open");
    return 1;
}
close(fd);

close

Description : Ferme un descripteur de fichier.

Prototype :

#include <unistd.h>
int close(int fd);

Arguments :

fd : descripteur de fichier à fermer

Exemple :

int fd = open("test.txt", O_RDONLY);
if (fd != -1) {
    close(fd);
}

read

Description : Lit des données depuis un descripteur de fichier.

Prototype :

#include <unistd.h>
ssize_t read(int fd, void *buf, size_t count);

Arguments :

fd : descripteur de fichier

buf : buffer de stockage des données lues

count : nombre d'octets à lire

Exemple :

char buffer[100];
int fd = open("test.txt", O_RDONLY);
if (fd != -1) {
    read(fd, buffer, sizeof(buffer));
    close(fd);
}

write

Description : Écrit des données dans un descripteur de fichier.

Prototype :

#include <unistd.h>
ssize_t write(int fd, const void *buf, size_t count);

Arguments :

fd : descripteur de fichier

buf : buffer contenant les données à écrire

count : nombre d'octets à écrire

Exemple :

int fd = open("test.txt", O_WRONLY | O_CREAT, 0644);
if (fd != -1) {
    write(fd, "Hello, World!", 13);
    close(fd);
}

malloc

Description : Alloue dynamiquement de la mémoire.

Prototype :

#include <stdlib.h>
void *malloc(size_t size);

Arguments :

size : taille en octets de la mémoire à allouer

Exemple :

int *ptr = malloc(10 * sizeof(int));
if (!ptr) {
    perror("malloc");
    return 1;
}
free(ptr);

free

Description : Libère la mémoire allouée par malloc.

Prototype :

#include <stdlib.h>
void free(void *ptr);

Arguments :

ptr : pointeur vers la mémoire à libérer

Exemple :

int *ptr = malloc(10 * sizeof(int));
if (ptr) {
    free(ptr);
}

perror

Description : Affiche un message d'erreur basé sur errno.

Prototype :

#include <stdio.h>
#include <errno.h>
void perror(const char *s);

Arguments :

s : préfixe du message d'erreur

Exemple :

FILE *file = fopen("inexistant.txt", "r");
if (!file) {
    perror("Erreur ouverture fichier");
}

strerror

Description : Retourne un message d'erreur sous forme de chaîne de caractères.

Prototype :

#include <string.h>
#include <errno.h>
char *strerror(int errnum);

Arguments :

errnum : numéro d'erreur errno

Exemple :

printf("Erreur: %s\n", strerror(ENOENT));

access

Description : Vérifie les permissions d'accès à un fichier.

Prototype :

#include <unistd.h>
int access(const char *pathname, int mode);

Arguments :

pathname : chemin du fichier

mode : mode d'accès (F_OK, R_OK, W_OK, X_OK)

Exemple :

if (access("test.txt", F_OK) == 0) {
    printf("Le fichier existe.\n");
}

fork

Description : Crée un processus enfant.

Prototype :

#include <unistd.h>
pid_t fork(void);

Exemple :

pid_t pid = fork();
if (pid == 0) {
    printf("Processus enfant\n");
} else {
    printf("Processus parent\n");
}

wait

Description : Attend la fin d'un processus enfant.

Prototype :

#include <sys/types.h>
#include <sys/wait.h>
pid_t wait(int *wstatus);

Exemple :

pid_t pid = fork();
if (pid > 0) {
    wait(NULL);
    printf("Processus enfant terminé\n");
}

Toutes les fonctions ont été détaillées avec leurs prototypes et exemples. Si tu veux encore plus d'explications ou d'autres exemples, dis-moi !

