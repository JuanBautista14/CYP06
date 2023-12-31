/*****************************************************************************************************************
	UNIVERSIDAD NACIONAL AUTONOMA DE MEXICO
	FACULTAD DE ESTUDIOS SUPERIORES -ARAGON-

	Computadoras y programacion. 
	Programado por: Butista Solis Juan Pedro 
	Numero de Cuenta: 321333351
	
	Quiso decir: Programa principal de la aplicacion de la distancia de Levenstein.
	
******************************************************************************************************************/


#include "stdafx.h"
#include <string.h>
#include <stdio.h>
#include "corrector.h"
#include <ctype.h>
#define DEPURAR 1

//Funciones publicas del proyecto
/*****************************************************************************************************************
	DICCIONARIO: Esta funcion crea el diccionario completo
	char *	szNombre				:	Nombre del archivo de donde se sacaran las palabras del diccionario	
	char	szPalabras[][TAMTOKEN]	:	Arreglo con las palabras completas del diccionario
	int		iEstadisticas[]			:	Arreglo con el numero de veces que aparecen las palabras en el diccionario
	int &	iNumElementos			:	Numero de elementos en el diccionario
******************************************************************************************************************/

void	Diccionario			(char *szNombre, char szPalabras[][TAMTOKEN], int iEstadisticas[], int &iNumElementos)
{
	FILE* fpDicc;
	char linea[4000];
	char palabraDetectada[TAMTOKEN];
	char aux[TAMTOKEN];
	int i;
	int indicePD;
	int pas, comp;
	iNumElementos = 0;
	// abrir el achivo
	if (DEPURAR == 1)
		printf("%s", szNombre);

	fopen_s(&fpDicc, szNombre, "r");
	if (fpDicc != NULL)
	{

		if (DEPURAR == 1)
			printf("\nSi lo pude abrir");

		indicePD = 0;
		while (!feof(fpDicc))
		{
			fgets(linea, sizeof(linea), fpDicc);
			if (DEPURAR == 1)
				
			for (i = 0; i < strlen(linea); i++)
			{

				// Detectar una palabra
				if ((linea[i] == ' ' || linea[i] == '.' || linea[i] == '\t' || linea[i] == '\n') && (linea[i + 1] != ' ' && linea[i + 1] != '\t' && linea[i + 1] != '\n' && linea[i] != ' - '))
				{

					palabraDetectada[indicePD] = '\0';

					strcpy_s(szPalabras[iNumElementos], TAMTOKEN, palabraDetectada);
					iEstadisticas[iNumElementos] = 1;
					if (DEPURAR == 1)
						//printf("\np: %s", palabraDetectada);
						indicePD = 0;
					iNumElementos++;

					// eliminar los espacios en blanco
					// tabuladores y saltos de linea consecutivos				
				}
				else if (linea[i] != '\n')
				{
					if (linea[i] != '(' && linea[i] != ')' && linea[i] != ',' && linea[i] != '.' && linea[i] != ';' && linea[i] != ':' && linea[i] != ' ' && linea[i] != '\'' && linea[i] != '-' && linea[i + 1] != '-' && linea[i + 1] != '\'' && linea[i] != '-' && linea[i] != '&')
					{
						palabraDetectada[indicePD] = tolower(linea[i]);
						indicePD++;
					}
				}
			}
			if (DEPURAR == 1)
				printf("\nNumPalabras: %i\n", iNumElementos);

			// burbujazo

		}

		fclose(fpDicc);
		for (i = 0; i < iNumElementos - 1; i++) {
			for (int j = i + 1; j < iNumElementos;) {
				if (strcmp(szPalabras[i], szPalabras[j]) == 0) {
					iEstadisticas[i] = iEstadisticas[i] + 1;
					// Eliminar elemento duplicado
					for (int k = j; k < iNumElementos - 1; k++) {
						strcpy_s(szPalabras[k], TAMTOKEN, szPalabras[k + 1]);

					}
					(iNumElementos)--;

				}
				else {
					j++;
				}
			}
		}
		// burbujazo
		for (pas = 0;pas < iNumElementos - 1;pas++) {
			for (comp = 0;comp < iNumElementos - 1;comp++) {
				if (strcmp(szPalabras[comp], szPalabras[comp + 1]) > 0) {

					strcpy_s(aux, TAMTOKEN, szPalabras[comp]);
					strcpy_s(szPalabras[comp], TAMTOKEN, szPalabras[comp + 1]);
					strcpy_s(szPalabras[comp + 1], TAMTOKEN, aux);

				}
			}
		}
	}

	else
	{
		if (DEPURAR == 1)
			printf("\nNo lo pude abrir");
	}
}

