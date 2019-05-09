
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <string.h>

//char * gets(char *);

typedef struct {
	int codigoCli; //primarykey
	char dniCli[15];
	char nombreCli[80];
	char direccionCli[100];
	char poblacionCli[50];
	char provinciaCli[30];
	char cpCli[6];
} regClientes;

typedef struct {
	int codigoPro; //primarykey
	char dniPro[15];
	char nombrePro[80];
	char direccionPro[100];
	char poblacionPro[50];
	char provinciaPro[30];
	char cpPro[6];
} regProveedores;

typedef struct {
	char referenciaArt[20]; //primarykey
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

void continuar() {
	printf("Presione una tecla para continuar.....\n");
	getchar();
}

/* funcion para crear el archivo */
void crear(char titulo[15]) {
	FILE *archivo; //, *copiaSeguridad;
	char resp = 'n';

	//leer archivo binario
	if (fopen(titulo, "rb") == NULL) { //el archivo no existe
		//printf("Error: %d, %s\n", sys_nerr, sys_errlist[sys_nerr]);
		archivo = fopen(titulo, "wb"); //leer archivo binario
		printf("El fichero %s se ha creado correctamente\n ", titulo);
		//exit(1); //error

	} else {
		printf(
				"\nEl fichero %s existe y puede que contenga datos Â¿Desea sobrescribirlo? (s/n) ",
				titulo);
		do {
			resp = tolower(getchar());
			//scanf("%c\r",&resp);

			if (resp == 's') {
				archivo = fopen(titulo, "wb");
			} else {
				archivo = fopen(titulo, "rb");
			}

		} while (resp != 's' && resp != 'n');
	}

	fclose(archivo);
	continuar();
}

regClientes rellenarClientes(char modificar, regClientes clientes) {
	//pedir los datos por pantalla
	if (modificar == 'n') {
		printf("Ingrese el codigo del cliente:");
		scanf("%d", &clientes.codigoCli);
	}

	fflush(stdin);
	printf("Ingrese el DNI de CLiente:");
	scanf("%s", clientes.dniCli);
	printf("Ingrese el nombre CLiente:");
	scanf("%s", clientes.nombreCli);
	printf("Ingrese la direccion del CLiente:");
	scanf("%s", clientes.direccionCli);
	printf("Ingrese la poblacion del CLiente:");
	scanf("%s", clientes.poblacionCli);
	printf("Ingrese la provincia del CLiente:");
	scanf("%s", clientes.provinciaCli);
	printf("Ingrese CP:");
	scanf("%s", clientes.cpCli);
	return clientes;
}

regProveedores rellenarProveedores(char modificar, regProveedores proveedores) {
	//pedir los datos por pantalla
	if (modificar == 'n') {
		printf("\nIngrese el codigo del Proveedores:");
		scanf("%d", &proveedores.codigoPro); //&producto.codigo
	}

	fflush(stdin);
	printf("Ingrese el DNI de Proveedores:");
	fgets(proveedores.dniPro, sizeof(proveedores.dniPro), stdin);
	printf("Ingrese el nombre Proveedores:");
	fgets(proveedores.nombrePro, sizeof(proveedores.nombrePro), stdin);
	printf("Ingrese la direccion del Proveedores:");
	fgets(proveedores.direccionPro, sizeof(proveedores.direccionPro), stdin);
	printf("Ingrese la poblacion del Proveedores:");
	fgets(proveedores.poblacionPro, sizeof(proveedores.poblacionPro), stdin);
	printf("Ingrese la provincia del Proveedores:");
	fgets(proveedores.provinciaPro, sizeof(proveedores.provinciaPro), stdin);
	printf("Ingrese CP:");
	scanf("%s", proveedores.cpPro);
	return proveedores;
}

regArticulos rellenarArticulos(char modificar, regArticulos articulo) {
	//pedir los datos por pantalla
	if (modificar == 'n') {
		printf("\nIngrese la referencia del articulo:");
		fgets(articulo.referenciaArt, sizeof(articulo.referenciaArt), stdin);
	}

	fflush(stdin);
	printf("Ingrese la descripcion del articulo:");
	fgets(articulo.descrpcionArt, sizeof(articulo.descrpcionArt), stdin);
	printf("Ingrese numero de existencias:");
	scanf("%d", &articulo.existencias);
	printf("Ingrese el precio del articulo:");
	scanf("%d", &articulo.precio);
	printf("Ingrese el stock minimo:");
	scanf("%d", &articulo.stockMinimo);
	printf("Ingrese codigo:");
	scanf("%d", &articulo.codigoSec);
	return articulo;
}

regSecciones rellenarSecciones(char modificar, regSecciones secciones) {
	//pedir los datos por pantalla

	if (modificar == 'n') {
		printf("\nIngrese codigo secciones:");
		scanf("%d", &secciones.codigoSec);
	}

	fflush(stdin);
	printf("Ingrese la descripcion de la seccion:");
	fgets(secciones.descrpcionSec, sizeof(secciones.descrpcionSec), stdin);

	return secciones;
}

regIva rellenarIva(char modificar, regIva iva) {
	//pedir los datos por pantalla
	if (modificar == 'n') {
		printf("\nIngrese codigo iva:");
		scanf("%d", &iva.codigoIva);
	}

	fflush(stdin);
	printf("Ingrese la descripcion iva:");
	scanf("%d", &iva.descrpcionIva);

	return iva;
}

int generarCodigo(FILE *archivo, regPagos pagos) {

	fseek(archivo, 0, SEEK_END);
	int i = (ftell(archivo) / sizeof(pagos)) + 1;
	return i;

}

regPagos rellenarPagos(FILE *archivo, regPagos pagos) {

	pagos.codigoPago = generarCodigo(archivo, pagos);
	printf("codigo pago: %d\n", pagos.codigoPago);
	fflush(stdin);
	printf("Ingrese la descripcion de la forma de pago:");
	fgets(pagos.descrpcionPago, sizeof(pagos.descrpcionPago), stdin);

	return pagos;
}

/*cargar datos de 1 estructura dentro del archivo*/
void cargar(char titulo[]) {
	regClientes clientes;
	regArticulos articulos;
	regProveedores proveedores;
	regSecciones secciones;
	regIva iva;
	regPagos formPagos;

	FILE *archivo;
	archivo = fopen(titulo, "ab"); //abrir para aÃ±adir al archivo binario//strcat(titulo,".dat"); para concatenar los caracteres
	if (archivo == NULL) {
		exit(1);
	}
	if (strncmp(titulo, "Clientes", 2) == 0) {
		//pedir los datos por pantalla
		printf("\n");
		clientes = rellenarClientes('n', clientes);
		//pasar los datos al archivo
		fwrite(&clientes, sizeof(regClientes), 1, archivo);
	} else if (strncmp(titulo, "Proveedores", 2) == 0) {
		//pedir los datos por pantalla
		printf("\n");
		proveedores = rellenarProveedores('n', proveedores);
		fwrite(&proveedores, sizeof(regProveedores), 1, archivo);
	} else if (strncmp(titulo, "Articulos", 2) == 0) {
		//pedir los datos por pantalla
		printf("\n");
		articulos = rellenarArticulos('n', articulos);
		//pasar los datos al archivo
		fwrite(&articulos, sizeof(regArticulos), 1, archivo);
	} else if (strncmp(titulo, "Secciones", 2) == 0) {
		//pedir los datos por pantalla
		printf("\n");
		secciones = rellenarSecciones('n', secciones);
		//pasar los datos al archivo
		fwrite(&secciones, sizeof(regSecciones), 1, archivo);
	} else if (strncmp(titulo, "Iva", 2) == 0) {
		//pedir los datos por pantalla
		printf("\n");
		iva = rellenarIva('n', iva);
		//pasar los datos al archivo
		fwrite(&iva, sizeof(regIva), 1, archivo);
	} else if (strncmp(titulo, "F_Pagos", 2) == 0) {
		//pedir los datos por pantalla
		printf("\n");
		formPagos = rellenarPagos(archivo, formPagos);
		//pasar los datos al archivo
		fwrite(&formPagos, sizeof(regPagos), 1, archivo);
	} else {
		printf("mallll");
	}

	fclose(archivo);
	continuar();
}
void consulta(char titulo[]) {
	int cod, existe = 0;
	regClientes clientes;
	regArticulos articulos;
	regProveedores proveedores;
	regSecciones secciones;
	regIva iva;
	regPagos formPagos;

	FILE *archivo = fopen(titulo, "rb"); //lectura binaria

	if (archivo == NULL) {
		printf("No existe archivo\n");
		exit(1);
	}
	char ref[20];
	if (strncmp(titulo, "Articulos", 2) == 0) {
		printf("Ingrese el referencia %s a consultar:", titulo);
		scanf("%s", ref);
	} else {
		printf("Ingrese el codigo %s a consultar:", titulo);
		scanf("%i", &cod);
	}
	if (strncmp(titulo, "Clientes", 2) == 0) {

		fread(&clientes, sizeof(regClientes), 1, archivo); //leer la primera vez para comprobar los datos
		//mientras tenga datos el archivo ejecuta
		while (!feof(archivo)) {
			if (cod == clientes.codigoCli) {
				printf(
						"codigo: %i   DNI: %s   nombre: %s    direccion: %s    poblacion: %s    provincia: %s  CP: %s",
						clientes.codigoCli, clientes.dniCli, clientes.nombreCli,
						clientes.direccionCli, clientes.poblacionCli,
						clientes.provinciaCli, clientes.cpCli);
				existe = 1;
				break;
			}
			fread(&clientes, sizeof(regClientes), 1, archivo);
		}

	} else if (strncmp(titulo, "Proveedores", 2) == 0) {
		fread(&proveedores, sizeof(regProveedores), 1, archivo); //leer la primera vez para comprobar los datos
		//mientras tenga datos el archivo ejecuta
		while (!feof(archivo)) {
			if (cod == proveedores.codigoPro) {
				printf(
						"codigo: %i   DNI: %s   nombre: %s    direccion: %s    poblacion: %s    provincia: %s  CP: %s",
						proveedores.codigoPro, proveedores.dniPro,
						proveedores.nombrePro, proveedores.direccionPro,
						proveedores.poblacionPro, proveedores.provinciaPro,
						proveedores.cpPro);
				existe = 1;
				break;
			}
			fread(&proveedores, sizeof(regProveedores), 1, archivo);
		}
	} else if (strncmp(titulo, "Articulos", 2) == 0) {
		fread(&articulos, sizeof(regArticulos), 1, archivo); //leer la primera vez para comprobar los datos
		//mientras tenga datos el archivo ejecuta
		while (!feof(archivo)) {
			if (strcmp(ref, articulos.referenciaArt) == 0) {
				printf(
						"referencia: %s   descrpcion: %s   existencias: %d    precio: %d    stock minimo: %d    codigo: %d",
						articulos.referenciaArt, articulos.descrpcionArt,
						articulos.existencias, articulos.precio,
						articulos.stockMinimo, articulos.codigoSec);
				existe = 1;
				break;
			}
			fread(&articulos, sizeof(regArticulos), 1, archivo);
		}
	} else if (strncmp(titulo, "Secciones", 2) == 0) {
		fread(&secciones, sizeof(regSecciones), 1, archivo); //leer la primera vez para comprobar los datos
		//mientras tenga datos el archivo ejecuta
		while (!feof(archivo)) {
			if (cod == secciones.codigoSec) {
				printf("codigo: %i   descrpcion: %s", secciones.codigoSec,
						secciones.descrpcionSec);
				existe = 1;
				break;
			}
			fread(&secciones, sizeof(regSecciones), 1, archivo);
		}
	} else if (strncmp(titulo, "Iva", 2) == 0) {
		fread(&iva, sizeof(regIva), 1, archivo); //leer la primera vez para comprobar los datos
		//mientras tenga datos el archivo ejecuta
		while (!feof(archivo)) {
			if (cod == iva.codigoIva) {
				printf("codigo: %d   descrpcion: %d", iva.codigoIva,
						iva.descrpcionIva);
				existe = 1;
				break;
			}
			fread(&iva, sizeof(regIva), 1, archivo);
		}
	} else if (strncmp(titulo, "F_Pagos", 2) == 0) {
		//printf("Ingrese el codigo de forma de pago a consultar:");
		//scanf("%i", &cod);
		fread(&formPagos, sizeof(regPagos), 1, archivo); //leer la primera vez para comprobar los datos
		//mientras tenga datos el archivo ejecuta
		while (!feof(archivo)) {
			if (cod == formPagos.codigoPago) {
				printf("codigo: %i   descripcion: %s\n", formPagos.codigoPago,
						formPagos.descrpcionPago);
				existe = 1;
				break;
			}
			fread(&formPagos, sizeof(regPagos), 1, archivo);
		}

	}
	if (existe == 0) {
		printf("No existe el codigo\n");
	}
	fclose(archivo);
	continuar();
}
int modificacion(char titulo[]) {

	int cod;
	char respuesta = 'n', ref[20];

	regClientes clientes;
	regArticulos articulos;
	regProveedores proveedores;
	regSecciones secciones;
	regIva iva;
	regPagos formPagos;

	FILE *archivo = fopen(titulo, "r+b"); //lectura binaria

	if (archivo == NULL) {
		printf("No existe archivo\n");
		exit(1);
	}

	if (strncmp(titulo, "Articulos", 2) == 0) {
		printf("\nIngrese el referencia %s a consultar:", titulo);
		scanf("%s", ref);
	} else {
		printf("\nIngrese el codigo %s a consultar:", titulo);
		scanf("%i", &cod);
	}

	//clientes
	if (strncmp(titulo, "Clientes", 2) == 0) {
		fread(&clientes, sizeof(regClientes), 1, archivo);
		while (!feof(archivo)) {
			//si coincide el codigo indicado y el del archivo

			if (cod == clientes.codigoCli) {
				printf(
						"Estos son los datos antiguos-> codigo: %i   DNI: %s   nombre: %s    direccion: %s    poblacion: %s    provincia: %s  CP: %s",
						clientes.codigoCli, clientes.dniCli, clientes.nombreCli,
						clientes.direccionCli, clientes.poblacionCli,
						clientes.provinciaCli, clientes.cpCli);
				printf("\nEstas seguro de modificar los datos s/n? ");
				scanf("%s", &respuesta);
				fflush(stdin);
				//continuar();

				if (respuesta == 's') {
					//printf("modificar datos: %d", clientes.codigoCli);
					clientes = rellenarClientes(respuesta, clientes);

					int pos = ftell(archivo) - sizeof(regClientes);
					fseek(archivo, pos, SEEK_SET);
					fwrite(&clientes, sizeof(regClientes), 1, archivo);
					break;
				} else {
					continuar();
					fclose(archivo);
					return 0;
				}
			}

			fread(&clientes, sizeof(regClientes), 1, archivo);
		}

	}
	//articulos
	else if (strncmp(titulo, "Articulos", 2) == 0) {
		fread(&articulos, sizeof(regArticulos), 1, archivo);
		//si coincide el codigo indicado y el del archivo
		//cambiar a referencia que es un char []
		while (!feof(archivo)) {
			if (strcmp(ref, articulos.referenciaArt) == 0) {
				printf(
						"Estos son los datos antiguos-> referencia: %s   descrpcion: %s   existencias: %d    precio: %d    stock minimo: %d    codigo: %d",
						articulos.referenciaArt, articulos.descrpcionArt,
						articulos.existencias, articulos.precio,
						articulos.stockMinimo, articulos.codigoSec);
				printf("\nEstas seguro de modificar los datos s/n? ");
				scanf("%s", &respuesta);
				fflush(stdin);
				//continuar();

				if (respuesta == 's') {
					//printf("modificar datos: %s", articulos.referenciaArt);
					articulos = rellenarArticulos(respuesta, articulos);

					int pos = ftell(archivo) - sizeof(regArticulos);
					fseek(archivo, pos, SEEK_SET);
					fwrite(&articulos, sizeof(regArticulos), 1, archivo);

				} else {
					continuar();
					fclose(archivo);
					return 0;
				}
			}
		}

	}
	//proveedores
	else if (strncmp(titulo, "Proveedores", 2) == 0) {
		fread(&proveedores, sizeof(regProveedores), 1, archivo);
		while (!feof(archivo)) {
			//si coincide el codigo indicado y el del archivo
			if (cod == proveedores.codigoPro) {
				printf(
						"Estos son los datos antiguos-> codigo: %i   DNI: %s   nombre: %s    direccion: %s    poblacion: %s    provincia: %s  CP: %s",
						proveedores.codigoPro, proveedores.dniPro,
						proveedores.nombrePro, proveedores.direccionPro,
						proveedores.poblacionPro, proveedores.provinciaPro,
						proveedores.cpPro);
				printf("\nEstas seguro de modificar los datos s/n? ");
				scanf("%s", &respuesta);
				fflush(stdin);
				//continuar();

				if (respuesta == 's') {
					//printf("modificar datos: %d", proveedores.codigoPro);
					proveedores = rellenarProveedores(respuesta, proveedores);

					int pos = ftell(archivo) - sizeof(regProveedores);
					fseek(archivo, pos, SEEK_SET);
					fwrite(&proveedores, sizeof(regProveedores), 1, archivo);

				} else {
					continuar();
					fclose(archivo);
					return 0;
				}

			}

		}
	}

	//secciones
	else if (strncmp(titulo, "Secciones", 2) == 0) {
		fread(&secciones, sizeof(regSecciones), 1, archivo);
		while (!feof(archivo)) {
			//si coincide el codigo indicado y el del archivo
			if (cod == secciones.codigoSec) {
				printf(
						"Estos son los datos antiguos-> codigo: %i   descripcion: %s",
						secciones.codigoSec, secciones.descrpcionSec);

				printf("\nEstas seguro de modificar los datos s/n? ");
				scanf("%s", &respuesta);
				fflush(stdin);
				//continuar();

				if (respuesta == 's') {
					//printf("modificar datos: %d", secciones.codigoSec);
					secciones = rellenarSecciones(respuesta, secciones);

					int pos = ftell(archivo) - sizeof(regSecciones);
					fseek(archivo, pos, SEEK_SET);
					fwrite(&secciones, sizeof(regSecciones), 1, archivo);

				} else {
					continuar();
					fclose(archivo);
					return 0;
				}
			}
		}

	}

	//iva
	if (strncmp(titulo, "Iva", 2) == 0) {
		fread(&iva, sizeof(regIva), 1, archivo);
		while (!feof(archivo)) {
			//si coincide el codigo indicado y el del archivo
			if (cod == iva.codigoIva) {
				printf(
						"Estos son los datos antiguos-> codigo: %d   descripcion: %d",
						iva.codigoIva, iva.descrpcionIva);

				printf("\nEstas seguro de modificar los datos s/n? ");
				scanf("%s", &respuesta);
				fflush(stdin);
				//continuar();

				if (respuesta == 's') {
					//printf("modificar datos: %d", iva.codigoIva);
					iva = rellenarIva(respuesta, iva);

					int pos = ftell(archivo) - sizeof(regIva);
					fseek(archivo, pos, SEEK_SET);
					fwrite(&iva, sizeof(regIva), 1, archivo);

				} else {
					continuar();
					fclose(archivo);
					return 0;
				}
			}
		}

	}
	//forma de pago
	if (strncmp(titulo, "F_Pago", 2) == 0) {
		fread(&formPagos, sizeof(regPagos), 1, archivo);
		while (!feof(archivo)) {
			//si coincide el codigo indicado y el del archivo
			if (cod == formPagos.codigoPago) {
				printf(
						"Estos son los datos antiguos-> codigo: %i   descripcion: %s",
						formPagos.codigoPago, formPagos.descrpcionPago);

				printf("\nEstas seguro de modificar los datos s/n? ");
				scanf("%s", &respuesta);
				fflush(stdin);
				//continuar();

				if (respuesta == 's') {
					printf("modificar datos: %d", formPagos.codigoPago);
					printf("Ingrese nuevo descripcion:");
					scanf("%s", formPagos.descrpcionPago);

					int pos = ftell(archivo) - sizeof(regPagos);
					fseek(archivo, pos, SEEK_SET);
					fwrite(&formPagos, sizeof(regPagos), 1, archivo);

				} else {
					continuar();
					fclose(archivo);
					return 0;
				}
			}
		}
	}

	fclose(archivo);
	continuar();
	return 0;
}

//mostar una lista
void listado(char titulo[]) {
	regClientes clientes;
	regArticulos articulos;
	regProveedores proveedores;
	regSecciones secciones;
	regIva iva;
	regPagos formPagos;

	FILE *archivo = fopen(titulo, "rb"); //abrir el archivo en modo lectura binaria

	if (archivo == NULL) {
		exit(1);
	}

	if (strncmp(titulo, "Clientes", 2) == 0) {
		fread(&clientes, sizeof(regClientes), 1, archivo); //leo los datos
		printf("lista %s  \n codigo  dni  nombre direccion poblacion provincia  cp",titulo);
		printf("  \n-------------------------------------------------------------------------------------------------------------------\n");
		//mientras tenga datos el archivo ejecuta
		while (!feof(archivo)) {
			printf("\t%d\t%s\t%s\t%s\t%s\t%s\t%s\n", clientes.codigoCli,
					clientes.dniCli, clientes.nombreCli, clientes.direccionCli,
					clientes.poblacionCli, clientes.provinciaCli,
					clientes.cpCli);
			fread(&clientes, sizeof(regClientes), 1, archivo); //mientrar tenga datos sigue leyendo
		}
		printf("  \n-------------------------------------------------------------------------------------------------------------------\n");
	} else if (strncmp(titulo, "Proveedores", 2) == 0) {
		fread(&proveedores, sizeof(regProveedores), 1, archivo); //leo los datos
		printf("  \n-------------------------------------------------------------------------------------------------------------------\n");
		//mientras tenga datos el archivo ejecuta
		while (!feof(archivo)) {
			printf("\t%d\t%s\t%s\t%s\t%s\t%s\t%s\n", proveedores.codigoPro,
					proveedores.dniPro, proveedores.nombrePro,
					proveedores.direccionPro, proveedores.poblacionPro,
					proveedores.provinciaPro, proveedores.cpPro);
			fread(&proveedores, sizeof(regProveedores), 1, archivo); //mientrar tenga datos sigue leyendo
		}
		printf("  \n-------------------------------------------------------------------------------------------------------------------\n");
	} else if (strncmp(titulo, "Articulos", 2) == 0) {
		fread(&articulos, sizeof(regArticulos), 1, archivo); //leo los datos
		printf("  \n-----------------------------------\n");
		//mientras tenga datos el archivo ejecuta
		while (!feof(archivo)) {
			printf("\t%s\t%s\t%d\t%d\t%d\t%d\n", articulos.referenciaArt,
					articulos.descrpcionArt, articulos.existencias,
					articulos.precio, articulos.stockMinimo,
					articulos.codigoSec);
			fread(&articulos, sizeof(regArticulos), 1, archivo); //mientrar tenga datos sigue leyendo
		}
		printf("  \n-------------------------------------------------------------------------------------------------------------------\n");
	} else if (strncmp(titulo, "Secciones", 2) == 0) {
		fread(&secciones, sizeof(regSecciones), 1, archivo); //leo los datos
		printf("  \n-------------------------------------------------------------------------------------------------------------------\n");
		//mientras tenga datos el archivo ejecuta
		while (!feof(archivo)) {
			printf("\t%i\t%s\n", secciones.codigoSec, secciones.descrpcionSec);
			fread(&secciones, sizeof(regSecciones), 1, archivo); //mientrar tenga datos sigue leyendo
		}
		printf("  \n-------------------------------------------------------------------------------------------------------------------\n");
	} else if (strncmp(titulo, "Iva", 2) == 0) {
		fread(&iva, sizeof(regIva), 1, archivo); //leo los datos
		printf("  \n-----------------------------------\n");
		//mientras tenga datos el archivo ejecuta
		while (!feof(archivo)) {
			printf("   %i       %i       \n", iva.codigoIva, iva.descrpcionIva);
			fread(&iva, sizeof(regIva), 1, archivo); //mientrar tenga datos sigue leyendo
		}
		printf("  \n-------------------------------------------------------------------------------------------------------------------\n");
	} else if (strncmp(titulo, "F_Pagos", 2) == 0) {
		fread(&formPagos, sizeof(regPagos), 1, archivo); //leo los datos
		printf("  \n-------------------------------------------------------------------------------------------------------------------\n");
		//mientras tenga datos el archivo ejecuta
		while (!feof(archivo)) {
			printf("   %i       %s       \n", formPagos.codigoPago,
					formPagos.descrpcionPago);
			fread(&formPagos, sizeof(regPagos), 1, archivo); //mientrar tenga datos sigue leyendo
		}
		printf("  \n-------------------------------------------------------------------------------------------------------------------\n");
	} else {
		printf("mallll");
	}
	fclose(archivo);
	continuar();
}

//eliminar
// leer el archivo menos el que coincida con el codigo a eliminar usando un continue(), saltando ese registro
//escribiendo todos los registros buenos en un archivo temporal, borrar el original y cambiar el nombre al temporal

int elimina(char titulo[]) {

	regClientes clientes;
	regArticulos articulos;
	regProveedores proveedores;
	regSecciones secciones;
	regIva iva;
	regPagos formPagos;

	char ref[20];
	int cod;

	FILE *archivo, *temporal;
	archivo = fopen(titulo, "rb");
	temporal = fopen("temporal", "wb");

	if (strncmp(titulo, "Articulos", 2) == 0) {
		printf("Ingrese el referencia %s a consultar:", titulo);
		scanf("%s", ref);
	} else {
		printf("Ingrese el codigo %s a consultar:", titulo);
		scanf("%i", &cod);
	}
	if (strncmp(titulo, "Clientes", 2) == 0) {

		fread(&clientes, sizeof(regClientes), 1, archivo); //leer la primera vez para comprobar los datos
		//mientras tenga datos el archivo ejecuta
		while (!feof(archivo)) {
			//for(int i=0; i<=sizeof(regClientes);i++){
			if (cod != clientes.codigoCli) {
				fwrite(&clientes, sizeof(regClientes), 1, temporal);
			}
			fread(&clientes, sizeof(regClientes), 1, archivo);

		}
	} else if (strncmp(titulo, "Articulos", 2) == 0) {
		fread(&articulos, sizeof(regArticulos), 1, archivo); //leer la primera vez para comprobar los datos
		//mientras tenga datos el archivo ejecuta
		while (!feof(archivo)) {
			//for(int i=0; i<=sizeof(regClientes);i++){
			if (strcmp(ref, articulos.referenciaArt) == 0) {
				fwrite(&articulos, sizeof(regArticulos), 1, temporal);
			}
			fread(&articulos, sizeof(regArticulos), 1, archivo);
		}
	} else if (strncmp(titulo, "Proveedores", 2) == 0) {
		fread(&proveedores, sizeof(regProveedores), 1, archivo); //leer la primera vez para comprobar los datos
		//mientras tenga datos el archivo ejecuta
		while (!feof(archivo)) {
			//for(int i=0; i<=sizeof(regClientes);i++){
			if (cod != proveedores.codigoPro) {
				fwrite(&proveedores, sizeof(regProveedores), 1, temporal);
			}
			fread(&proveedores, sizeof(regProveedores), 1, archivo);

		}
	} else if (strncmp(titulo, "Secciones", 2) == 0) {
		fread(&secciones, sizeof(regSecciones), 1, archivo); //leer la primera vez para comprobar los datos
		//mientras tenga datos el archivo ejecuta
		while (!feof(archivo)) {
			//for(int i=0; i<=sizeof(regClientes);i++){
			if (cod != secciones.codigoSec) {
				fwrite(&secciones, sizeof(regSecciones), 1, temporal);
			}
			fread(&secciones, sizeof(regSecciones), 1, archivo);

		}
	} else if (strncmp(titulo, "Iva", 2) == 0) {
		fread(&iva, sizeof(regIva), 1, archivo); //leer la primera vez para comprobar los datos
		//mientras tenga datos el archivo ejecuta
		while (!feof(archivo)) {
			//for(int i=0; i<=sizeof(regClientes);i++){
			if (cod != iva.codigoIva) {
				fwrite(&iva, sizeof(regIva), 1, temporal);
			}
			fread(&iva, sizeof(regIva), 1, archivo);

		}
	} else if (strncmp(titulo, "F_Pagos", 2) == 0) {
		fread(&formPagos, sizeof(regPagos), 1, archivo); //leer la primera vez para comprobar los datos
		//mientras tenga datos el archivo ejecuta
		while (!feof(archivo)) {
			//for(int i=0; i<=sizeof(regClientes);i++){
			if (cod != formPagos.codigoPago) {
				fwrite(&formPagos, sizeof(regPagos), 1, temporal);
			}
			fread(&formPagos, sizeof(regPagos), 1, archivo);
		}
	}

	fclose(archivo);
	fclose(temporal);
	continuar();
	//remove(titulo);
	//continuar();
	remove(titulo);
	rename("temporal", titulo);
	continuar();
	return 0;
}
int menu2(char titulo[]) {
	int opcion;

	do {

		printf("\n1.  Crear / AÃ±adir registro %s", titulo);
		printf("\n2.  Modificar registro %s", titulo);
		printf("\n3.  Buscar un registro %s", titulo);
		printf("\n4.  Listar todos registro %s", titulo);
		printf("\n5.  Eliminar registro %s", titulo); //preguntar si esta seguro que desea eliminarlo
		printf("\n0. <-- Volver\n");
		printf("\n\tIngrese su opcion:  ");
		scanf("%d", &opcion);
		switch (opcion) {
		case 1:
			crear(titulo);
			cargar(titulo);
			break;
		case 2:
			modificacion(titulo);
			break;
		case 3:
			consulta(titulo);
			break;
		case 4:
			listado(titulo);
			break;
		case 5:
			elimina(titulo);
			break;
		case 6:

			break;
		}
	} while (opcion != 0);
	return 0;
}

int main() {
	int opcion;

	do {
		printf("1 - Menu Clientes");
		printf("\n2 - Menu Proveedores");
		printf("\n3 - Menu Articulos");
		printf("\n4 - Menu Secciones");
		printf("\n5 - Menu IVA");
		printf("\n6 - Menu Formas de Pago");
		printf("\n0 - SAlir\n");
		printf("\n\tIngrese su opcion:  ");
		scanf("%d", &opcion);

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
			menu2("F_Pago");
			break;
		}
	} while (opcion != 0);
	return 0;
}



