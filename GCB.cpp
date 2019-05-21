#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>

struct fecha{
	int day, month, year;
};

struct{
	char telefono[50];
	char nombre[100];
	char num_cu[50];
	char nomTemp;
	float dinero;

	struct fecha deposito;
	struct fecha transicion;
	struct fecha retiro;
}a, e, t, r;

void menu();
void crear();
void lista();
void detalles();
void modificar();
void eliminar();
void detalles();
void pago();

char esc;

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
	//Creacion del archivo datos.ojs donde se almacenará toda la información
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
		
		printf("\n Ingrese el numero de cuenta de su tarjeta (ej: 0000-0000-0000-0000): ");
		scanf("%s", &a.num_cu);
		
		printf("\n Ingrese su nombre: ");
		scanf("%c", &a.nomTemp);
		fgets(a.nombre, 100, stdin);
		
		printf("\n Ingrese su telefono: ");
		scanf("%s", &a.telefono);

		printf("\n Ingrese su saldo actual: $");
		scanf("%f", &a.dinero);
		
		//Obtener fecha actual
		time_t T= time(NULL);
    	struct  tm tm = *localtime(&T);
     
    	printf("System Date is: %02d/%02d/%04d\n",tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900);
		scanf("%d/%d/%d", tm.tm_mday, tm.tm_mon, tm.tm_year);
		
		tm.tm_mday = a.deposito.day;
		tm.tm_mon = a.deposito.month;
		tm.tm_year = a.deposito.year;

		//Guardar los datos ingresados en el archivo correspondiente
		fwrite(&a, sizeof(a), 1, fDatos);
		fflush(stdin);

		system("cls");
		printf(" Usuario agregado correctamente");
		printf("\n Presione la tecla ESC para regresar al menu principal, otra tecla para crear otro registro.");

		//Comparación de la tecla presionada
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

	FILE *fDatos;

	int i;
	char tecla;

	//En caso de que no haya ningun registro y si se ingresa a la función lista, regresarlo
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
		printf(" Num. Cuenta\t\tNum. Telefono\t\tNombre\t\t\tSaldo total\n");
		for(i = 0;i<79;i++)
			printf("-");
		
		while(fread(&a, sizeof(a), 1, fDatos) == 1)
		{
			printf("\n %s\t\t%-10s\t%-40s\t$ %.2f", a.num_cu, a.telefono, a.nombre, a.dinero, "\n");
		}
		printf("\n");
		for(i=0;i<79;i++)
			printf("-");

		fclose(fDatos);
		
		//Checar tecla presionada para ir al menu principal
			printf("\n\n\n Presione una tecla para regresar al menu principal");
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

	char num_cu[50];
	int flag = 1;

	fDatos = fopen("datos.ojs", "rb+");

	if(fDatos == 0)
		exit(1);

	fflush(stdin);

	system("cls");

	//Pedir el numero de cuenta a buscar
	printf("Ingrese el numero de cuenta a buscar informacion (ej: 0000-0000-0000-0000): ");
	scanf("%s", num_cu);

	while(fread(&a, sizeof(a), 1, fDatos) == 1){
		if(strcmp(a.num_cu, num_cu) == 0){
			system("cls");
			printf("\t\t\t\t\t\t\n Registro encontrado");
			
			printf("\n Num. cuenta: %s\n Nombre: %s\n Telefono: %s\n Fecha de creacion de la cuenta: %02d/%02d/%04d\n Saldo total: $%.2f", &a.num_cu, &a.nombre, &a.telefono, &a.deposito.day, &a.deposito.month, &a.deposito.year, &a.dinero);
			flag = 0;
			break;
		} else{
			system("cls");
			printf("\n El numero de cuenta no fue encontrado dentro de la BD");	
		}
	}

	printf("\n\n\n Presione la tecla ESC para regresar al menu principal, otra tecla para buscar otro usuario.");
	//Comparación de la tecla presionada
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
