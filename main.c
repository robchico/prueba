/*
 ============================================================================
 Name        : main.c
 Author      : rob
 Version     : 0.1
 Copyright   : Your copyright notice
 Description : proyectoCarni in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <string.h>

char * gets(char *);

typedef struct {
	int codigoCli;  //primarykey
	char dniCli[15];
	char nombreCli[80];
	char direccionCli[100];
	char poblacionCli[50];
	char provinciaCli[30];
	char cpCli[6];
} regClientes;

typedef struct {
	int codigoPro;  //primarykey
	char dniPro[15];
	char nombrePro[80];
	char direccionPro[100];
	char poblacionPro[50];
	char provinciaPro[30];
	char cpPro[6];
} regProveedores;

typedef struct {
	char referenciaArt[20];  //primarykey
	char descrpcionArt[80];
	int existencias;
	int precio;
	int stockMinimo;
	int codigoSec; //FORGEIN KEY tabla secciones
} regArticulos;

typedef struct {
	int codigoSec; //primarykey
	char descrpcionSec[80];
} regSecciones;

typedef struct {
	int codigoIva; //primarykey
	int descrpcionIva;
} regIva;

typedef struct {
	int codigoPago; //primarykey
	char descrpcionPago[80];
} regPagos;

/* funcion para crear el archivo */
void crear(char titulo[15]) {
	FILE *archivo; //, *copiaSeguridad;
	char resp = 'n';

	//leer archivo binario
	if (fopen(titulo, "rb") == NULL) { //el archivo no existe
		//printf("Error: %d, %s\n", sys_nerr, sys_errlist[sys_nerr]);
		archivo = fopen(titulo, "wb"); //leer archivo binario
		printf("fichero creado\n");
		//exit(1); //error

	} else {
		do {
			fflush(stdin);
			printf("Este fichero existe ¿Desea sobrescribirlo? (s/n) ");
			resp = tolower(getchar());
			fflush(stdin);
			if (resp == 's') {
				archivo = fopen(titulo, "wb");
			} else {
				archivo = fopen(titulo, "rb");
			}
		} while (resp != 's' && resp != 'n');
	}

	fclose(archivo);
	//continuar();
}

regClientes rellenarClientes(regClientes clientes) {
	//pedir los datos por pantalla

	printf("Ingrese el codigo del cliente:");
	scanf("%d", &clientes.codigoCli); //&producto.codigo
	fflush(stdin);
	printf("Ingrese el DNI de CLiente:");
	scanf("%s", clientes.dniCli);
	printf("Ingrese el nombre CLiente:");
	scanf("%s", clientes.nombreCli);
	printf("Ingrese la poblacion del CLiente:");
	scanf("%s", clientes.poblacionCli);
	printf("Ingrese la provincia del CLiente:");
	scanf("%s", clientes.provinciaCli);
	printf("Ingrese CP:");
	scanf("%s", clientes.cpCli);
	return clientes;
}
regProveedores rellenarProveedores(regProveedores proveedores) {
	//pedir los datos por pantalla
	printf("Ingrese el codigo del Proveedores:");
	scanf("%d", &proveedores.codigoPro); //&producto.codigo
	fflush(stdin);
	printf("Ingrese el DNI de Proveedores:");
	gets(proveedores.dniPro);
	printf("Ingrese el nombre Proveedores:");
	gets(proveedores.nombrePro);
	printf("Ingrese la poblacion del Proveedores:");
	gets(proveedores.poblacionPro);
	printf("Ingrese la provincia del Proveedores:");
	gets(proveedores.provinciaPro);
	printf("Ingrese CP:");
	scanf("%s", proveedores.cpPro);
        return proveedores;
}
regArticulos rellenarArticulos(regArticulos articulo) {
	//pedir los datos por pantalla
	printf("Ingrese la referencia del articulo:");
	gets(articulo.referenciaArt); 
	fflush(stdin);
	printf("Ingrese la descripcion del articulo:");
	gets(articulo.descrpcionArt);
	printf("Ingrese numero de existencias:");
	scanf("%d",articulo.existencias);
	printf("Ingrese el precio del articulo:");
	scanf("%d",articulo.precio);
	printf("Ingrese el stock minimo:");
	scanf("%d",articulo.stockMinimo);
	printf("Ingrese codigo:");
	scanf("%d", articulo.codigoSec);
        return articulo;
}
regSecciones rellenarSecciones(regSecciones secciones) {
	//pedir los datos por pantalla
	printf("Ingrese codigo secciones:");
	gets(secciones.codigoSec); 
	fflush(stdin);
	printf("Ingrese la descripcion de la seccion:");
	gets(secciones.descrpcionSec);
	
        return secciones;
}
regIva rellenarIva(regIva iva) {
	//pedir los datos por pantalla
	printf("Ingrese codigo iva:");
	gets(iva.codigoIva); 
	fflush(stdin);
	printf("Ingrese la descripcion iva:");
	gets(iva.descrpcionIva);
	
        return iva;
}
/**
 * 
 * @param archivo
 * @param pagos
 * @return 
 * falla siempre pone un 1
 */
