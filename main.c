#include <wchar.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Map.h"

typedef struct
{
    char *nombre;
    int precio;
    char *tipo;
    int stock;
    char *marca;
}Producto;

typedef struct
{
    char *nombre;
    Map * Carro;
    int tamanyo;
}ShoppingCart;


//funcion que separa el archivo csv en campos distintos para luego guardarlos en las distntas variablrs
const char *get_csv_field (char * tmp, int k)
{
    int open_mark = 0;
    char* ret = (char*) malloc (100*sizeof(char));
    int ini_i = 0, i = 0;
    int j = 0;
    while(tmp[i+1] != '\0'){

        if(tmp[i] == '\"')
        {
            open_mark = 1-open_mark;
            if(open_mark) ini_i = i+1;
            i++;
            continue;
        }

        if(open_mark || tmp[i]!= ',')
        {
            if(k==j) ret[i-ini_i] = tmp[i];
            i++;
            continue;
        }

        if(tmp[i]== ',')
        {
            if(k==j)
            {
               ret[i-ini_i] = 0;
               return ret;
            }
            j++; ini_i = i+1;
        }

        i++;
    }

    if(k==j)
    {
       ret[i-ini_i] = 0;
       return ret;
    }

    return NULL;
}


Producto* createBook(char *nombre,int precio,char *tipo,int stock,char *marca){
    Producto* p = (Producto*) malloc (sizeof(Producto));
    strcpy(p->nombre,nombre);
    strcpy(p->tipo,tipo);
    strcpy(p->marca,marca);
    p->precio=precio;
    p->stock=stock;
    return p;
}

/*
  función para comparar claves de tipo string
  retorna 1 si son iguales
*/
int is_equal_string(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2)==0) return 1;
    return 0;
}

/*
  función para comparar claves de tipo string
  retorna 1 si son key1<key2
*/
int lower_than_string(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2) < 0) return 1;
    return 0;
}

/*
  función para comparar claves de tipo int
  retorna 1 si son iguales
*/
int is_equal_int(void * key1, void * key2) {
    if(*(int*)key1 == *(int*)key2) return 1;
    return 0;
}

/*
  función para comparar claves de tipo int
  retorna 1 si son key1<key2
*/
int lower_than_int(void * key1, void * key2) {
    if(*(int*)key1 < *(int*)key2) return 1;
    return 0;
}

//Funcion que importa el archivo csv
/*
    La funcion abre el archivo csv, crea un while para poder recorrer cada linea del csv
    luego con un for desde 0 hasta 5 recorre los distintos campos dentro de cada linea recorrida por el while
    y cada uno de esos campos es almacenado en la variable de la estructura para ser 
    almacenadas en la lista de mapas
*/
void importar(Map * MapaGeneral,Map *Producto_por_tipo ,Map *Producto_por_marca )
{
    FILE *fp = fopen ("Archivo_100productos.csv","r");
    char linea[1024];
    int campo; 
    size_t largoString;

    while (fgets (linea, 1024, fp) != NULL){
        /*  
        char *nombre = (char *) malloc(50*sizeof(char));
        int precio;
        char *tipo = (char *) malloc(50*sizeof(char));
        int stock;
        char *marca = (char *) malloc(50*sizeof(char));
        */
        Producto* product= (Producto *) malloc (sizeof(Producto));
        for (campo = 0; campo < 5; campo += 1){
            char* aux = (char *) get_csv_field(linea , campo);
            largoString = strlen(aux)+1;
            if (campo == 0)
            {
                product->nombre = (char *) calloc(largoString , sizeof(char));
                strcpy(product->nombre , aux);
            }
            if (campo == 1)
            {
                product->marca = (char *) calloc(largoString , sizeof(char));
                strcpy(product->marca , aux);
            }
            if (campo == 2)
            {
                product->tipo =  (char *) calloc(largoString , sizeof(char));
                strcpy(product->tipo,aux);
            }
            if (campo == 3)
            {
                product->stock = atoi(aux);
            }
            if (campo == 4)
            {
                product->precio = atoi(aux);

            }

        }//fin del ciclo for
        
        insertMap(MapaGeneral,product->nombre,product);
        
        insertMap(Producto_por_tipo,product->tipo,product); 
        insertMap(Producto_por_marca,product->marca,product);
        
    }
    return; 
}

