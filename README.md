# 42School minishell 

El proyecto minishell de 42School tiene como objetivo sumergirte en el mundo de las shells desafiándote a crear tu propia mini-shell. 
![](minishell42.png)
## minishell debe:
- Mostrar una entrada mientras espera un comando nuevo.
- Tener un historial funcional.
- Buscar y ejecutar el ejecutable correcto (basado en la variable `PATH` o mediante el uso de rutas relativas o absolutas).
- Evita utilizar más de una variable global para indicar la recepción de una señal. Piensa en lo que implica: Esta aproximación evita que tu gestor de señales acceda a tus estructuras de datos principales.
- No interpretar comillas sin cerrar o caracteres especiales no especificados en el enunciado como `\` (barra invertida) o `;` (punto y coma).
- Gestionar que la `’` evite que el shell interprete los metacaracteres en la secuencia
entrecomillada.
- Gestionar que la `"` evite que el shell interprete los metacaracteres en la secuencia entrecomillada exceptuando `$` (signo de dólar).
- Implementar redirecciones:
  - `<` debe redirigir input.
  - `>` debe redirigir output.
  - `<<` debe recibir un delimitador, después leer del input de la fuente actual hasta que una línea que contenga solo el delimitador aparezca. Sin embargo, no necesita actualizar el historial.
  - `>>` debe redirigir el output en modo append.
- Implementar pipes (carácter `|`). El output de cada comando en la pipeline se conecta a través de un pipe al input del siguiente comando.
- Gestionar las variables de entorno (`$` seguidos de caracteres) que deberán expandirse a sus valores.
- Gestionar `$?`, que deberá expandirse al estado de salida del comando más reciente ejecutado en la pipeline.
- Gestionar `ctrl-C` `ctrl-D` `ctrl-\`, que deberán funcionar como en bash.
- Cuando sea interactivo:
  - `ctrl-C` imprime una nueva entrada en una línea nueva.
  - `ctrl-D` termina el shell.
  - `ctrl-\` no hace nada.
- Deberá implementar los built-ins:
  - `echo` con la opción `-n`.
  - `cd` solo con una ruta relativa o absoluta.
  - `pwd` sin opciones.
  - `export` sin opciones.
  - `unset` sin opciones.
  - `env` sin opciones o argumentos.
  - `exit` sin opciones.
 
## Proceso
Como todo proyecto de 42School, la primera etapa es la de investigación.  
Recomendamos leer el [manual de bash](https://www.gnu.org/software/bash/manual/html_node/index.html) y dividir el proyecto en fases tal y como se menciona en la sección [shell operation](https://www.gnu.org/software/bash/manual/html_node/Shell-Operation.html).

> 1.  Reads its input from a file (see Shell Scripts), from a string supplied as an argument to the -c invocation option (see Invoking Bash), or from the user’s terminal.
> 2.  Breaks the input into words and operators, obeying the quoting rules described in Quoting. These tokens are separated by metacharacters. Alias expansion is performed by this step (see Aliases).
> 3.  Parses the tokens into simple and compound commands (see Shell Commands).
> 4.  Performs the various shell expansions (see Shell Expansions), breaking the expanded tokens into lists of filenames (see Filename Expansion) and commands and arguments.
> 5.  Performs any necessary redirections (see Redirections) and removes the redirection operators and their operands from the argument list.
> 6.  Executes the command (see Executing Commands).
> 7.  Optionally waits for the command to complete and collects its exit status (see Exit Status).

### Lectura del input
Utilizamos la libreria readline de GNU que ya está permitido su uso. [ver manual.](https://tiswww.case.edu/php/chet/readline/rltop.html)  
Esta libreria, a su vez, nos proporciona el historial que solicita la consigna.   

### Análisis lexicológico
Esta etapa consiste en identificar tokens. Leemos caracter a caracter la línea que obtubimos en el paso anterior y guardamos en una estructura clasificando en `word` o `token` siguiendo las reglas de encomillado de bash.

### Análisis sintáctico
La lista de nodos generada por el paso anterior se libera y se generan nuevos nodos para la instancia de ejecución. Aquí también, revisamos si hay redirecciones y generamos los file descriptors para cada uno de los procesos que vayamos a ejecutar más adelante. Cada nodo que generemos es el conjunto de `word` y `token` hasta llegar a un `PIPE` en caso de encontrar uno.

### Expansiones
Antes de enviar la lista de nodos al ejecutor hay que realizar las expansiones necesarias de acuerdo a las reglas de encomillado de bash.

### Redirecciones y liberación de memoria
Una vez hecho el `fork()` libramos todas las estructuras en memoria del proceso hijo y duplicamos los file descriptors en caso de haber redirecciones.

### Ejecución
Por último, ejecutamos uno a uno todos los nodos que generamos, liberamos memoria, cerramos file descriptors y lanzamos el prompt esperando la nueva senencia a ejecutar.

## Uso
### Clona el repositorio
```bash
git clone ... minishell
```
### Compila el proyecto con make
```bash
make
```
Como se menciona anteriormente, este proyecto requiere de la libreria `readline`. En caso de no tenerla instalada ejecuta:
- En sistemas basados en Debian/Ubuntu:
```bash
sudo apt-get update
sudo apt-get install libreadline-dev
```
- En sistemas basados en Red Hat/Fedora:
```bash
sudo yum install readline-devel
```
- En macOS (usando Homebrew):
```bash
brew install readline
```

### Ejecuta la minishel
```bash
./minishell
```
## Documentación
- [BASH manual](https://www.gnu.org/software/bash/manual/html_node/index.html)
- [GNU readline](https://tiswww.case.edu/php/chet/readline/rltop.html)

## Autores

- [@Fefeco](https://www.github.com/Fefeco)
- [@Daviichii89](https://github.com/Daviichii89)














