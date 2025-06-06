#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10

///Estructuras///
typedef struct
{
    int legajo;
    char nombreYapellido [30];
    int edad;
    int anio;
} stAlumno;

///Prototipos///
stAlumno crearAlumno();
void agregarAlArchivo(char nombre[]);
void mostrarArchivo();
int cantidadRegistros(char archivo[]);
void cargarDos(char archivo[]);
void mostrarUnAlumno(stAlumno a);
void mostrarRegistros(char nombre[]);
void agregarUnElemento(char nombre[]);
int pasarLegajoMayores(char nombre[], int arreglo[], int *cantidad);
void mostrarArreglo(int arreglo[], int cant);
int contarMayoresA(char nombre[], int edad);
void mostrarPorRango(char nombre[], int min, int max);
stAlumno obtenerMayor(char nombre[]);
int cantPorAnio (char nombre[], int anioBuscado);
int cargaArreglo(stAlumno a[], int dimension);
void arrayToArchivo(char nombre[], stAlumno arreglo[], int cantidad);
int archivoToArray(char nombre[], stAlumno arreglo[], int dimension, int anio);

///Main///
int main()
{
    char archivo[] = "alumnos.bin";
    int opcion;
    int registrados;
    int legajoMayores[MAX];
    int cantidad=0;
    int cantMayores = 0;

    do
    {
        printf("=== MENU ===\n");
        printf("1. Agregar alumno/s\n");
        printf("2. Mostrar contenido del archivo\n");
        printf("3. Contar cantidad de registros\n");
        printf("4. Cargar dos alummnos\n");
        printf("5. Mostrar registros de archivo\n");
        printf("6. Agregar UN alumno\n");
        printf("7. Agregar legajo de alumnos mayores a mi arreglo\n");
        printf("8. Mostrar arreglo de mayores\n");
        printf("9. Contar alumnos mayores a una edad\n");
        printf("10. Mostrar alumnos por rango de edad\n");
        printf("11. Mostrar cantidad de alumnos por anio\n");
        printf("12. Obtener alumno mayor\n");
        printf("13. Pasar arreglo de alumnos al archivo\n");
        printf("14. Pasar alumnos de archivo a arreglo\n");
        printf("0. Salir\n");
        printf("Seleccione una opci�n: ");
        scanf("%d", &opcion);

        switch(opcion)
        {
        case 1:
            agregarAlArchivo(archivo);
            system("pause");
            system("cls");
            break;
        case 2:
            mostrarArchivo(archivo);
            system("pause");
            system("cls");
            break;
        case 3:
            registrados = cantidadRegistros(archivo);
            printf("\nEl Archivo contiene %d alumnos registrados.", registrados);
            system("pause");
            system("cls");
            break;
        case 4:
            cargarDos(archivo);
            system("pause");
            system("cls");
            break;
        case 5:
            mostrarRegistros(archivo);
            system("pause");
            system("cls");
            break;
        case 6:
            agregarUnElemento(archivo);
            system("pause");
            system("cls");
            break;
        case 7:
            pasarLegajoMayores(archivo, legajoMayores, &cantidad);
            system("pause");
            system("cls");
            break;
        case 8:
            mostrarArreglo(legajoMayores, cantidad);
            system("pause");
            system("cls");
            break;
        case 9:
            int edad;
            printf("/nIngrese la edad de referncia:");
            fflush(stdin);
            scanf(" %d", &edad);
            cantMayores = contarMayoresA(archivo, edad);
            printf("\nCantidad de alumnos mayores a %d: %d\n", edad, cantMayores);
            system("pause");
            system("cls");
            break;
        case 10:
            int min, max;
            printf("\nIngrese la edad minima:");
            fflush(stdin);
            scanf(" %d", &min);
            printf("\nIngrese la edad maxima:");
            fflush(stdin);
            scanf(" %d", &max);
            mostrarPorRango(archivo, min, max);
            system("pause");
            system("cls");
            break;
        case 11:
            int aux=0;
            int anioBuscado;
            printf("\nIngrese el anio que desea buscar:");
            fflush(stdin);
            scanf(" %d", &anioBuscado);
            aux = cantPorAnio(archivo, anioBuscado);
            printf("\nLa cantidad de alumnos registrados en %d son %d.", anioBuscado, aux);
            system("pause");
            system("cls");
            break;
        case 12:
            stAlumno mayor;
            mayor = obtenerMayor(archivo);
            mostrarUnAlumno(mayor);
            system("pause");
            system("cls");
            break;
        case 13:
            int cantidad;
            stAlumno lista[50];
            cantidad = cargaArreglo(lista, 50);
            arrayToArchivo(archivo, lista, cantidad);
            system("pause");
            system("cls");
            break;
        case 14:
            stAlumno arregloporanio[50];
            int anio;
            printf("\nIngrese anio deseado:");
            fflush(stdin);
            scanf(" %d", &anio);
            archivoToArray(archivo, arregloporanio, 50, anio);
            system("pause");
            system("cls");
            break;
        case 0:
            printf("\nSaliendo del programa...");
            break;
        default:
            printf("Opci�n inv�lida. Intente nuevamente.\n");
        }

    }
    while(opcion != 0);
}