/*
    La funcion mostrar productos como bien dice muestra todos los productos recorriendo la lista general,
    y mientras la variable auxiliar tipo producto sea distinta de null se imprimirán todos los productos
    de la forma "Nombre: %s\nMarca:  %s\nTipo:   %s\nStock:  %d\nPrecio: $%d\n\n"
*/
void MostrarProductos(Map * MapaGeneral)
{
    Producto * aux = (Producto *) malloc(sizeof(Producto));
    aux = firstMap(MapaGeneral);
    while (aux != NULL)
    {
        printf("Nombre: %s\nMarca:  %s\nTipo:   %s\nStock:  %d\nPrecio: $%d\n\n",aux->nombre,aux->marca,aux->tipo,aux->stock,aux->precio);
        aux = nextMap(MapaGeneral);
    }
}

/*
    La funcion buscar por nombre, busca por nombre recorriendo la lista general encontrando coincidencias
    con un strncmp == 0, y si no se encuentra ninguna coincidencia se imprime 
    "El producto ingresado no encuentra ninguna coincidencia"
*/
void BuscarPorNombre(Map * MapaGeneral)
{    
    Producto *aux = (Producto *) malloc(sizeof(Producto));
    aux = firstMap(MapaGeneral);
    printf("Ingrese el nombre del producto que quiere buscar: ");
    fflush(stdin);
    char *nombreAux = (char*) malloc (sizeof(char));
    gets(nombreAux);
    int largoNombre = strlen(nombreAux);
    
    while (aux != NULL)
    {
        if (strncmp(nombreAux , aux->nombre , largoNombre) == 0)
        {
            printf("El producto de nombre %s si se encuentra en el archivo\n", nombreAux);
            printf("Nombre: %s\nMarca:  %s\nTipo:   %s\nStock:  %d\nPrecio: $%d\n\n",aux->nombre,aux->marca,aux->tipo,aux->stock,aux->precio);
            return;
        }
        aux = nextMap(MapaGeneral);
    }
    printf("El producto ingresado no se encuentra en el archivo\n");
    return;
}

/*La funcion SearchByName
    funciona de la misma manera que la funcion BuscarPorNombre, con la diferencia que retorna
    un puntero a la estructura Producto, para poder modificar el mapa que ingresamos
*/
Producto * SearcHByName(Map * MapaGeneral, char * nombre)
{    
    Producto *aux = (Producto *) malloc(sizeof(Producto));
    aux = firstMap(MapaGeneral);
    while (aux != NULL)
    {
        if (strcmp(nombre , aux->nombre) == 0)
        {
            return aux;
        }
        aux = nextMap(MapaGeneral);
    }
    return NULL;
}

/*
    SearchCartByName: funciona de la misma manera que SearchByName con al diferencia que en vez de retornar
    un tipo Producto, retorna un puntero a la estructura ShoppingCart
*/
ShoppingCart * SearchCartByName(Map * MapaCarros, char * nombre)
{    
    ShoppingCart *aux = (ShoppingCart *) malloc(sizeof(ShoppingCart));
    aux = firstMap(MapaCarros);

    while (aux != NULL)
    {
        if (strcmp(nombre , aux->nombre) == 0)
        {
            return aux;
        }
        aux = nextMap(MapaCarros);
    }
    return NULL;
}

/*La funcion buscar por tipo:
    Primero crea una variable auxiliar de tipo producto para poder recorrer la lista de productos por tipo
    lusgo se ingresa el tipo que deseamos buscar y se recorre la lista mientras nuestra variable 
    auxiliar sea distinta de null.

    Mientras se recorre se buscan las coincidencias y se muestran por pantalla.
*/
void BuscarPorTipo(Map * pptipo){
    Producto *aux = (Producto *)malloc(sizeof(Producto));
    aux = firstMap(pptipo);
    char tipo[50];
    printf("Ingrese el tipo que desea buscar: ");
    fflush(stdin);
    scanf("%s",tipo);

    printf("\nLos productos de tipo \"%s\" son: \n\n",tipo);
    while (aux!=NULL){
        if (strcmp(aux->tipo,tipo) == 0){
            printf("Nombre: %s\nMarca:  %s\nTipo:   %s\nStock:  %d\nPrecio: $%d\n\n",aux->nombre,aux->marca,aux->tipo,aux->stock,aux->precio);
        }
        aux = nextMap(pptipo);
    }
    fflush(stdin);
    return;
}

