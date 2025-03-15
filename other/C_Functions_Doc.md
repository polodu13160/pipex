# 📖 Documentation des Fonctions Système en C

## 📌 Sommaire

- [📂 open](#open)
- [❌ close](#close)
- [📖 read](#read)
- [✍️ write](#write)
- [📦 malloc](#malloc)
- [🗑️ free](#free)
- [🚨 perror](#perror)
- [⚠️ strerror](#strerror)
- [🔑 access](#access)
- [🔁 dup](#dup)
- [🔁 dup2](#dup2)
- [🚀 execve](#execve)
- [🚪 exit](#exit)
- [👶 fork](#fork)
- [🔗 pipe](#pipe)
- [🗑️ unlink](#unlink)
- [⏳ wait](#wait)
- [⏳ waitpid](#waitpid)

---

## 📂 open

**🔎 Description** : Ouvre un fichier et retourne un descripteur de fichier.

**📜 Prototype** :

```c
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int open(const char *pathname, int flags, mode_t mode);
```

**🛠️ Arguments** :

- `📄 pathname` : chemin du fichier
- `⚙️ flags` : options d'ouverture (`O_RDONLY`, `O_WRONLY`, `O_RDWR`, etc.)
- `🔑 mode` : permissions du fichier (utilisé si le fichier est créé)

**📌 Exemple** :

```c
int fd = open("test.txt", O_CREAT | O_WRONLY, 0644);
if (fd == -1) {
    perror("open");
    return 1;
}
close(fd);
```

---

## ❌ close

**🔎 Description** : Ferme un descripteur de fichier.

**📜 Prototype** :

```c
#include <unistd.h>
int close(int fd);
```

**🛠️ Arguments** :

- `🔢 fd` : descripteur de fichier à fermer

**📌 Exemple** :

```c
int fd = open("test.txt", O_RDONLY);
if (fd != -1) {
    close(fd);
}
```

---

## 📖 read

**🔎 Description** : Lit des données depuis un descripteur de fichier.

**📜 Prototype** :

```c
#include <unistd.h>
ssize_t read(int fd, void *buf, size_t count);
```

**🛠️ Arguments** :

- `🔢 fd` : descripteur de fichier
- `📦 buf` : buffer de stockage des données lues
- `📏 count` : nombre d'octets à lire

**📌 Exemple** :

```c
char buffer[100];
int fd = open("test.txt", O_RDONLY);
if (fd != -1) {
    read(fd, buffer, sizeof(buffer));
    close(fd);
}
```

---

## ✍️ write

**🔎 Description** : Écrit des données dans un descripteur de fichier.

**📜 Prototype** :

```c
#include <unistd.h>
ssize_t write(int fd, const void *buf, size_t count);
```

**🛠️ Arguments** :

- `🔢 fd` : descripteur de fichier
- `📦 buf` : buffer contenant les données à écrire
- `📏 count` : nombre d'octets à écrire

**📌 Exemple** :

```c
int fd = open("test.txt", O_WRONLY | O_CREAT, 0644);
if (fd != -1) {
    write(fd, "Hello, World!", 13);
    close(fd);
}
```

---

## 📦 malloc

**🔎 Description** : Alloue dynamiquement de la mémoire.

**📜 Prototype** :

```c
#include <stdlib.h>
void *malloc(size_t size);
```

**🛠️ Arguments** :

- `📏 size` : taille en octets de la mémoire à allouer

**📌 Exemple** :

```c
int *ptr = malloc(10 * sizeof(int));
if (!ptr) {
    perror("malloc");
    return 1;
}
free(ptr);
```

---

## 🗑️ free

**🔎 Description** : Libère la mémoire allouée par `malloc`.

**📜 Prototype** :

```c
#include <stdlib.h>
void free(void *ptr);
```

**🛠️ Arguments** :

- `📌 ptr` : pointeur vers la mémoire à libérer

**📌 Exemple** :

```c
int *ptr = malloc(10 * sizeof(int));
if (ptr) {
    free(ptr);
}
```

---

## 🚨 perror

**🔎 Description** : Affiche un message d'erreur basé sur `errno`.

**📜 Prototype** :

```c
#include <stdio.h>
#include <errno.h>
void perror(const char *s);
```

**🛠️ Arguments** :

- `📝 s` : préfixe du message d'erreur

**📌 Exemple** :

```c
FILE *file = fopen("inexistant.txt", "r");
if (!file) {
    perror("Erreur ouverture fichier");
}
```

---

## 👶 fork

**🔎 Description** : Crée un processus enfant.

**📜 Prototype** :

```c
#include <unistd.h>
pid_t fork(void);
```

**📌 Exemple** :

```c
pid_t pid = fork();
if (pid == 0) {
    printf("Processus enfant
");
} else {
    printf("Processus parent
");
}
```

---

## ⏳ wait

**🔎 Description** : Attend la fin d'un processus enfant.

**📜 Prototype** :

```c
#include <sys/types.h>
#include <sys/wait.h>
pid_t wait(int *wstatus);
```

**📌 Exemple** :

```c
pid_t pid = fork();
if (pid > 0) {
    wait(NULL);
    printf("Processus enfant terminé
");
}
```


## 🔑 access

**🔎 Description** : Vérifie les permissions d'accès d'un fichier.

**📝 Prototype** :

```c
#include <unistd.h>
int access(const char *pathname, int mode);
```

**🛠️ Arguments** :

- `📄 pathname` : chemin du fichier
- `⚙️ mode` : type de test (
  - `F_OK` : vérifie si le fichier existe
  - `R_OK` : test lecture
  - `W_OK` : test écriture
  - `X_OK` : test exécution)

**📌 Exemple** :

```c
if (access("test.txt", F_OK) == 0) {
    printf("Le fichier existe.\n");
} else {
    perror("access");
}
```

---

## 🔄 dup

**🔎 Description** : Duplique un descripteur de fichier.

**📝 Prototype** :

```c
#include <unistd.h>
int dup(int oldfd);
```

**🛠️ Arguments** :

- `💿 oldfd` : descripteur de fichier à dupliquer

**📌 Exemple** :

```c
int fd = open("test.txt", O_RDONLY);
int new_fd = dup(fd);
```

---

## 🔄 dup2

**🔎 Description** : Duplique un descripteur de fichier vers un numéro spécifique.

**📝 Prototype** :

```c
#include <unistd.h>
int dup2(int oldfd, int newfd);
```

**🛠️ Arguments** :

- `💿 oldfd` : descripteur de fichier existant
- `💿 newfd` : descripteur de fichier cible

**📌 Exemple** :

```c
int fd = open("test.txt", O_RDONLY);
dup2(fd, 0); // Redirige l'entrée standard vers fd
```

---

## 🛡️ strerror

**🔎 Description** : Retourne une chaîne d'erreur correspondant à errno.

**📝 Prototype** :

```c
#include <string.h>
char *strerror(int errnum);
```

**📌 Exemple** :

```c
printf("Erreur: %s\n", strerror(errno));
```

---

## 👶 fork

**🔎 Description** : Crée un processus enfant.

**📝 Prototype** :

```c
#include <unistd.h>
pid_t fork(void);
```

**📌 Exemple** :

```c
pid_t pid = fork();
if (pid == 0) {
    printf("Processus enfant\n");
} else {
    printf("Processus parent\n");
}
```

---

## 🔗 pipe

**🔎 Description** : Crée un canal de communication unidirectionnel.

**📝 Prototype** :

```c
#include <unistd.h>
int pipe(int pipefd[2]);
```

**📌 Exemple** :

```c
int fd[2];
pipe(fd);
write(fd[1], "Hello", 5);
```

---

## 🛡️ unlink

**🔎 Description** : Supprime un fichier.

**📝 Prototype** :

```c
#include <unistd.h>
int unlink(const char *pathname);
```

**📌 Exemple** :

```c
unlink("test.txt");
```

---

## ⏳ waitpid

**🔎 Description** : Attend la fin d'un processus enfant spécifique.

**📝 Prototype** :

```c
#include <sys/types.h>
#include <sys/wait.h>
pid_t waitpid(pid_t pid, int *status, int options);
```

**📌 Exemple** :

```c
pid_t pid = fork();
if (pid > 0) {
    waitpid(pid, NULL, 0);
}
```

## 🚀 execve

**🔎 Description** : Exécute un programme en remplaçant le processus courant.

**📝 Prototype** :

```c
#include <unistd.h>
int execve(const char *pathname, char *const argv[], char *const envp[]);
```

**🛠️ Arguments** :

- `📄 pathname` : chemin du programme à exécuter
- `📚 argv` : tableau des arguments (le premier étant le nom du programme)
- `🌍 envp` : tableau des variables d'environnement

**📌 Exemple** :

```c
char *args[] = {"/bin/ls", "-l", NULL};
char *env[] = {NULL};
execve("/bin/ls", args, env);
perror("execve"); // S'exécute seulement si execve échoue
```

---