int generarCodigo(FILE *archivo,regPagos pagos){
   
    fseek(archivo,0,SEEK_END);
    if((ftell(archivo)/sizeof(regPagos))==0){
        return 1;
    }else{
        fseek(archivo,-sizeof(regPagos),SEEK_CUR);
        pagos.codigoPago = fread(&pagos,sizeof(regPagos),1,archivo);//me pide igualar int
        //registro=fread(&registro,tamayoRegistro,1,fichero);
        return pagos.codigoPago + 1;
    }
    
}
regPagos rellenarPagos(FILE *archivo,regPagos pagos) {
	//pedir los datos por pantalla
	//printf("Ingrese codigo pago:");
	//gets(pagos.codigoPago); 
        pagos.codigoPago=generarCodigo(archivo,pagos);
	fflush(stdin);
	printf("Ingrese la descripcion de la forma de pago:");
	gets(pagos.descrpcionPago);
	
        return pagos;
}


/*cargar datos de 1 estructura dentro del archivo*/
void cargar(char titulo[15]) {
	regClientes clientes;
        regProveedores proveedores;
	regArticulos articulos;
	regSecciones secciones;
	regIva iva;
	regPagos formPagos;

	FILE *archivo;
	archivo = fopen(titulo, "ab"); //abrir para aÃ±adir al archivo binario//strcat(titulo,".dat"); para concatenar los caracteres
	if (archivo == NULL) {
		exit(1);
	}
                    
	if (strncmp(titulo, "Clientes",2) == 0) {
		//pedir los datos por pantalla

		clientes = rellenarClientes(clientes);
                //pasar los datos al archivo
                fwrite(&clientes, sizeof(regClientes), 1, archivo);
                
	}else if (strncmp(titulo, "Proveedores",2) == 0) {
		//pedir los datos por pantalla
		proveedores = rellenarProveedores(proveedores);
                //pasar los datos al archivo
                fwrite(&proveedores, sizeof(regProveedores), 1, archivo);
	}else if (strncmp(titulo, "Articulos",2) == 0) {
		//pedir los datos por pantalla
		articulos = rellenarArticulos(articulos);
                //pasar los datos al archivo
                fwrite(&articulos, sizeof(regArticulos), 1, archivo);
        }else if (strncmp(titulo, "Secciones",2) == 0) {
		//pedir los datos por pantalla
		secciones = rellenarSecciones(secciones);
                //pasar los datos al archivo
                fwrite(&secciones, sizeof(regSecciones), 1, archivo);
	}else if (strncmp(titulo, "Iva",2) == 0) {
		//pedir los datos por pantalla
		iva = rellenarIva(iva);
                //pasar los datos al archivo
                fwrite(&iva, sizeof(regIva), 1, archivo);
        }else if (strncmp(titulo, "Pagos",2) == 0) {
            printf("PAGOS");
		//pedir los datos por pantalla
		formPagos = rellenarPagos(archivo,formPagos);
                //pasar los datos al archivo
                fwrite(&formPagos, sizeof(regPagos), 1, archivo);
        }
        
	fclose(archivo);

}

int menu2(char titulo[15]) {
	regClientes clientes1;
                    regProveedores proveedores1;
                    regArticulos articulos1;
                    regSecciones secciones1;
                    regIva iva1;
                    regPagos formPagos1;
    int opcion;
        system("cls");
	do {

		printf("\t1. AÃ±adir registro %s\n", titulo);
		printf("\t2. Modificar registro %s\n", titulo);
		printf("\t3. Eliminar registro %s\n", titulo);
		printf("\t4. Visualizar registros %s\n", titulo);
		printf("0. <-- Volver\n\n");
		printf("\tIngrese su opcion:  ");
		scanf("%i", &opcion);
                //tolower(titulo);
		switch (opcion) {
		case 1:
			crear(titulo);
			cargar(titulo);
			break;
		case 2:
			//modificacion();
			break;
		case 3:
			//listado();
                    
                        listado(regArticulos articulos1,titulo);
			break;
		case 4:
			//consulta();
			break;
		case 5:
			//
			break;
		case 6:

			break;
		}
	} while (opcion != 0);
	return 0;
}

int main() {
	int opcion;
        system("chcp 65001");system("cls");
        
	do {
		printf("1 - Menu Clientes\n");
		printf("2 - Menu Proveedores\n");
		printf("3 - Menu Articulos\n");
		printf("4 - Menu Secciones\n");
		printf("5 - Menu IVA\n");
		printf("6 - Menu Formas de Pago\n");
		printf("0 - SAlir\n\n");
		printf("\tIngrese su opcion:  ");
		scanf("%i", &opcion);
		switch (opcion) {
		case 1:
			menu2("Clientes");
			break;
		case 2:
			menu2("Proveedores");
			break;
		case 3:
			menu2("Articulos");
			break;
		case 4:
			menu2("Secciones");
			break;
		case 5:
			menu2("IVA");
			break;
		case 6:
			menu2("Pagos");
			break;
		}
	} while (opcion != 0);
	return 0;
}


/*mostar una lista de los productos*/
void listado(struct estructura,char titulo[15]) {

    FILE *archivo;
    archivo = fopen(titulo, "rb"); //abrir el archivo en modo lectura binaria
    if (archivo == NULL) {
        exit(1);
    }


    fread(&estructura, sizeof (void), 1, archivo); //leo los datos
    printf(" Codigo Descripcion Precio \n-----------------------------------\n");
    //mientras tenga datos el archivo ejecuta
    while (!feof(archivo)) {
        printf("   %i       %s       %0.2f\n", estructura.codigoCli, estructura.descripcion, estructura.precio);
        fread(&estructura, sizeof (struct), 1, archivo); //mientrar tenga datos sigue leyendo
    }

    fclose(archivo);
   
}