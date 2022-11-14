#include <iostream>
#include <string.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

using namespace std; 

class Analizador
{
	public: 
		void LeerArchivo();
		string Token();
		string Tabla[37];
		void Error (int, string);
		bool ValidarTabla(string);
		bool EsIdent(string);
		bool EsNum(string);
		Analizador();
	private:
		int i;		
		string Arch;
};

Analizador::Analizador()
{
	i=0;
	Tabla[0]="CONTS";
	Tabla[1]="VAR";
	Tabla[2]="PROC";
	Tabla[3]="ENT";
	Tabla[4]="DEC";
	Tabla[5]="CAD";
	Tabla[6]="CAR";
	Tabla[7]="LLAMAR";
	Tabla[8]="LEER";
	Tabla[9]="ESCRIBIR";
	Tabla[10]="INICIO";
	Tabla[11]="FIN";
	Tabla[12]="SI";
	Tabla[13]="ENTONCES";
	Tabla[14]="CAMBIAR";
	Tabla[15]="CASO";
	Tabla[16]="MIENTRAS";
	Tabla[17]="HACER";
	Tabla[18]="PARA";
	Tabla[19]="SUBIR";
	Tabla[20]="BAJAR";
	Tabla[21]="=";
	Tabla[22]="==";
	Tabla[23]=">";
	Tabla[24]=">=";
	Tabla[25]="!=";
	Tabla[26]="<";
	Tabla[27]="<=";
	Tabla[28]="+";
	Tabla[29]="-";
	Tabla[30]="*";
	Tabla[31]="/";
	Tabla[32]=".";
	Tabla[33]=",";
	Tabla[34]=";";
	Tabla[35]="(";
	Tabla[36]=")";
}

void Analizador::LeerArchivo()
{
	FILE *Archivo;//se declara la palabra archivo
	Archivo=fopen("Pruebas.txt","r");//se abre el archivo en modo lectura
	if (Archivo == NULL)//en caso del que e,archivo se encuentre vacío o no exista 
	{
		cout<<"Error al abrir el archivo"<<endl;
		exit(0);//termina el programa
	}
	else
	{
		while (!feof(Archivo))//mientras que la linea no haya terminado 
		{
			Arch+=fgetc(Archivo);//obtiene caracter por caracter y los guaeda en Arch
		}
		fclose(Archivo);//cierro el archivo
	}
}

string Analizador::Token()
{
	string Cadena="";
	int X;
	
	//Palabras reservadas [A-Z]+ 
	X=(int) Arch[i];
	if ((X>=65)&&(X<=90))
	{
		Cadena+=Arch[i];
		i++;
		X=(int) Arch[i];
		while ((X>=65)&&(X<=90))
		{
			Cadena+=Arch[i];
			i++;
			X=(int) Arch[i];
		}
	}//Identificadores [a-z]([a-z]|[0-9])*
	else if ((X>=97)&&(X<=122))
	{
		Cadena+=Arch[i];
		i++;
		X=(int) Arch[i];
		while ((X>=48)&&(X<=57)||((X>=97)&&(X<=122)))
		{
			Cadena+=Arch[i];
			i++;
			X=(int) Arch[i];
		}
	}//Formar números [0-9]+(/.[0-9]+)*
	else if ((X>=48)&&(X<=57))
	{
		Cadena+=Arch[i];
		i++;
		X=(int) Arch[i];
		while ((X>=48)&&(X<=57))
		{
			Cadena+=Arch[i];
			i++;
			X=(int) Arch[i];
		}
		if (X==46)
		{
			if ((X>=48)&&(X<=57))
			{
				Cadena+=Arch[i];
				i++;
				X=(int) Arch[i];
				while ((X>=48)&&(X<=57))
				{
					Cadena+=Arch[i];
					i++;
					X=(int) Arch[i];
				}		
			}
			else
			{
				i--; //El punto no pertenece a la expresión porque no siguen números
			}
		}	
	}
	else if ((X==60)||(X==62)||(X==126)||(X==61))
	{
		Cadena+=Arch[i];
		i++;
		X=(int) Arch[i];
		if (X==61)
		{
			Cadena+=Arch[i];
			i++;
			X=(int) Arch[i];
		}
	}
	else
	{
			if ((X==32)||(X==13)||(X==10))
			{
				i++;
				return Token();
			}
			else
			{
			Cadena+=Arch[i];
			i++;
			X=(int) Arch[i];
			}
	}
	return Cadena;
}
bool Analizador::ValidarTabla(string Tok)
{
	int j;
	bool Band=false;
	for (j=0;j<=36;j++)
	{
		if (Tok.compare(Tabla[j])==0)
		{
			Band=true;
		}
	}
	if ((Band==false)&&(EsIdent(Tok)==false&&EsNum(Tok)==false))
	{
		Error(1,Tok);
	}
}

void Analizador::Error(int Tipo, string Tok)
{
	switch (Tipo)
	{
		case 1:
			cout<<"No es un simbolo valido: "<<Tok<<endl;
			break;
		default:
			cout<<"Error"<<endl;				
	}
}

bool Analizador::EsIdent(string Cadena)
{
	int j=0,X;
	
	X=(int) Cadena[j];
	if ((X>=97)&&(X<=122))
	{
		j++;
		X=(int) Cadena[j];
		while ((X>=97)&&(X<=122))
		{
			j++;
			X=(int) Cadena[j];
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool Analizador::EsNum(string Cadena)
{
	int j=0,X;
	X=(int) Cadena[j];
	if ((X>=48)&&(X<=57))
	{
		j++;
		X=(int) Cadena[j];
		while ((X>=48)&&(X<=57))
		{	
			j++;
			X=(int) Cadena[j];
		}
		if (X==46)
		{
			if ((X>=48)&&(X<=57))
			{
				j++;
				X=(int) Cadena[j];
				while ((X>=48)&&(X<=57))
				{
					j++;
					X=(int) Cadena[j];
				}		
				return true;
			}
			else
			{
				return false; //El punto no pertenece a la expresión porque no siguen números
			}
		}
	return true;
	}
}

int main(int argc, char** argv) {
	Analizador Obj1;
	string Tok;
	Obj1.LeerArchivo();
	
	Tok=Obj1.Token();
	Obj1.ValidarTabla(Tok);
	Tok=Obj1.Token();
	Obj1.ValidarTabla(Tok);
	Tok=Obj1.Token();
	Obj1.ValidarTabla(Tok);
	Tok=Obj1.Token();
	Obj1.ValidarTabla(Tok);
	return 0;
}
