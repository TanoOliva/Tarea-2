Indicaciones para compilar y ejecutar el programa:

    -Abrir un nuevo terminal
    -Escribir en el terminal: gcc Map.c -o main.c  (ENTER)
    -Luego escribir: ./a.exe (ENTER)
    -Se abrirá el menú de la aplicación y deberá indicar la opción 1 ("Importar archivo..."), para importar los productos del archivo.
    (Si no ingresa como primera opcion la numero 1, saldra un mensaje indicando que no importo archivo)
    -Luego podra indicar la opción que desee.

        
        
Opciones que funcionan correctamente y las que no lo hacen indicando posibles causas

    Correctamente:
        1.- Importar archivo
        2.- Exportar archivo
        3.- Agregar producto / aumentar stock
        4.- Buscar producto por tipo
        5.- Buscar producto por marca
        6.- Buscar Producto por nombre
        7.- Mostrar todos los productos
        8.- Agregar al carrito
        9.- Eliminar del carrito 
       10.- Concretar compra
       11.- Mostrar nombres de los carros de compras
       
    Casos especiales 

    -Si su opción es la 3 ("Agregar producto"), deberá indicar el nombre del producto, la marca, el tipo (ejemplo: aseo, mascota,
        Cocina,etc), el stock y el precio del producto, todo ello deberá escribirlo de la siguiente forma: 

        NombreProducto,Marca,Tipo,stock,precio(y un espacio)

        (No olvidar poner mayusculas al principio de cada informacion ingresada y no dejar espacio entre ellas).

    -Si su opción es la 4,5 o 6 debe escribir la palabra o frase ingresada de la misma forma que se encuentra en el archivo,
        con sus respectivas mayúsculas al principio de cada palabra SI LAS TIENE.

        Si la palabra ingresada lleva tilde, como por ejemplo, Cafe instantáneo 170gr, el programa lo lee de esta forma:
        Caf├® instant├íneo 170 gr, por ello, para buscar este producto debera escribir Caf├® instant├íneo 170 gr.

        Si no sabe como se deberia escribir el nombre del producto que quiera buscar, primero seleccione la opción 7 para mostrar todos
        los productos y buscar con control+f la palabra, asi se le mostrara el nombre del producto de la forma que lo lee el programa.
        (Esto ocurre solo con las palabras con tildes)

    -Con respecto a las opciones Agregar al carrito y eliminar del carrito (opciones 8 y 9) tener cuidado al escribir los nombres,
        poner espacios al final o poner mayúsculas en donde no debería afectan al algoritmo de busqueda y podría generar
        errores. Además el eliminar del carro no elimina el último elemento, sino que le pide al usuario que seleccione cual quiere eliminar
        esto se podría haber solucionado cambiando la estructura de un Map a una Lista o Pila y usar las funciones que estas contienen.
        Al momento de escribir esto realizar un cambio de tal magnitud sería imposible.
   


Aspectos positivos y a mejorar (por cada integrante)

    -Antonia Navarrete: 
        Colaboré en desarrollar varias funciones, ayudando a resolver problemas y demás. Como aspecto a mejorar, me gustaria tener los
        contenidos del ramo más claros de forma que pueda apoyar a mis compañeros de grupo en las dudas que les generaban.
    
    -Esteban Carrasco:
        Ayude a terminar algunas funciones además de ayudar a solucionar algunas complicaciones que tuvieron mis compañeros
        y nesesito mejorar mi organizacion, ya que no pude estar presente en todas las reuniones del grupo.
        
    -Luciano Oliva:
        Aspectos a mejorar: Puntualidad, siempre quedamos a una hora especifica de juntarnos a trabajar y desarrollar el codigo y resulta
        que nos conectamos no unos minutos despues sino que horas mas tardes. 

        Desarrollé junto a mis compañeros las funciones y estuve presente en la prueba del codigo escribindo una y otra y otra vez "Tuco de carne", "acondicionador 900 ml", etc. 

    -Pablo Paillalef:
        Esta semana estuve bastante desconectado de la universidad en general, lo que llevó a que mis compañeros criticaran mi ausencia,
        pero al final pude compensar avanzando en gran parte del trabajo y encontrando soluciones a problemas que tenían varias
        funciones.


Puntos de premio/castigo (a cada integrante)

-Antonia Navarrete: 0
-Esteban Carrasco:  0
-Luciano Oliva:     0
-Pablo Paillalef:   0