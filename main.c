#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 10

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

///Main///
int main()
{
    char archivo[] = "alumnos.bin";
    int opcion;
    int registrados;
    int legajoMayores[max];
    int cantidad=0;

    do
    {
        printf("\n=== MENU ===\n");
        printf("1. Agregar alumno/s\n");
        printf("2. Mostrar contenido del archivo\n");
        printf("3. Contar cantidad de registros\n");
        printf("4. Cargar dos alummnos\n");
        printf("5. Mostrar registros de archivo\n");
        printf("6. Agregar UN alumno\n");
        printf("7. Agregar legajo de alumnos mayores a mi arreglo\n");
        printf("8. Mostrar arreglo de mayores\n");
        printf("0. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch(opcion)
        {
        case 1:
            agregarAlArchivo(archivo);
            break;
        case 2:
            mostrarArchivo(archivo);
            break;
        case 3:
            registrados = cantidadRegistros(archivo);
            printf("\nEl Archivo contiene %d alumnos registrados.", registrados);
            break;
        case 4:
            cargarDos(archivo);
            break;
        case 5:
            mostrarRegistros(archivo);
            break;
        case 6:
            agregarUnElemento(archivo);
            break;
        case 7:
            pasarLegajoMayores(archivo, legajoMayores, &cantidad);
            break;
        case 8:
            mostrarArreglo(legajoMayores, cantidad);
            break;
        case 0:
            printf("Saliendo del programa...\n");
            break;
        default:
            printf("Opción inválida. Intente nuevamente.\n");
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
    // eliminar salto de línea al final si está
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

        printf("¿Desea cargar otro alumno? (s/n): ");
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
