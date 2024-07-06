# 42School minishell 

El proyecto de 42School minishell busca interiorizar en el mundo de las shells intentando recrear tu propia mini-shell. Para ello deberás interiorizarte en file descriptors, procesos, señales y el comportamiento general de bahs. 

## Objetivo
[es](es.subject.pdf) [en]
### la minishell debe: 
- Mostrar una entrada mientras espera un comando nuevo.
- Tener un historial funcional.
- Buscar y ejecutar el ejecutable correcto (basado en la variable PATH o mediante el
uso de rutas relativas o absolutas).
- Evita utilizar más de una variable global para indicar la recepción de una señal.
Piensa en lo que implica: Esta aproximación evita que tu gestor de señales acceda
a tus estructuras de datos principales.
- No interpretar comillas sin cerrar o caracteres especiales no especificados en el
enunciado como \ (barra invertida) o ; (punto y coma).
- Gestionar que la ’ evite que el shell interprete los metacaracteres en la secuencia
entrecomillada.
- Gestionar que la " evite que el shell interprete los metacaracteres en la secuencia
entrecomillada exceptuando $ (signo de dólar).
- Implementar redirecciones:
  - `<` debe redirigir input.
  - `>` debe redirigir output.
  - `<<` debe recibir un delimitador, después leer del input de la fuente actual
hasta que una línea que contenga solo el delimitador aparezca. Sin embargo,
no necesita actualizar el historial.
  - `>>` debe redirigir el output en modo append.
- Implementar pipes (carácter |). El output de cada comando en la pipeline se
conecta a través de un pipe al input del siguiente comando.
- Gestionar las variables de entorno ($ seguidos de caracteres) que deberán expandirse a sus valores.
- Gestionar $?, que deberá expandirse al estado de salida del comando más reciente
ejecutado en la pipeline.
- Gestionar `ctrl-C` `ctrl-D` `ctrl-\`, que deberán funcionar como en bash.
- Cuando sea interactivo:
  - `ctrl-C` imprime una nueva entrada en una línea nueva.
  - `ctrl-D` termina el shell.
  - `ctrl-\` no hace nada.
- Deberá implementar los built-ins:
  - `echo` con la opción -n.
  - `cd` solo con una ruta relativa o absoluta.
  - `pwd` sin opciones.
  - `export` sin opciones.
  - `unset` sin opciones.
  - `env` sin opciones o argumentos.
  - `exit` sin opciones.
 
## Proceso
Como todo proyecto de 42School, la primera etapa es la de investigación.
Para esta estapa recomendamos fuertemente leer el [manual de bash](https://www.gnu.org/software/bash/manual/html_node/index.html) y dividir el proyecto en fases tal y como menciona en [shell operation](https://www.gnu.org/software/bash/manual/html_node/Shell-Operation.html).

> 1.  Reads its input from a file (see Shell Scripts), from a string supplied as an argument to the -c invocation option (see Invoking Bash), or from the user’s terminal.
> 2.  Breaks the input into words and operators, obeying the quoting rules described in Quoting. These tokens are separated by metacharacters. Alias expansion is performed by this step (see Aliases).
> 3.  Parses the tokens into simple and compound commands (see Shell Commands).
> 4.  Performs the various shell expansions (see Shell Expansions), breaking the expanded tokens into lists of filenames (see Filename Expansion) and commands and arguments.
> 5.  Performs any necessary redirections (see Redirections) and removes the redirection operators and their operands from the argument list.
> 6.  Executes the command (see Executing Commands).
> 7.  Optionally waits for the command to complete and collects its exit status (see Exit Status).
   
