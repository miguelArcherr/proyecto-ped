//adrian
#include <iostream>
#include <fstream>
using namespace std;

//estructura Nodo palabra
struct palabra
{
	string nombre,
	significado,
	sinonimo,
	antonimo;
};

struct Palabra
{
	palabra pal;
	//Apunta a la siguiente palabra
	Palabra *sig;
};
//Diccionario
struct Diccionario
{
	Palabra *palabra;
};

//Prototipo sde funciones

char menu();

//Funciones de archivos
void concatenar(string &palabra);
void desconcatenar(string &palabra);

void abrirArchivo(Diccionario *&); //abre el archivo y lee las palabras
void guardarArchivo(Diccionario *);//guarda las palabras en el archivo

//Funciones de Lista "Diccionario"
palabra ingresarPalabra();
void registrarPalabra(Diccionario *&, palabra);
void mostrarPalabra(Diccionario *);
void eliminarPalabra(Diccionario *&);
void ordenarDiccionario(Diccionario *&);

int main(int argc, char *argv[])
{
	//Almacena las palabras del diccionario
	Diccionario *diccionario = new Diccionario();
	//Lee las palabras del diccionario
	abrirArchivo(diccionario);
	//Para las opciones
	char opcion; 
	
	//Bucle infinito 
	while(1)
	{
		system("color b");
		//Despliega menu y recibe la tecla presionada por el usuario
		opcion = menu();
		//Limpia la consola
		system("cls");
		//Opciones validas
		switch(opcion)
		{
			//Agrega una palabra en el diccionario
			case '1': 
			    //registra una palabnra en el diccionario
			    registrarPalabra(diccionario, ingresarPalabra()); 
			    //ordena el diccionario
		        ordenarDiccionario(diccionario);
		    break;
		    //Elimina una palabra del diccionario
			case '2': 
			    eliminarPalabra(diccionario);
			break;
			//Busca una palabra
			case '3': 
			    mostrarPalabra(diccionario);
			break;
			//Guarda las palabras del diccionario y sale del programa
			case '4':
				guardarArchivo(diccionario);
				return 1;
			break;
			   
			default: cout << "\n\n\t\tOpcion Invalida!!!\n\n" << endl;
		}
		system("pause");
		system("cls");
	}
	
	return 0;
}

//michael josue
char menu()
{
	char opc;
	
	cout << "\n\n\t\tBienvenidos A Nuestro Diccionario  \n\n\n"
	        "\t1. Agregar  Palabra \n\n"
	        "\t2. Eliminar Palabra \n\n"
	        "\t3. Buscar   Palabra \n\n"
			"\t4. Salir ";
	cin>>opc;
	    
	return opc;
}

//miguel
void abrirArchivo(Diccionario *&dicc) //abre el archivo y lee las palabras
{
	//abre el archivo para leer su contenido
	ifstream archivo("Diccionario.txt", ios::in);
	
	if(!archivo.is_open()) //si archivo no existe
		return;
	    
	//Para almacenar las palabra
	palabra palabr;
	
	//leemos el nombre
	archivo >> palabr.nombre;
	//mientras no es el final del archivo
	while(!archivo.eof())
	{
		//Leee los datos de la palabra
		archivo >> palabr.significado;
		archivo >> palabr.sinonimo;
		archivo >> palabr.antonimo;
		
		desconcatenar(palabr.nombre);
		desconcatenar(palabr.significado);
		desconcatenar(palabr.sinonimo);
		desconcatenar(palabr.antonimo);
		
		//Almacena la palabra en el diccionario (lista)
		registrarPalabra(dicc, palabr);
		
		archivo >> palabr.nombre;
	}
	//Cierra el archivo
	archivo.close();
}

void guardarArchivo(Diccionario *dicc) //guarda las palabras en el archivo
{
	//Guardar las palabras del diccionario en un archivo .txt
	ofstream archivo("Diccionario.txt", ios::out); 
	//Variable aux para no eliminar los datos
	Palabra *actual = dicc->palabra;
	
	system("color a");
	cout << "\n\n\t\tDiccionario Guardando!! \n\n";
	
	while(actual != NULL)
	{
		//quita los espacio y les agrega un _
	    concatenar(actual->pal.nombre);
		concatenar(actual->pal.significado);
		concatenar(actual->pal.sinonimo);
		concatenar(actual->pal.antonimo);	
		     
		//GUarda  la palabra en el diccionario
		archivo << actual->pal.nombre << " " << actual->pal.significado << " " 
		        << actual->pal.sinonimo << " " << actual->pal.antonimo << "\n";       
		//siguiente nodo
		actual = actual->sig;
	}
	//Cerramos el archivo
	archivo.close();
}

//adrian
void concatenar(string &palabra)
{
	//para conctenar la nueva palabra
	string aux;
	//toma la longitud de la palabra enviada y recorre el arreglo
	for(int i=0; i<palabra.length(); i++)
	    if(palabra[i] != ' ')
	        aux += palabra[i];
	    else
	        aux += '_';
	//asignamos la nueva palabra
	palabra = aux;
}