///Funciones///
/* Ejercicio 1 */
stAlumno crearAlumno()
{
    stAlumno a;

    printf("Ingrese el legajo del alumno:");
    fflush(stdin);
    scanf(" %d", &a.legajo);
    while (getchar() != '\n');  // <-- limpia el buffer manualmente

    printf("\nIngrese el nombre y el apellido del alumno:");
    fflush(stdin);
    fgets(a.nombreYapellido, 30, stdin);
    // eliminar salto de l�nea al final si est�
    size_t len = strlen(a.nombreYapellido);
    if (len > 0 && a.nombreYapellido[len - 1] == '\n')
    {
        a.nombreYapellido[len - 1] = '\0';
    }

    printf("\nIngrese edad: ");
    fflush(stdin);
    scanf("%d", &a.edad);

    printf("\nIngrese el anio de cursada:");
    fflush(stdin);
    scanf(" %d", &a.anio);

    return a;
}

void agregarAlArchivo(char nombre[])
{
    FILE *arch;
    arch = fopen(nombre, "ab");
    char aux = 's';
    stAlumno a;

    while(aux == 's')
    {
        a = crearAlumno();
        fwrite(&a, sizeof(stAlumno), 1, arch);

        printf("�Desea cargar otro alumno? (s/n): ");
        fflush(stdin);
        scanf(" %c", &aux);
        system("cls");
    }
    fclose(arch);
}

/* Ejercicio 2 */
void mostrarArchivo()
{
    stAlumno a;
    FILE *arch = fopen("alumnos.bin", "rb");

    fread(&a,sizeof(stAlumno),1,arch);
    printf("\n=============================================================");
    while(!feof(arch))
    {
        printf("\nLegajo: %d",a.legajo);
        printf("\nNombre y Apellido: %s",a.nombreYapellido);
        printf("\nEdad: %d",a.edad);
        printf("\nAnio de Cursada: %d",a.anio);
        printf("\n=============================================================");
        fread(&a,sizeof(stAlumno),1,arch);
    }
    system("pause");
    system("cls");
}

/* Ejercicio 3 */
int cantidadRegistros(char archivo[])
{
    stAlumno a;
    FILE *arch;
    arch = fopen(archivo, "rb");
    int contador = 0;

    while(fread(&a, sizeof(stAlumno), 1, arch) == 1)
    {
        contador++;
    }

    fclose(arch);

    return contador;
}

/* Ejercicio 4 */
void cargarDos(char archivo[])
{
    FILE *arch;
    arch = fopen(archivo, "rb");
    stAlumno a;

    if(arch == NULL)
    {
        printf("\nElArchivo no esta creado, creando archivo...");
        arch = fopen(archivo, "wb");
    }
    else
    {
        fclose(arch);
        arch = fopen(archivo, "ab");
    }

    for(int i = 0; i<2; i++)
    {
        a=crearAlumno();
        fwrite(&a, sizeof(stAlumno), 1, arch);
    }
    fclose(arch);
}

/* Ejercicio 5 */
void mostrarUnAlumno(stAlumno a)
{
    printf("===============================");
    printf("\nNombre: %s", a.nombreYapellido);
    printf("\nEdad: %d",a.edad);
    printf("\nAnio de Cursada: %d",a.anio);
    printf("\n==============================");

}

void mostrarRegistros(char nombre[])
{
    FILE *arch;
    arch = fopen(nombre, "rb");
    stAlumno aux;

    if(arch == NULL)
    {
        return;
    }
    while(fread(&aux,sizeof(stAlumno),1,arch) == 1)
    {
        mostrarUnAlumno(aux);
    }
    fclose(arch);
    system("pause");
    system("cls");
}

