// ProyectoFinal.cpp : Codigo Principal Proyecto Programacion
//

#include <iostream>

using namespace std;

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char nom[25];
    int edad;
    char tel[15];
    char dir[35];
}Amigo;

/*Funciones de Archivo*/
void Crear(void);
void Listar(void);
void AgregarDemandante(void);
void Modificar(void);
void Borrar(void);
void Encontrar(void);

/*Nombre del Archivo a guardar*/
char nombre_fichero[] = "agenda.dat";

FILE *abrir_fichero_b(char cadena[], int metodo);

int main()
{
    FILE *fp;
    int opc, opcionf;
    char cad[3];
   
    fp = abrir_fichero_b(nombre_fichero,0);
    if( fp )
    {
        fclose(fp);
    }
    else
    {
        cout << "Error (NO ABIERTO)\n" <<endl;
        cout <<"Presiona cualquier tecla para continuar.... y Crear el Archivo"<<endl;
        fp = abrir_fichero_b(nombre_fichero,1);
        fclose(fp);
        getch();    }
   
    do{
    system("cls");
        cout << "1. Crear Archivo (Cuidado, elimina lo que ya se tiene en el Archivo)"<<endl;
        cout << "2. Agregar\n3. Eliminar\n4. Listar\n5. Buscar\n6. Modificar\n7. Salir";
        cout << "?Introduce tu opcion y depues enter.";
       
        opc = atoi(gets(cad));
        while(opc<0 || opc>7) /*Limitando la entrada de las opciones*/   
            opc = atoi(gets(cad));
        system("cls");   
        switch(opc)
        {
        case 1:
                Crear(); 
                break;
        case 2:  
				
					AgregarDemandante();//Decidir si es demandante o empleador
				
					
                break;
        case 3:
                Borrar();
                break;
        case 4:
                Listar();
                break;
        case 5:
                Encontrar();
                break;
        case 6:
                 Modificar();
                break;
           
        }
       
        /*Solo parar cuando sea una de las opciones*/
        if(opc<7)
        {
            cout << "\n\nPresiona Cualquier Tecla para Regresar al Menu"<<endl;
            getch();
        }
    }
    while(opc!=7);
   
}



// FUNCION PARA CREAR UN ARCHIVO
/*****************************************************************
Funcion que sirve para borrar todo el Contenido del Archivo Binario*/
void Crear(void){
   FILE *fp;

   fp = abrir_fichero_b(nombre_fichero,0);
   if(fp)
   {
       cout <<"\n Archivo agenda.dat YA EXISTE\n"<<endl;
        fclose(fp); 
   }
   else if(!fp){
   	cout <<"\n Archivo agenda.dat CREADO\n";
	}
}


/********************************************************
Funcion que sirve para imprimir todos los  un registros del Archivo Binario*/
void Listar(void){
   FILE *fp;
   int i=1;
   Amigo aux;
    fp = abrir_fichero_b(nombre_fichero,0);
   if(!(fp))
       cout <<"\n Error de apuertura del archivo agenda.dat\n";
   else{
      cout<<"\n U S U A R I O S  E N  L A  A G E N D A\n";
      cout <<"---------------------------------------------------------------\n";
      while ((fread(&aux, sizeof(aux), 1, fp))!=0){
        cout <<"=> Datos del Amigo "<<i<<"\n";
        cout <<"Nombre: "<<aux.nom<< "| Edad: "<<aux.edad<<" | Telefono: "<<aux.tel<<"\n";
        cout <<"Direccion: "<<aux.dir <<"\n";
        i++;
      }
      cout <<"---------------------------------------------------------------\n";
      fclose(fp);
   }
}

/********************************************************
Funcion que sirve para agregar un registro dentro del Archivo Binario*/
void AgregarDemandante(void){
   FILE *fp;
   Amigo aux;
   char cad[3];

   cout <<"\n Agregando un Amigo Nuevo al archivo binario agenda.dat\n";
   fp=abrir_fichero_b(nombre_fichero,2);
   if(!(fp))
        cout <<"\n Error de apuertura del archivo agenda.dat\n";
   else{
        /*Introduciendo los Datos del Amigo*/
        cout <<"Dame el nombre del Amigo: "<<endl;
        cin >> aux.nom;
        cout <<"Dame la Edad del Amigo: "<<endl;
        aux.edad=atoi(gets(cad));
        cout <<"Dame el telefono del Amigo: "<<endl;
        cin >> aux.tel;
        printf("Dame la direccion del Amigo: ");
        cin >> aux.dir;

        fwrite(&aux, sizeof(aux), 1, fp);
        fclose(fp);
   }
}


