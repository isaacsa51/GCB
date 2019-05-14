#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

struct datos_cliente{
	char nombre[100];
	int edad;
	long telefono;	
}add;

void nueva_cu(){
	FILE *fDatos;
	char tecla;
	fDatos=fopen("datos.dat","ab+");

	if(fDatos==0){   
		fDatos=fopen("datos.dat","wb+");
		system("cls");
		printf("Espere un momento en lo que se guardan los datos...");
		printf("\n\nPresione una tecla para continuar.");
		getch();
	}

	while(1){
		system("cls");
		printf("\n\t\t\t\t\t\tCREAR NUEVO USUARIO");
		printf("\n Ingrese su nombre: ");
		scanf("%s", &add.nombre);
		
		printf("\n Ingrese su edad: ");
		scanf("%d",&add.edad);
		fflush(stdin);
		
		printf("\n Ingrese su numero de celular: ");
		scanf("%lf", &add.telefono);
		
		fwrite(&add, sizeof(add), 1, fDatos);
		fflush(stdin);
		
		system("cls");
		
		printf("Usuario agregado correctamente");
		
		//Checar si la tecla que se presione es ESC para salir, si no ejecutar la función de nuevo
		printf("\n Presione la tecla ESC para volver al menu principal, si cualquier otra letra para introducir otro usuario.");
		tecla = getche();
		if(tecla ==27)
			break;
	}
	fclose(fDatos);
}

void detalles_cu(){
	system("cls");
	printf("\nDETALLES");
}

void edit_cu(){
	system("cls");
	printf("\nEDITAR");
}

void rec_saldo(){
	system("cls");
	printf("\nRECARGA");
}

void deposito(){
	system("cls");
	printf("\nDEPOSITO");
}

void elim_cu(){
	system("cls");
	printf("\nELIMINAR CUENTA");
}

void salir(){
	printf("\n\n\nRegrese pronto...");
	exit(1);
}

void main_menu(){
	int opcion;

	printf("\n\t\t\t\t\t\t MENU PRINCIPAL");
	printf("\n\n\t1. Crear una nueva cuenta.");
	printf("\n\t2. Ver detalles de la cuenta");
	printf("\n\t3. Modificar informacion de una cuenta");
	printf("\n\t4. Recargar saldo");
	printf("\n\t5. Hacer un deposito");
	printf("\n\t6. Eliminar una cuenta existente");
	printf("\n\t7. Salir");
	
	printf("\n\n\tIngrese una opcion: ");
	scanf("%d", &opcion);

	switch(opcion){
		case 1:
			nueva_cu();
			break;

		case 2:
			detalles_cu();
			break;

		case 3:
			edit_cu();
			break;

		case 4:
			rec_saldo();
			break;

		case 5:
			deposito();
			break;

		case 6:
			elim_cu();
			break;
		
		case 7:
			salir();
			break;
			
		default:
			system("cls");
			printf("\nFavor de ingresar una opcion correcta");
			system("cls");
			main_menu();
	}
}

main(){
	main_menu();
}
