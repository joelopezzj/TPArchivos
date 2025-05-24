#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
///Main///
int main()
{
    char archivo[] = "alumnos.bin";
    int opcion;
    int registrados;

    do {
        printf("\n=== MENU ===\n");
        printf("1. Agregar alumno/s\n");
        printf("2. Mostrar contenido del archivo\n");
        printf("3. Contar cantidad de registros\n");
        printf("4. Cargar dos alummnos\n");
        printf("0. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch(opcion) {
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
            case 0:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción inválida. Intente nuevamente.\n");
        }

    } while(opcion != 0);
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
    }else
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
