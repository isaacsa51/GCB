	#include <stdio.h>
	#include <stdlib.h>
	#include <conio.h>
	#include <windows.h>

	void main_menu();

	void delay(int j){
		int i, k;

		for(i=0; i<j; i++)
			k=i;
	}

	char tecla;

	struct fecha{
		int dia, mes, anio;
	};

	struct datos_cliente{
		char nombre[100];
		char num_cu[250];
		char nomTemp;		//Variable temporal
		int edad;
		long telefono;	
		
		struct fecha deposito;
	}add, check;

	void nueva_cu(){
		FILE *fDatos;
		fDatos=fopen("datos.txt","ab+");

		nueva_cuenta:

		if(fDatos==0){   
			fDatos=fopen("datos.txt","wb+");
			system("cls");
			printf("\tEspere un momento en lo que se guardan los datos...");
			printf("\t\n\nPresione una tecla para continuar.");
			getch();
		}

		while(1){
			system("cls");
			printf("\n\t\t\t\t\t\tCREAR NUEVO USUARIO");

			printf("\n\t Ingrese fecha actual (dd/mm/aa): ");
			scanf("%d/%d/%d", &add.deposito.dia, &add.deposito.mes, &add.deposito.anio);

			/*

			//Pedir número de cuenta y checar si ya existe dentro de los registros para no guardarlo en caso de que ya exista
			printf("\n\t Ingrese el numero de cuenta (ej: 0000-0000-0000-0000): ");
			scanf("%s", &check.num_cu);
			//Checar si existe
			while(fscanf(fDatos, "%s %s %d %lf %d/%d/%d", &add.nombre, &add.num_cu, &add.edad, &add.telefono, &add.deposito.dia, &add.deposito.mes, &add.deposito.anio) != EOF){
				if(check.num_cu == add.num_cu){
					printf("\n\t El numero de cuenta ingresado ya existe!");
					delay(1000000);
					goto nueva_cuenta; //Redirigir a la creación de cuenta
				}
			}

			//add.num_cu=check.num_cu;
		
			*/

			printf("\n\t Ingrese su nombre: ");
			scanf("%c", &add.nomTemp);		//Guarda el valor de nombre en una variable "temporal" para liberar el buffer y poder guardar un char con espacios
			fgets(add.nombre, 100, stdin);
			
			printf("\n\t Ingrese su edad: ");
			scanf("%d",&add.edad);
			fflush(stdin);
			
			printf("\n\t Ingrese su numero de celular: ");
			scanf("%lf", &add.telefono);
			
			fwrite(&add, sizeof(add), 1, fDatos);
			fflush(stdin);
			
			system("cls");
			
			printf("\n Usuario agregado correctamente");
			
			//Checar si la tecla que se presione es ESC para salir, si no ejecutar la función de nuevo
			printf("\n Presione la tecla ESC para volver al menu principal, si cualquier otra letra para introducir otro usuario.");
			tecla = getche();
			if(tecla == 27){
				system("cls");
				main_menu();	
			}
		}
		fclose(fDatos);
	}

	void lista_cu(){
		system("cls");

		FILE *fDatos;

		//Checa si hay datos dentro del sistema, si no existe que se regrese al menu principal
		if ((fDatos = fopen("datos.txt", "rb")) == NULL){
			system("cls");

			printf("\n No hay ningun usuario registrado dentro del sistema!");

			printf("\n\n\n Presione cualquier tecla para regresar al menu principal...");
			tecla = getche();
			if (tecla != 27){
				system("cls");
				main_menu();
			}
			
			system("cls");

			main_menu();
		}else{
			system("cls");

			printf("\nNOMBRE\t\tEDAD\t\tNUM. TELEFONO\t\t\n");

			for(int i=0; i<79; i++)
				printf("-");

			while(fread(&add, sizeof(add), 1, fDatos) == 1){
				printf("\n%s\t\t%d\t\t%lf", &add.nombre, &add.edad, &add.telefono);
			}

			// fread(&add, sizeof(add), 50, fDatos);
			// printf("\n%s", &add.nombre);

			for(int i=0;i<79;i++)
				printf("-");
			
			fclose(fDatos);
			
			//Checar tecla presionada para ir al menu principal
			printf("\n\n\n Presione una tecla para regresar al menu principal");
			tecla = getche();
			if(tecla != 27){
				system("cls");
				main_menu();	
			}else{
				system("cls");
				main_menu();
			}
		}
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
		printf("\n\n\n\tRegrese pronto...");
		exit(1);
	}

	void main_menu(){
		int opcion;

		printf("\n\t\t\t\t\t\t MENU PRINCIPAL");
		printf("\n\n\t1. Crear una nueva cuenta.");
		printf("\n\t2. Ver una lista de todas las cuentas creadas");
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
				lista_cu();
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

