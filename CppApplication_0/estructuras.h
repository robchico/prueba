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


#ifdef __cplusplus
}
#endif

#endif /* ESTRUCTURAS_H */

