#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>

//Variables globales
char esc;

//Estructuras
struct fecha{
	int day, month, year;
};

struct{
	char telefono[50];
	char nombre[100];
	char num_cu[20];
	char nomTemp;
	float dinero;

	struct fecha creacion;
	struct fecha deposito;
	struct fecha transicion;
	struct fecha retiro;
}a, el, ed, ch;

//Funciones
void menu();
void crear();
void lista();
void detalles();
void modificar();
void eliminar();
void pago();

int main(){
	menu();
}

void menu(){
	int opcion;

	printf("\n\t\t\t\t\t\t MENU PRINCIPAL");
	printf("\n\n\t1. Crear una nueva cuenta.");
	printf("\n\t2. Ver una lista de todas las cuentas creadas.");
	printf("\n\t3. Ver detalles de una cuenta.");
	printf("\n\t4. Modificar informacion de una cuenta.");
	printf("\n\t5. Recargar saldo.");
	printf("\n\t6. Eliminar una cuenta existente.");
	printf("\n\t7. Salir.");
	printf("\n\n\tIngrese una opcion: ");
	scanf("%d", &opcion);

	switch(opcion){
		case 1:
			crear();
			break;
		case 2:
			lista();
			break;
		case 3:
			detalles();
			break;
		case 4:
			modificar();
			break;
		case 5:
			pago();
			break;
		case 6:
			eliminar();
			break;
		case 7:
			printf("\n\n\n\tRegrese pronto...");
			exit(1);
			break;
		default:
			printf("\n\n\tFavor de ingresar una opcion correcta!");
			getch();
			system("cls");
			menu();
	}
}

void crear(){
	//Creacion del archivo datos.ojs donde se almacenar� toda la informaci�n
	FILE *fDatos;
	fDatos = fopen("datos.ojs", "ab+");
	//Checar si existe el archivo
	if(fDatos == 0){
		fDatos = fopen("datos.ojs", "wb+");

		system("cls");

		printf("Espere mientras se crea la BD");
		printf("\nPresione una tecla para continuar...");
		getch();
	}

	while(1){
		system("cls");
		
		crear_u:
		printf(" Ingresa la fecha actual (ej: dd/mm/aa): ");
		scanf("%d/%d/%d", &a.creacion.day, &a.creacion.month, &a.creacion.year);

		printf("\n Ingrese el numero de cuenta de su tarjeta (ej: 0000-0000-0000-0000): ");
		scanf("%s", &ch.num_cu);

		//Comparar el número de cuenta ingresado y checar si este existe dentro de los datos guardados
		while(fscanf(fDatos, "%s %s %s %s %f %d/%d/%d", &a.telefono, &a.nombre, &a.num_cu, &a.dinero, &a.creacion.day, &a.creacion.month, &a.creacion.year) != EOF){
			if(ch.num_cu == a.num_cu){
				printf("El numero de cuenta ingresado ya existe!");

				getch();
				goto crear_u;
			}
		}
		a.nombre == ch.num_cu;
		
		printf("\n Ingrese su nombre: ");
		scanf("%c", &a.nomTemp);
		fgets(a.nombre, 100, stdin);
		printf("\n Ingrese su telefono: ");
		scanf("%s", &a.telefono);
		printf("\n Ingrese su saldo actual: $");
		scanf("%f", &a.dinero);

		//Guardar los datos ingresados en el archivo correspondiente
		fwrite(&a, sizeof(a), 1, fDatos);
		fflush(stdin);

		system("cls");
		printf("\t\t\t\t\t\t Usuario agregado correctamente!");
		printf("\n\n Presione la tecla ESC para regresar al menu principal, otra tecla para crear otro registro.");
		esc = getche();
		if(esc==27)
			system("cls");
			menu();
	}

	fclose(fDatos);
}

void lista()
{
	system("cls");

	printf("\n\t\t\tSi el usuario que acaba de agregar no aparece, reinicie el programa.\n\n\n\n");

	FILE *fDatos;

	int i;
	char tecla;

	//En caso de que no haya ningun registro y si se ingresa a la funci�n lista, regresarlo
	if((fDatos = fopen("datos.ojs", "rb")) == NULL){
		system("cls");

		printf("\n No hay ningun usuario registrado dentro del sistema!");

		printf("\n\n\n Presione cualquier tecla para regresar al menu principal...");
		esc = getche();
		if (esc != 27){
			system("cls");
			menu();
		}
	}else{
		printf(" Num. Cuenta\t\tNum. Telefono\t\tNombre\t\tCreacion de la cuenta\n");
		for(i = 0;i<99;i++)
			printf("-");
		
		while(fread(&a, sizeof(a), 1, fDatos) == 1){
			printf("\n %s\t%s\t\t\t%s\t%02d/%02d/%02d", a.num_cu, a.telefono, a.nombre, a.creacion.day, a.creacion.month, a.creacion.year);

			printf("\n");
			for(i=0;i<99;i++)
				printf("-");
		}
		for(i=0;i<99;i++)
			printf("-");

		fclose(fDatos);
		
		printf("\n\n\n Presione una tecla para regresar al menu principal...");
		tecla = getche();
		if(tecla != 27){
			system("cls");
			menu();	
		}else{
			system("cls");
			menu();
		}
	}
}

void detalles(){
	FILE *fDatos;

	char num_cu[20];
	int flag = 1;

	fDatos = fopen("datos.ojs", "rb+");

	if(fDatos == 0){
		system("cls");
		printf(" No hay ningun registro dentro de la BD!");

		printf("\n\n\n Presione una tecla para regresar al menu principal...");
		esc = getche();
		if(esc != 27){
			system("cls");
			menu();	
		}else{
			system("cls");
			menu();
		}
	}

	fflush(stdin);

	system("cls");

	//Pedir el numero de cuenta a buscar
	printf("\n Ingrese el numero de cuenta a buscar informacion (ej: 0000-0000-0000-0000): ");
	scanf("%s", num_cu);

	while(fread(&a, sizeof(a), 1, fDatos) == 1){
		if(strcmp(a.num_cu, num_cu) == 0){
			system("cls");
			printf("\n\t\t\t\t\t\t Registro encontrado");
			
			printf("\n Num. cuenta: %s\n Nombre: %s\n Telefono: %s\n Fecha de creacion de la cuenta: %02d/%02d/%02d\n Saldo total: $%.2f", &a.num_cu, &a.nombre, &a.telefono, &a.creacion.day, &a.creacion.month, &a.creacion.year, &a.dinero);
			flag = 0;
			break;
		} else{
			system("cls");
			printf("\n El numero de cuenta no fue encontrado dentro de la BD");	
		}
	}

	printf("\n\n\n Presione la tecla ESC para regresar al menu principal, otra tecla para buscar otro usuario.");
	esc = getche();
	if(esc==27){
		system("cls");
		menu();
	}else{
		system("cls");
		detalles();
	}

	fclose(fDatos);
}

void modificar(){
	printf("\nmodificar");
}

void eliminar(){
	printf("\neliminar");
}

void pago(){
	printf("\npago");
}
