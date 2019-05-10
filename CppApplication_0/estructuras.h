/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   estructuras.h
 * Author: mañana
 *
 * Created on 9 de mayo de 2019, 9:11
 */

#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#ifdef __cplusplus
extern "C" {
#endif

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
	scanf("%s", proveedores.dniPro);
	printf("Ingrese el nombre Proveedores:");
	scanf("%s", proveedores.nombrePro);
	printf("Ingrese la direccion del Proveedores:");
	scanf("%s", proveedores.direccionPro);
	printf("Ingrese la poblacion del Proveedores:");
	scanf("%s", proveedores.poblacionPro);
	printf("Ingrese la provincia del Proveedores:");
	scanf("%s", proveedores.provinciaPro);
	printf("Ingrese CP:");
	scanf("%s", proveedores.cpPro);
	return proveedores;
}

regArticulos rellenarArticulos(char modificar, regArticulos articulo) {
	//pedir los datos por pantalla
	if (modificar == 'n') {
		printf("\nIngrese la referencia del articulo:");
		scanf("%s", articulo.referenciaArt);
	}

	fflush(stdin);
	printf("Ingrese la descripcion del articulo:");
	scanf("%s", articulo.descrpcionArt);
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
	scanf("%s", secciones.descrpcionSec);

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
	scanf("%d", pagos.descrpcionPago);

	return pagos;
}



#ifdef __cplusplus
}
#endif

#endif /* ESTRUCTURAS_H */

