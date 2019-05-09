#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <string.h>

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

