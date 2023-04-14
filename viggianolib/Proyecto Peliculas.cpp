#include"viggiano.h"
#include<stdio.h>
using namespace std;
using namespace vgg;
Str<> toCompare(const Str<>& str){
	Str<> new_str=str;
	new_str.strip();
	new_str.noExtraSpaces();
	new_str.lower();
	return new_str;
}
struct Pelicula{
    private:
        Str<> nombre;
        Str<> director;
        Str<> genero;
	    unsigned short anio;
	    unsigned short horas;
	    unsigned short minutos;
	    int votos;
    public:
        Pelicula():votos(0){}
        void get(){
            printf("Ingrese el director\n>>> ");
            getstr(director);
			director.strip();
			director.noExtraSpaces();
            printf("Ingrese el genero\n>>> ");
            getstr(genero);
			genero.strip();
			genero.noExtraSpaces();
            printf("Ingrese la duracion\n>>> ");
            scanf("%d",&horas);
			fflush(stdin);
			printf(">>> ");fflush(stdin);
			scanf("%d",&minutos);
		}
        void upvote(){
            votos++;
        }
        void downvote(){
            votos--;
        }
		Str<>& get_nombre(){
			return nombre;
		}
		bool operator==(Pelicula other){//		El operador == usado en Pelicula compara los nombres entre peliculas todo en minusculas y sin espacios de mas
			return toCompare(this->nombre)==toCompare(other.nombre);
		}
		bool operator>(Pelicula other){//		El operador > usado en Pelicula compara los votos entre peliculas
			return this->votos>other.votos;
		}
		bool operator<(Pelicula other){//		El operador < usado en Pelicula compara los votos entre peliculas
			return this->votos<other.votos;
		}
		friend short get_index_of(Str<> pelicula,const List<Pelicula>& lista){
			pelicula=toCompare(pelicula);
			for(int i=0;i<lista.len();i++){
				if(lista[i].nombre.lower_cpy()==pelicula/*.lower_cpy()*/)
					return i;
			}
			return -1;
		}
		Pelicula nombreEnMin(){
			Pelicula copia_minuscula=*this;
			copia_minuscula.nombre.lower();
			return copia_minuscula;
		}
};
void printMovies(const List<Pelicula>& lista){
	for(int i=0;i<lista.len();i++){
		cout<<i<<" - "<<lista[i].get_nombre()<<'.'<<endl;
	}
}
void menu(){
        printf("Ingrese una opcion: \n");
        printf("\t - 0 : Eliminar una pelicula\n");
		printf("\t - 1 : Agregar una nueva pelicula\n");
		printf("\t - 2 : Votar pelicula\n");
		printf("\t - 3 : Obtener el ranking de peliculas\n");
		printf("\t - 4 : Obtener el director de la mejor pelicula\n");
		printf("\t - 5 : Obtener el top 10 de peliculas de un genero\n");
		printf("\t - 6 : Obtener la mejor pelicula de un anio\n");
		printf("\t - 7 : Obtener la pelicula mas larga\n");
		printf("\t - 8 : Obtener la pelicula mas corta\n");
		printf("\t - 9 : Salir\n");
		
		puts("");
}
int main(){
	system("color 1e");
    List<Pelicula> listaDePeliculas;
    bool salir=0;
    int seleccion;
    while(not salir){
		menu();
        printf(">>> ");scanf("%d", &seleccion);
		system("cls");
		menu();
		fflush(stdin);
		switch(seleccion){
			case 0:{
				Str<> remover;
				printf("Ingrese el nombre de la pelicula que se quiere eliminar:\n>>> ");
				getstr(remover);
				short index=get_index_of(remover,listaDePeliculas);
				if(index>=0){
					listaDePeliculas.del(index);
					puts("Se elimino una pelicula correctamente.\n");				
				}
				else
					puts("No se encontro la pelicula");
				break;				
			}
            case 1:{
            	Pelicula nueva;
            	printf("Ingrese el nombre de la pelicula\n>>> ");
            	getstr(nueva.get_nombre());
				nueva.get_nombre().strip();
            	nueva.get_nombre().noExtraSpaces();
				if(listaDePeliculas.has(nueva)){
					puts("La pelicula que intenta agregar ya esta en la lista");
				}
				else{
					listaDePeliculas.append(nueva);
					nueva.get();
					puts("Se agrego una pelicula correctamente.\n");					
				}
			
				break;
			}
			case 2:{
				Str<> pelicula;
				printf("Que pelicula quiere seleccionar?\n>>> ");
				getstr(pelicula);fflush(stdin);
				//pelicula=toCompare(pelicula);
				int index=get_index_of(pelicula,listaDePeliculas);
				if(index>=0){
					bool voto;
					printf("0 : Votar en contra\n1 : Votar a favor\n");
					cout<<">>> ";cin>>voto;
					if(voto){
						listaDePeliculas[index].upvote();
						cout<<"Se voto a favor de ";
						listaDePeliculas[index].get_nombre().print();
					}
					else{
						listaDePeliculas[index].downvote();
						cout<<"Se voto en contra de ";
						listaDePeliculas[index].get_nombre().print();
					}
				}
				else
					puts("\aNo se encontro la pelicula");			
				break;				
			}
			case 3:{
				listaDePeliculas.sort(true);// reverse=true
				printMovies(listaDePeliculas);
				break;
			}
			case 4:{
				printBestDirector();
				break;
			}
			case 5:
				top10byGenre();
				break;
			case 6:
				bestMovieOfTheYear();
				break;
			case 7:
				longestFilm();
				break;
			case 8:
				shortestFilm();
				break;
			default:
				Finalizar();
				puts("FIN DEL PROGRAMA");
				salir=true;
				break;

        }
		system("pause");
        system("cls");
    }


}