/*****************************************************************************************************************
	ListaCandidatas: Esta funcion recupera desde el diccionario las palabras validas y su peso
	Regresa las palabras ordenadas por su peso
	char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
	int		iNumSugeridas,						//Lista de palabras clonadas
	char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
	int		iEstadisticas[],					//Lista de las frecuencias de las palabras
	int		iNumElementos,						//Numero de elementos en el diccionario
	char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
	int		iPeso[],							//Peso de las palabras en la lista final
	int &	iNumLista)							//Numero de elementos en la szListaFinal
******************************************************************************************************************/
void	ListaCandidatas		(
	char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
	int		iNumSugeridas,						//Lista de palabras clonadas
	char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
	int		iEstadisticas[],					//Lista de las frecuencias de las palabras
	int		iNumElementos,						//Numero de elementos en el diccionario
	char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
	int		iPeso[],							//Peso de las palabras en la lista final
	int &	iNumLista)							//Numero de elementos en la szListaFinal
{

	//Sustituya estas lineas por su c�digo
	strcpy_s(szListaFinal[0],TAMTOKEN, szPalabrasSugeridas[ 0] ); //la palabra candidata
	iPeso[0] = iEstadisticas[0];			// el peso de la palabra candidata
	
	iNumLista = 1;							//Una sola palabra candidata
}

/*****************************************************************************************************************
	ClonaPalabras: toma una palabra y obtiene todas las combinaciones y permutaciones requeridas por el metodo
	char *	szPalabraLeida,						// Palabra a clonar
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int &	iNumSugeridas)						//Numero de elementos en la lista
******************************************************************************************************************/
void	ClonaPalabras(
	char *	szPalabraLeida,	char szPalabrasSugeridas[][TAMTOKEN], int &	iNumSugeridas)		
{
	const char* abc = "abcdefghijklmnopqrstuvwxyz�����";
	char sugerencia[70000][TAMTOKEN];
	int longi;
	int contapa = 0;
	//variables contadores
	int i;
	strcpy_s(sugerencia[0], TAMTOKEN, szPalabraLeida);
	longi = strlen(szPalabraLeida);

	//ELIMINACION  DE CARACTERES
	for (i = 0; i < longi; i++)
	{
		// Copiar la palabra original
		strcpy_s(szPalabraLeida, TAMTOKEN - 1, sugerencia[0]);

		// Eliminar i caracteres (la posici�n actual)
		strcpy_s(szPalabraLeida + i, TAMTOKEN - 1, szPalabraLeida + i + 1);

		// Almacenar la palabra modificada en el arreglo de palabras sugeridas
		strcpy_s(sugerencia[i + 1], TAMTOKEN, szPalabraLeida);
		contapa++;

	}
	// Transponer pares de caracteres y almacenar las nuevas sugerencias
	for (i = 0; i <= longi - 1; i++) {
		// Copiar la palabra original
		strcpy_s(szPalabraLeida, TAMTOKEN, sugerencia[0]);

		// Intercambiar caracteres en posici�n i e i+1 sin usar void swap
		szPalabraLeida[i] ^= szPalabraLeida[i + 1];
		szPalabraLeida[i + 1] ^= szPalabraLeida[i];
		szPalabraLeida[i] ^= szPalabraLeida[i + 1];

		// Almacenar la palabra modificada en el arreglo de palabras sugeridas
		strcpy_s(sugerencia[longi + i + 1], TAMTOKEN, szPalabraLeida);
		contapa++;
	}
	//Sustitucion de palabras por alfabeto
	for (int letra = 'a'; letra <= 'z'; letra++)
	{
		// Copiar la palabra original
		strcpy_s(szPalabraLeida, TAMTOKEN, sugerencia[0]);

		// Reemplazar cada letra por la letra actual del abecedario
		for (i = 0; i < longi; i++)
		{
			strcpy_s(szPalabraLeida, TAMTOKEN, sugerencia[0]);
			szPalabraLeida[i] = letra;
			strcpy_s(sugerencia[contapa], TAMTOKEN, szPalabraLeida);
			contapa++;
		}
	}
	for (iNumSugeridas = 0;iNumSugeridas < contapa;iNumSugeridas++) {
		strcpy_s(szPalabrasSugeridas[iNumSugeridas], TAMTOKEN, sugerencia[iNumSugeridas]);
	}

}