/* 
    La fucnion BuscarPorMarca
    Funciona de la misma manera que buscar por tipo con la diferencia que imprime "marca" en vez de tipo como en la fucnion anterior 
*/
void BuscarPorMarca(Map * ppmarca){
    Producto *aux = (Producto *)malloc(sizeof(Producto));
    aux = firstMap(ppmarca);
    printf("Ingrese la marca que desea buscar: ");
    fflush(stdin);
    char *marca = (char*)malloc(sizeof(char));
    gets(marca);
    int cont = 0;
    printf("\nLos productos de marca \"%s\" son: \n",marca);
    while (aux != NULL)
    {
        if (strcmp(aux->marca, marca) == 0)
        {
            printf("Nombre: %s\nMarca:  %s\nTipo:   %s\nStock:  %d\nPrecio: $%d\n\n",aux->nombre,aux->marca,aux->tipo,aux->stock,aux->precio);
            cont+= 1;
        }
        aux = nextMap(ppmarca);
    }

    if (cont == 0)
    {
        printf("La marca que ingreso no se encuentra en ningun producto\n");
    }
    return;
}

/*
    La funcion aumentar stock, se creó para ser utilizada dentro de la funcion agregar progucto,
    ya que si el producto ingresado ya se encuentra aumenta el stock y retorna 1 para no insertar el producto en la lista
*/
int AumentarStock(Producto * p , Map * mapaGeneral)
{
    Producto * aux = (Producto *) malloc (sizeof(Producto));
    aux = SearcHByName(mapaGeneral,p->nombre);
    if (aux == NULL)
    {
        return 0;
    }
    else
    {
        //se aumenta el stock
        aux->stock+=p->stock;
        return 1;
    }
}

/*
    La funcion agregar Producto crea un for para recorrer los distintos campos de la funcion get_csv_field y almacenar los campos en las 
    distintas variables de la estructura Producto *, luego se comprueba si existe dentro del mapa general y si existe aumenta el stock

    OJO que al ingresar el producto hay que hacerlo de la siguiente manera: 
    "Nombre,Marca,tipo,Stock,Precio " con un espacio al final
*/
void AgregarProducto(Map * MapaGeneral)
{
    printf("Si ya se encuentra el producto en el inventario, se aumentara su stock\n");
    printf("Ingrese los datos del producto: ");
    char datosProducto[1024];
    Producto * product = (Producto *)malloc (sizeof(Producto));
    int largoString;
    fflush(stdin);
    gets(datosProducto);
    
    for (int campo = 0 ; campo < 5; campo++)
    {
        char*aux = (char*) get_csv_field (datosProducto, campo);
        largoString = strlen(aux) + 1;
        if(campo == 0)
        {
            product->nombre = (char*) calloc (largoString, sizeof(char));
            strcpy(product->nombre, aux);
        }
        if (campo == 1)
        {
            product->marca = (char *) calloc(largoString , sizeof(char));
            strcpy(product->marca , aux);
        }
        if (campo == 2)
        {
            product->tipo = (char *) calloc(largoString , sizeof(char));
            strcpy(product->tipo , aux);
        }   
        if (campo == 3)
        {
            //product->stock = (int *) calloc(largoString , sizeof(int));
            product->stock = atoi(aux);
        }
        if (campo == 4)
        {
            //product->precio= (int *) calloc(largoString , sizeof(int));
            product->precio= atoi(aux);
        }  
    }

    if (AumentarStock(product, MapaGeneral) == 1)
    {
        printf("\nEl producto que ingreso ya se encuentra guardado\n");
        printf("Se aumento el stock con exito\n");
        
        return;
    }

    printf("El nombre del producto es:...%s\n", product->nombre);
    printf("La marca es:.................%s\n", product->marca);
    printf("El producto es de tipo:......%s\n", product->tipo);
    printf("El stock del producto es:....%d\n", product->stock);
    printf("Precio del producto:.........%d\n", product->precio);

    insertMap(MapaGeneral , product->nombre , product);
}