/********************************************************
Funcion que sirve para Modificar un registro dentro del Archivo Binario*/
void Modificar(void){
   FILE *fp;
   Amigo    aux;
   int n;
   char cadena[25],cad[2];
    fp=abrir_fichero_b(nombre_fichero,3);
   if(!(fp))
       cout <<"\n Error de apuertura del archivo agenda.dat\n";
   else{
        cout <<"Como se llama al amigo que quieres Modificar: "<<endl;
        cin >> cadena;
       
        /*Buscando el Amigo dentro del Archivo*/
      while ((n=fread(&aux, sizeof(aux), 1, fp))!=0 && stricmp(aux.nom,cadena)!=0);
      if (n==0)
         cout <<"No existe el usuario llamado: "<<cadena<<endl;
      else{
         cout <<"\n Amigo encontrado....!!!\n"<<endl;
         cout <<"Nombre: "<<aux.nom<<endl;
         cout <<"Edad: "<<aux.edad<<endl;
         cout <<"Telefono: "<<aux.tel<<endl;
         cout <<"Direccion: "<<aux.dir<<endl;
       
         cout <<"\n CAMBIANDO VALORES \n";
       
        cout <<"Dame el nombre nuevo del Amigo: "<<endl;
        gets(aux.nom);
        cout <<"Dame la nueva Edad del Amigo: "<<endl;
        aux.edad=atoi(gets(cad));
        cout <<"Dame el nuevo telefono del Amigo: "<<endl;
        gets(aux.tel);
        cout <<"Dame la nueva direccion del Amigo: "<<endl;
        gets(aux.dir);
        
       

         printf("\n GRABANDO Y CERRANDO ARCHIVO \n");
         fseek(fp,-1*sizeof(aux),SEEK_CUR);
         fwrite(&aux, sizeof(aux), 1, fp);
      }
      fclose(fp);   //Cerramos el archivo
   }
}

/********************************************************
Funcion que sirve para borrar un registro dentro del Archivo Binario*/
void Borrar(void){
   FILE *fp,*fd;
   Amigo    aux;
   int encontrado=0;
    char cadena[25];
  
   printf("Introduce el nombre del Amigo a borrar: ");
   gets(cadena);
  
   printf("\n BORRANDO REGISTROS  \n");
   fp=abrir_fichero_b(nombre_fichero,0);
   if(!(fp))
       printf("\n Error de apuertura del archivo agenda.dat\n");
   else{
        fd=abrir_fichero_b("paso.$$$",1);
      if(!(fd))
         printf("\n Error Imposible crear archivo auxiliar\n");
      else{
         while ((fread(&aux, sizeof(aux), 1, fp))!=0)
            if(stricmp(aux.nom,cadena)!=0)
              fwrite(&aux, sizeof(aux), 1, fd);
            else
              encontrado=1;
         fclose(fd);
      }
      fclose(fp);
      if(encontrado){
         system("del agenda.dat");
         system("ren paso.$$$ agenda.dat");
         printf("\n Registro BORRADO con Exito!!!\n");
      }
      else{
         system("del paso.$$$");
         printf("\n El Registro NO SE ENCONTRO, no fue borrado!!!");
      }
   }
}

/******************************************
Funcion para Encontrar un Amigo e imprimir sus datos*/
void Encontrar(void){
    FILE *fp;
    Amigo    aux;
    int n;
    char cadena[25];

    printf("Introduce el nomrbre del Amigo que buscas: ");
    gets(cadena);

    printf("\n Buscando a un Amigo  \n");
    fp=abrir_fichero_b(nombre_fichero,0);
    if(!(fp))
        printf("\n Error de apuertura del archivo agenda.dat\n");
    else{
        while ((n=fread(&aux, sizeof(aux), 1, fp))!=0 && stricmp(aux.nom,cadena)!=0);
      if (n==0)
         printf("No existe el cuate llamado: %s ",cadena);
      else{
         printf("\n Amigo encontrado....!!!\n");
         printf("Nombre: %s | Edad: %d | Telefono: %s\n",aux.nom,aux.edad,aux.tel);
         printf("Direccion: %s\n",aux.dir);
       
        /* getch();*/
       
        }
    }


}

/*************************************************
Funcion que Carga el Archivo y regresa un apuntador con que se va ha manejar el Archivo
Recibe:     El nombre del Archivo , Y el método con que se va abrir el Archivo
        Un Apuntador tipo Archivo, 0 - Solo Lectura , 1 - Para crearlo de nuevo desde cero,
        2 - Anhadir Informacion, 3 - para Lectura y Escritura.       
 Regresa:    El apuntador de Tipo FILE, con el cual se abrio*/
FILE *abrir_fichero_b(char cadena[], int metodo){
    FILE *x;
    switch(metodo){
        case 0:
            x = fopen(cadena,"rb");
            break;
        case 1:
            x = fopen(cadena,"wb");
            break;
        case 2:
            x = fopen(cadena,"ab");
            break;
        case 3:
            x = fopen(cadena,"r+b");
            break;
    }
    return x;
} //En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
