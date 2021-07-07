# QuonMusic
Proyecto final estructura de datos

-IMPORTANTE-

El trabajo fue realizado en un principio en code block y posteriormente por temas de comodidad comenzamos a trabajar en la aplicación Replit, es por esto que al transferir el código a Code Blocks se generan algunos errores que no estaban en Replit. Para que puedan revisar el código de mejor manera es preferible que sea revisado en Replit.

https://replit.com/join/arqlqylgts-jefteponce este es el link que se utilizó.


A continuación se darán algunos consejos antes de utilizar la aplicación para evitar fallos o errores que lleven a la caída de esta.

-En el menú de inicio de sesión al ingresar un número como usuario o contraseña el programa se cae si no existe ningún usuario con estos datos, pero independiente a esto el usuario al registrarse puede usar números.

-Para las funciones de ver los datos que pertenecen al usuario (género,canciones y artistas) se tendrá que ingresar exactamente como viene en la base de datos, esto quiere decir que si la canción se llama "Hello" el usuario no podrá ingresar de la manera "hello", se tendrán que respetar mayúsculas y espacios correspondientemente.

-Para probar la función TOP(cómo aumenta o se reduce la calificación de la canción) tendrá que ingresar a una nueva cuenta o una cuenta actual y comenzar a agregar/quitar canciones favoritas.

-En la función recomendacion de artista según tus gusto, si tienes artistas con los mismos géneros te recomendará dos veces los mismos artistas.

-Para las contraseñas se intentó utilizar un código para hacer que la palabra que se quisiera escribir apareciera con asteriscos, sin embargo no funcionó, pero el codigo quedó comentado en el main, especificamente en estas partes en la linea 9 se añade la libreria, en las lineas 77 a 80 se declaran las variables necesarias para hacer funcionar la función, en las lineas 136 a 151 se hace el código necesario para que la contraseña aparezca con "*" en el registro, en las lineas 217 a 232 se hace el código necesario para que la contraseña aparezca con "*" en el inicio de sesión.

-En las funciones que piden números como parametros (principalmente los menús) si no se le da un número el programa se cae, ya que no hay validaciones.