/*
    La funcion exportar productos: crea un archivo csv con el fopen de la forma w+ que significa que crea un archivo en modo escritura dentro de la variable exportar 
    se recorre el mapa general y se imprimen con fprintf para poder escribir dentro del archivo creado 
*/
void exportarProductosCSV(Map* MapaGeneral)
{
    FILE * exportar;
    exportar = fopen("productosexportados.csv","w+");
    Producto *aux = (Producto *) malloc(sizeof(Producto));
    aux = firstMap(MapaGeneral);
    
    while (aux != NULL)
    {   
        printf("%s\n", aux->nombre);
        fprintf(exportar,"%s,%s," , aux->nombre , aux->marca);
        
        fprintf(exportar,"%s,%d,%d\n", aux->tipo , aux->stock, aux->precio);

        aux = nextMap(MapaGeneral);
    }
    fclose(exportar);
    return;
}

/*
    La funcion ReducirStock esta implementada en la funcion agregar al carro, se encarga
    de buscar el producto y disminuir su stock dependiendo de lo que se quiera agregar
    al carro.
*/
Producto * Reducir_Stock (Producto * item , Map * mapaGeneral)
{
    Producto * aux;
    int opcion = 0;

    aux = SearcHByName(mapaGeneral , item->nombre);
    if (aux == NULL)
    {
        printf("El producto no existe\n");
        return NULL;
    }
    else
    {
        if (aux->stock == 0)
        {
            printf("No hay stock del producto que quiere agregar\n");
            return NULL;
        }

        if (aux->stock < item->stock)
        {
            printf("La cantidad de items en stock que hay es menor a la que quiere agregar al carro\n");
            printf("Quiere agregar todo el stock al carro?\n");
            printf("1) Si\n");
            printf("0) No\n");
            while (opcion != 1)
            {
                scanf("%d",&opcion);
                if (opcion != 1 && opcion != 0)
                {
                    printf("ingrese una respuesta valida\n");
                    continue;
                }

                if (opcion == 0)
                {
                    return NULL;
                }
            }

            item->stock = aux->stock;
            aux->stock = 0;
        }
        else
        {
            aux->stock -= item->stock;
        }
    }

    item->precio = aux->precio;
    item->marca = aux->marca;
    item->tipo = aux->tipo;
    return item;
}

/*
    La funcion crear carro esta implementada dentro de la funcion agregar al carro,
    despues de que ingresamos el nombre y comprobar que exista en la lista general, se crea un carro 
    para poder seguir agregando productos, en caso de que se trate de un nuevo carro que
    no haya existido previamente.
*/
void CrearCarro (Map * MapaCarros , char Nombre[])
{
    ShoppingCart * carroAux = (ShoppingCart *) malloc(sizeof(ShoppingCart));
    carroAux->Carro = createMap(is_equal_int);
    carroAux->nombre = (char *) calloc (strlen(Nombre), sizeof(char));
    strcpy(carroAux->nombre , Nombre);
    carroAux->tamanyo = 0;
    insertMap(MapaCarros , carroAux->nombre , carroAux);
}

/*Agregar al carro:
    Es la que se encarga de agregar los productos que queramos al carro, asegurándose que
    el producto exista y de crear un carro nuevo en caso de que queramos. También actualizará
    el stock del producto que ingresemos al carro.
*/
void Agregar_Al_Carro(Map * MapaGeneral , Map * MapaCarros)
{
    ShoppingCart * carroAux;
    Producto * item = (Producto *) malloc(sizeof(Producto));
    Producto * itemAux = (Producto *) malloc(sizeof(Producto));
    char nombre[1024];
    char nombreCarro[1024];
    int cantidad;
    int opcion = 0;

    printf("Si el producto que quiere ingresar se encuentra ya en el carro la cantidad de este aumentara\n");
    printf("ingrese el nombre del producto que desea agregar: ");
    while(1)
    {
        fflush(stdin);
        gets(nombre);
        itemAux = SearcHByName(MapaGeneral , nombre);
        if (itemAux == NULL)
        {
            printf("El elemento ingresado no existe\n");
            printf("Intentelo con otro elemento\n");
            continue;
        }

        break;
    }

    printf("ingrese cuantos \"%s\" desea agregar al carro: ",nombre);
    fflush(stdin);
    scanf("%d",&cantidad);

    printf("Ingrese el nombre del carro al que quiere agregar este producto: \n");
    while(1)
    {
        fflush(stdin);
        gets(nombreCarro);
        carroAux = SearchCartByName(MapaCarros , nombreCarro);
        if (carroAux == NULL)
        {
            printf("El carro ingresado no existe, quiere crear uno con ese mismo nombre?\n");
            printf("1) Si\n");
            printf("0) No\n");
            scanf("%d",&opcion);
            if (opcion == 1)
            {
                CrearCarro(MapaCarros , nombreCarro);
                break;
            }
            
            printf("Vuelva a ingresar el nombre del carro\n");
            continue;
        }

        break;
    }
    
    item->nombre = (char *) calloc (strlen(nombre), sizeof(char));
    strcpy(item->nombre , nombre);
    item->stock = cantidad;

    item = Reducir_Stock(item , MapaGeneral);
    if (item != NULL)
    {
        carroAux = SearchCartByName(MapaCarros , nombreCarro);     //para asegurarme que el current este en donde tiene que estar
        Producto * itemAux = SearcHByName(carroAux->Carro , item->nombre);
        if (itemAux == NULL)
        {
            insertMap(carroAux->Carro , item->nombre , item);
            carroAux->tamanyo += 1;
        }
        else
        {
            itemAux->stock += item->stock;
        }
    }
}

