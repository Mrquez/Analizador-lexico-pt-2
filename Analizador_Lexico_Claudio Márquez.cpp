#include <iostream>

#include <string.h>

using namespace std;
class Compilador{
	public:
		void leer();
		string palabra();
		bool reservada(string);
		Compilador();
		string Tabla[25];
		void imprimir (string);
	private:
	int i;
	string Arch;
};

Compilador::Compilador()
{
	i=0;
	Tabla[0]="@ENT";
	Tabla[1]="@CAD";
	Tabla[2]="@DEC";
	Tabla[3]="@IF";
	Tabla[4]="@FOR";
	Tabla[5]="@ELSE";

	
	
	
}

void Compilador::leer()
{
	FILE *Archivo;						//se declara la palabra archivo
	Archivo=fopen("Pruebas.txt","r");   //se abre el archivo en modo lectura
	if (Archivo == NULL)				//en caso del que el,archivo se encuentre vac?o o no exista 
	{
		cout<<"Archivo inexistente o vacío"<<endl;
		exit(0);						//termina el programa
	}
	else
	{
		while (!feof(Archivo))			//mientras que la linea no haya terminado 
		{
			Arch+=fgetc(Archivo);		//obtiene caracter por caracter y los guaeda en Arch
		}
		fclose(Archivo);				//cierro el archivo
	}
}
string Compilador::palabra()
{
	string Cadena="";
	int X;
	X=(int) Arch[i];
	//Palabras reservadas #minusculas 
	
	if (X==35)
	{
		
		Cadena+=Arch[i];
		i++;
		X=(int) Arch[i];
		while (X>96&&X<123)
		{
			Cadena+=Arch[i];
			i++;
			X=(int) Arch[i];
		}
	}//Identificadores @MAYUSCULAS
	else if (X==64)
	{
		
		Cadena+=Arch[i];
		i++;
		X=(int) Arch[i];
		while (X>64&&X<91)
		{
			Cadena+=Arch[i];
			i++;
			X=(int) Arch[i];
		}
		int y=0,z=0;
		while(z<6){
			if(Cadena==Tabla[z]){
				y++;
			}
			z++;
		}
		if(y==0){
			cout<<"La cadena " <<Cadena<<" no es una palabra reservada"<<endl;
			Cadena="";
		}
	}//Formar n?meros [0-9]+(/.[0-9]+)*
	else if (X>47&&X<58)
	{
		Cadena+=Arch[i];
		i++;
		X=(int) Arch[i];
		while ((X>45)&&(X<=57))
		{
			Cadena+=Arch[i];
			i++;
			X=(int) Arch[i];
		}
			
	}
	else if ((X==61))
	{
		Cadena+=Arch[i];
		i++;
		X=(int) Arch[i];
		if ((X==60)||(X==61)||(X==62)||(X==33))
		{
			Cadena+=Arch[i];
			i++;
		}
	}
	else if((X==59)||(X==60)||(X==62)||(X==39)||(X==40)||(X==41)){
		Cadena+=Arch[i];
		i++;
		X=(int) Arch[i];
	}
	else if((X==123)||(X==125)||(X==43)||(X==47)){
		Cadena+=Arch[i];
		i++;
		X=(int) Arch[i];
	}
	else{
	//cout<<X<<" ";
	
	i++;
	return palabra();
	}
	cout<<Cadena<<endl<<endl;
	return Cadena;
	
	
	
}
void Compilador::imprimir( string word){
	//cout<<word;
}




int main()
{
	
	Compilador Obj1;
	string word;
	Obj1.leer();
	Obj1.palabra();
	Obj1.palabra();
	Obj1.palabra();
	Obj1.palabra();
	Obj1.palabra();
	Obj1.palabra();
	Obj1.palabra();
	Obj1.palabra();
	Obj1.palabra();
	Obj1.palabra();
	Obj1.palabra();
	Obj1.palabra();


}