void desconcatenar(string &palabra)

{
	//para concatenar la nueva palabra
	string aux;
	//toma la longitud de la palabra enviada y recorre el arreglo
	for(int i=0; i<palabra.length(); i++)
	    if(palabra[i] != '_')
	        aux += palabra[i];
	    else
	        aux += ' ';
	//asignamos la nueva palabra
	palabra = aux;

}

//miguel
palabra ingresarPalabra()
{
	//Ingresa los datos de la palabra
	palabra nueva;
	
	fflush(stdin);
	
	cout << "Palabra: ";
	getline(cin, nueva.nombre);
	
	cout << "Significado: ";
	getline(cin, nueva.significado);
	
	cout << "Sinonimo: ";
	getline(cin, nueva.sinonimo);
	
	cout << "Antonimo: ";
	getline(cin, nueva.antonimo);
	
	return nueva;
}

void registrarPalabra(Diccionario *&dicc, palabra palabr)
{
	//Nueva palabra (nodo)
	Palabra *nueva = new Palabra();
	//Asiganmos la nueva palabra 
	nueva->pal = palabr;
    //sigueinte nodo es nulo
	nueva->sig = NULL;
	
	//Si el diccionario no esta vacio
	if(dicc->palabra != NULL)
	{
		//Para recorrer la lista sin eliminar los nodos
		Palabra *actual = dicc->palabra;
		//recorre la lista hasta llegar al final        
		while(actual->sig != NULL)
		    //Recorre el nodo actual con el siguiente
			actual = actual->sig;
		//Si no la agrega al ultimo
		actual->sig = nueva;
	}
	//Si esta vacio    
	else
	    //Si el diccionario esta vacio
		dicc->palabra = nueva;
	    
}

//adrian
void mostrarPalabra(Diccionario *dicc)
{	
    //Si el diccionario no esta vacio
	if(dicc->palabra != NULL)
	{
		//Para rtecorrer el nodo sin eliminar los nodos
	    Palabra *actual = dicc->palabra;
	    //Para la palabra que deseamos buscar
	    string buscar; 
	    //Palabra a buscar
	    cout << "\n\n\t\t Buscar Palabra en el diccionario \n\n"
		        "\tBuscar: ";
	    cin >> buscar;
	    //Hasta que el siguiente nodo sea nulo
	    while(actual != NULL)
	    {
	    	//Si encontramos la palabra
	        if(buscar == actual->pal.nombre)
	        {
	        	system("color a");
	        	//Mostramos la palabra y sus datos
		        cout <<"\n\n\t\tPalabra: "<<actual->pal.nombre << "\n\n\n\tSignificado: " << actual->pal.significado << "\n\n\tSinonimo: " 
		        << actual->pal.sinonimo << "\n\n\tAntonimo: " << actual->pal.antonimo << "\n\n";           
		        return; //terminamos el proceso de la funcion
	        }
	        //Recorre del nodo actual al siguiente
	        actual = actual->sig;
    	}   
    	//Si no
    	system("color c");
    	cout << "\n\n\t\tNo se encontro la palabra!!!\n\n" ;	
    	return;
	}
	//Si no
	system("color c");
	cout << "\n\n\t\tDiccionario esta vacio!!!\n\n";
}

//michael josue
void eliminarPalabra(Diccionario *&dicc)
{
	//Para no perder los nodos del diccionario
    Palabra *actual = dicc->palabra,
    //almacenar el anterior nodo
	*anterior = NULL;
	//Para eliminar la palabra
    string palabra;
    
    cout << "\n\n\t\tPalabra a Eliminar\n\n"
         << "\tEliminar: ";
    getline(cin, palabra);
	getline(cin, palabra);
    
    if(dicc->palabra != NULL)
    {
        while(actual != NULL)
        {
        	//Si encuentra la palabra
            if(actual->pal.nombre == palabra)
            {
            	system("color a");
            	cout << "\n\n\t\tPalabra " << actual->pal.nombre << " Fue eliminada!!!\n\n";
                if(actual == dicc->palabra)
                    dicc->palabra = dicc->palabra->sig;
                else
                    anterior = actual->sig;
                //Eliminamos el actual 
                delete(actual);
                return;
            }
            //Asignamos el actual al anterior
            anterior = actual;
            //Pasamos al siguiente nodo
            actual = actual->sig;
        }
        system("color c");
        cout << "\n\n\t\tNo se encontro la palabra\n\n";
        return;
    }
    else
        system("color c");
        cout<<"\n\n\t\tLista vacia!!!\n\n";
}
void ordenarDiccionario(Diccionario *&dicc)
{
    Palabra *actual = dicc->palabra;
	Palabra *anterior = NULL;
	palabra aux;
	
	while(actual->sig != NULL)
	{
		anterior = actual->sig;
		
		while(anterior != NULL)
		{
			if(actual->pal.nombre[0] > anterior->pal.nombre[0])
			{
				aux = anterior->pal;
				anterior->pal = actual->pal;
				actual->pal = aux;
			}
			
			anterior = anterior->sig;
		}
		
		actual = actual->sig;
	}
}