/*Mostrar nombres carros:
    Recorre el MapaCarros para mostrar por pantalla todos los carros distintos que haya
    junto con los elementos distintos que contiene y los datos de estos.
*/
void Mostrar_Nombres_Carros (Map * MapaCarros)
{
    ShoppingCart * aux;
    aux = firstMap(MapaCarros);
    while (aux != NULL)
    {
        printf("Nombre: %s\nEl carro contiene %d elementos distintos.\n\n" , aux->nombre , aux->tamanyo);
        MostrarProductos(aux->Carro);
        aux = nextMap(MapaCarros);  
    }
}

/*Eliminar del Carro:
    Recibe el nombre del carro del que queramos eliminar algún elemento, revisa si este existe,
    y luego recibe el nombre del elemento que queramos eliminar, quitándolo del carro y actualizando
    el stock en el Mapa de los productos, si el carro pasa a tener 0 elementos, este se elimina.
*/
void Eliminar_del_Carro (Map * MapaGeneral , Map * MapaCarros)
{
    ShoppingCart * carroAux;
    Producto * elementoAux;
    char nombreCarro[1024];
    char nombreElemento[1024];
    
    printf("Ingrese el carro del que quiera eliminar algun elemento\n");
    while(1)
    {
        fflush(stdin);
        gets(nombreCarro);
        carroAux = SearchCartByName(MapaCarros , nombreCarro);

        if (carroAux == NULL)
        {
            //pulir esta parte
            printf("El carro ingresado no existe\n");
            printf("Vuelva a ingresar el nombre del carro\n");
            continue;
        }
        break;
    }

    printf("Ingrese el elemento que quiere eliminar\n");
    while(1)
    {
        fflush(stdin);
        gets(nombreElemento);
        elementoAux = SearcHByName(carroAux->Carro , nombreElemento);

        if (elementoAux == NULL)
        {
            //pulir esta parte
            printf("El elemento ingresado no existe en el carro\n");
            printf("Ingrese un elemento valido\n");
            continue;
        }
        break;
    }

    eraseMap(carroAux->Carro , nombreElemento);
    AumentarStock(elementoAux , MapaGeneral);
    carroAux->tamanyo -= 1;
    if (carroAux->tamanyo == 0)
    {
        eraseMap(MapaCarros , nombreCarro);
        free(carroAux);
    }
}

/*Concretar Compra:
    Recibe el nombre del carro del que queremos comprar, revisa si este existe,
    en caso de que sea así, se muestran los productos que se van a comprar y el
    precio final. Luego se elimina el carro. (Habría estado bien preguntar si
    el usuario está de acuerdo con la compra)
*/
void concretar_compra(Map* MapaCarros)
{
    int total = 0;
    char nombreCarro[1240];

    printf("ingrese el nombre del carro que desea concretar su compra\n ");
    fflush(stdin);
    scanf("%s", nombreCarro);
    
    while(SearchCartByName(MapaCarros , nombreCarro)==NULL)
    {
        printf("El carro ingresado no existe vuelva a ingresar\n");
        fflush(stdin);
        gets(nombreCarro);
    }

    ShoppingCart* Cart = SearchCartByName(MapaCarros , nombreCarro);
    Producto * aux2 = (Producto *) malloc(sizeof(Producto));
    aux2 = firstMap(Cart->Carro);
    
    while (aux2 != NULL)
    {
        printf("Nombre: %s\nMarca:  %s\nTipo:   %s\nStock:  %d\nPrecio: $%d\n\n",aux2->nombre,aux2->marca,aux2->tipo,aux2->stock,aux2->precio);
        total += (aux2->precio*aux2->stock);
        aux2 = nextMap(Cart->Carro);
    }
    printf("el total de su compra es de $%d\n",total);

    eraseMap(MapaCarros , nombreCarro);
    free(Cart);
}