/* Ejercicio 6 */
void agregarUnElemento(char nombre[])
{
    FILE *arch;
    arch= fopen(nombre, "ab");
    stAlumno aux;

    if(arch == NULL)
    {
        return;
    }
    aux=crearAlumno();
    fwrite(&aux, sizeof(stAlumno), 1, arch);
    fclose(arch);
    printf("\nAlumno agregado...");
    system("pause");
    system("cls");
}

/* Ejercicio 7 */
int pasarLegajoMayores(char nombre[], int arreglo[], int *cantidad)
{
    FILE *arch;
    arch= fopen(nombre, "rb");
    stAlumno a;
    int i = 0;

    if(arch == NULL )
    {
        return 0; //Error
    }

    while(fread(&a, sizeof(stAlumno), 1, arch) == 1)
    {
        if(a.edad >= 18)
        {
            arreglo[i] = a.legajo;
            i++;
        }
    }
    *cantidad = i;
    fclose(arch);
    system("pause");
    system("cls");
}

void mostrarArreglo(int arreglo[], int cant)
{
    for(int i=0; i<cant; i++)
    {
        printf("\n============================");
        printf("\nLegajo: %d", arreglo[i]);
    }
    system("pause");
    system("cls");
}

/* Ejercicio 8 */
int contarMayoresA(char nombre[], int edad)
{
    FILE *arch;
    arch = fopen(nombre, "rb");
    int contador = 0;
    stAlumno aux;

    if(arch == NULL)
    {
        return 0;
    }

    while(fread(&aux, sizeof(stAlumno), 1, arch) == 1)
    {
        if(aux.edad >= edad)
        {
            contador++;
        }
    }
    fclose(arch);
    return contador;
}

/* Ejercicio 9 */
void mostrarPorRango(char nombre[], int min, int max)
{
    FILE *arch;
    arch = fopen(nombre, "rb");
    stAlumno aux;

    if(arch == NULL)
    {
        return;
    }

    while(fread(&aux, sizeof(stAlumno), 1, arch) == 1)
    {
        if(aux.edad > min && aux.edad < max)
        {
            mostrarUnAlumno(aux);
        }
    }
    fclose(arch);
}

/* Ejercicio 10 */
stAlumno obtenerMayor(char nombre[])
{
    FILE *arch;
    arch = fopen(nombre, "rb");
    int primero = 1;
    stAlumno aux, mayor;

    if(arch == NULL)
    {
        return aux;
    }

    while(fread(&aux, sizeof(stAlumno), 1, arch) == 1)
    {
        if(primero)
        {
            mayor = aux;
            primero = 0;
        }
        else if( aux.edad > mayor.edad)
        {
            mayor = aux;
        }
    }
    fclose(arch);
    return mayor;
}

/* Ejercicio 11 */
int cantPorAnio (char nombre[], int anioBuscado)
{
    FILE *arch;
    arch = fopen(nombre, "rb");
    stAlumno aux;
    int contador= 0;

    if(arch == NULL)
    {
        return 0;
    }

    while(fread(&aux, sizeof(stAlumno), 1, arch) == 1)
    {
        if(aux.anio == anioBuscado)
        {
            contador++;
        }
    }
    fclose(arch);
    return contador;
}

/* Ejercicio 12 A*/
//FUNCION AUXILIAR//
int cargaArreglo(stAlumno a[], int dimension)
{
     int i=0;
    char letra ='s';
    printf("\n\nIngrese nuevos alumnos al arreglo\n\n");

    while(letra=='s' && i<dimension)
    {
        a[i]= crearAlumno();
        i++;

        printf("\n Quiere seguir cargando? Presione s o n ");
        fflush(stdin);
        scanf(" %c", &letra);
    }
    return i;
}
void arrayToArchivo(char nombre[], stAlumno arreglo[], int cantidad)
{
    FILE *arch;
    arch = fopen(nombre, "ab");

    if(arch!=NULL)
    {
        fwrite(arreglo, sizeof(stAlumno), cantidad, arch);
        fclose(arch);
    }
}

/* Ejercicio 12 B*/
int archivoToArray(char nombre[], stAlumno arreglo[], int dimension, int anio)
{
    FILE *arch;
    arch = fopen(nombre, "rb");
    int i=0;

    if(arch != NULL)
    {
        stAlumno aux;

        while(fread(&aux, sizeof(stAlumno), 1, arch) == 1)
        {
            arreglo[i] = aux;
            i++;
        }
    }
    fclose(arch);
    return i;
}