/*main:
    Crea los Mapas que se usarán en todo el resto de la función y funciona también
    como menú para seleccionar las opciones que queramos realizar.
    Al final libera la memoria de los mapas que creamos.
*/
int main(int argc, const char * argv[])
{
    Map * Producto_por_tipo  = createMap(is_equal_int);
    Map * Producto_por_marca = createMap(is_equal_int);
    Map * MapaGeneral        = createMap(is_equal_int);
    Map * MapaCarros         = createMap(is_equal_int);
    bool importado = false;
    int opciones = 1; 
    while(opciones != 0)
    {
        
        printf("\nIngrese la opcion que desea utilizar\n\n");
        printf("1)  Importar archivo desde un archivo CSV\n");
        printf("2)  Exportar archivo de productos CSV\n");
        printf("3)  Agregar producto / Aumentar stock de un producto\n");
        printf("4)  Buscar producto por tipo\n");
        printf("5)  Buscar producto por marca\n");
        printf("6)  Buscar producto por nombre\n");
        printf("7)  Mostrar todos los productos\n");
        printf("8)  Agregar al carrito\n");
        printf("9)  Eliminar del carrito\n");
        printf("10) Concretar compra\n");
        printf("11) Mostrar nombres de los carros de compras\n");
        printf("0)  EXIT!!\n\n");
        printf("Ingrese opcion: ");
        scanf("%d", &opciones);

        switch (opciones)
        {
        case 1: ; //Importar archivo desde un archivo CSV
            importar(MapaGeneral,Producto_por_tipo,Producto_por_marca);
            importado = true;
            break;
        case 2:// Exportar productos CSV
            if (importado == false) printf("\nPrimero debe importar el archivo\n");
            else exportarProductosCSV(MapaGeneral);
            break;
        case 3://Agregar producto
            if (importado == false) printf("\nPrimero debe importar el archivo\n");
            else AgregarProducto(MapaGeneral);
            break;
        case 4://Buscar producto por tipo
            if (importado == false) printf("\nPrimero debe importar el archivo\n");
            else BuscarPorTipo(Producto_por_tipo);
            break;
        case 5:// Buscar producto por marca
            if (importado == false) printf("\nPrimero debe importar el archivo\n");
            else BuscarPorMarca(Producto_por_marca);
            break;
        case 6:// Buscar producto por nombre
            if (importado == false) printf("\nPrimero debe importar el archivo\n");
            else BuscarPorNombre(MapaGeneral);
            break;
        case 7:// Mostrar todos los productos
            if (importado == false) printf("\nPrimero debe importar el archivo\n");
            else MostrarProductos(MapaGeneral);
            break;
        case 8:// Agregar al carrito
            if (importado == false) printf("\nPrimero debe importar el archivo\n");
            else Agregar_Al_Carro(MapaGeneral , MapaCarros);
            break;
        case 9://Eliminar del carrito 
            if (importado == false) printf("\nPrimero debe importar el archivo\n");
            else Eliminar_del_Carro(MapaGeneral , MapaCarros);
            break;
        case 10://Concretar compra
            if (importado == false) printf("\nPrimero debe importar el archivo\n");
            else concretar_compra(MapaCarros); //Concretar_Compra(MapaCarros);
            break;
        case 11://Mostrar carritos de compras
            if (importado == false) printf("\nPrimero debe importar el archivo\n");
            else Mostrar_Nombres_Carros(MapaCarros);
            break;
        case 0:// en el caso que la opcion sea 0 el programa termina
            return 0; 
        default:
            printf("\nOpcion no disponible, por favor intentelo de nuevo\n");
            continue;
            break;
        }
    }

    free(MapaGeneral);
    free(MapaCarros);
    free(Producto_por_tipo);
    free(Producto_por_marca);
    return 0;
}
