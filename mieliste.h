#include <stdlib.h>
#include <stdio.h>

typedef int TipoElemento;

typedef struct EL {
  TipoElemento info;
  struct EL * prox;
} ElemLista;

typedef ElemLista * ListaDiElem;

/*************************************************************
                        PROTOTIPI
*************************************************************/

ListaDiElem Inizializza( void );

int ListaVuota( ListaDiElem lista );

int Dimensione(ListaDiElem lista);
int DimensioneRic(ListaDiElem lista);

int VerificaPresenza (ListaDiElem lista, TipoElemento elem);
int VerificaPresenzaRic(ListaDiElem lista, TipoElemento elem);
int ContaOccorrenze (ListaDiElem lista, TipoElemento elem);
int ContaOccorrenzeRic(ListaDiElem lista, TipoElemento elem);

void VisualizzaLista( ListaDiElem lista );
void VisualizzaListaRovesciata( ListaDiElem lista );

ListaDiElem InsInTesta ( ListaDiElem lista, TipoElemento elem );
ListaDiElem InsInFondo( ListaDiElem lista, TipoElemento elem );
ListaDiElem InsInFondoRic( ListaDiElem lista, TipoElemento elem );
ListaDiElem InsInOrd( ListaDiElem lista, TipoElemento elem );
ListaDiElem InsInOrdRic( ListaDiElem lista, TipoElemento elem );

ListaDiElem CancellaUno( ListaDiElem lista, TipoElemento elem );
ListaDiElem CancellaUnoRic( ListaDiElem lista, TipoElemento elem );
ListaDiElem CancellaTutti( ListaDiElem lista, TipoElemento elem );
ListaDiElem CancellaTuttiRic( ListaDiElem lista, TipoElemento elem );

ListaDiElem EliminaDuplicati( ListaDiElem lista );
ListaDiElem EliminaDuplicatiRic( ListaDiElem lista );

ListaDiElem DistruggiLista( ListaDiElem lista );
void DistruggiListaRic( ListaDiElem lista );

ListaDiElem InvertiClonando( ListaDiElem lista, int keepSource );
ListaDiElem InvertiRiusando( ListaDiElem lista );
ListaDiElem InvertiRiusandoRic( ListaDiElem lista );

ListaDiElem OrdinaCrescente( ListaDiElem lista );
ListaDiElem OrdinaCrescenteRic( ListaDiElem lista );

ListaDiElem Inverti(ListaDiElem lista, ListaDiElem inversa);


/*** funzioni aggiuntive ***/

ListaDiElem CercaMin (ListaDiElem lista);
ListaDiElem Copia (ListaDiElem from);

void swap(TipoElemento *elem1, TipoElemento *elem2);
void Stampa(ListaDiElem lista);

/*************************************************************
                     IMPLEMENTAZIONE
*************************************************************/


void todo() {
    printf("\n\n\n ***********************************************\n");
    printf(" **                                           **\n");
    printf(" **     FUNZIONE NON ANCORA IMPLEMENTATA !    **\n");
    printf(" **                                           **\n");
    printf(" *******************************************\n\n\n ");
}

ListaDiElem Inizializza( void ) {
	return NULL;
}

int ListaVuota( ListaDiElem lista ) {
    return lista == NULL;
}

ListaDiElem InsInTesta ( ListaDiElem lista, TipoElemento elem ) {
	ListaDiElem punt;
	punt = (ListaDiElem) malloc(sizeof(ElemLista));
    punt->info = elem;
    punt->prox = lista;
	return  punt;
}

int Dimensione(ListaDiElem lista) {
	int count = 0;
	while( ! ListaVuota(lista) ) {
       lista = lista->prox;
       count++;
	}
	return count;
}

int DimensioneRic(ListaDiElem lista) {
  if( ListaVuota(lista) ) 
     return 0;
  return 1 + DimensioneRic(lista->prox);
}

int VerificaPresenza (ListaDiElem lista, TipoElemento elem) {
  while(!ListaVuota(lista))
      if(lista->info == elem)
          return 1;
      else
          lista = lista->prox;
  return 0; 
} 

int VerificaPresenzaRic(ListaDiElem lista, TipoElemento elem) {
    if(lista == NULL)
        return 0;
    if(lista->info == elem)
        return 1;
    else
        return VerificaPresenzaRic(lista->prox, elem);
}

int ContaOccorrenze( ListaDiElem lista, TipoElemento elem ) {
    int count = 0;
    while(!ListaVuota(lista)){
        if(lista->info == elem)
            count++;
        lista = lista->prox;
    }
  return count;
} 

int ContaOccorrenzeRic( ListaDiElem lista, TipoElemento elem ) {
    if(lista == NULL)
        return 0;
    if(lista->info == elem)
        return 1+ContaOccorrenzeRic(lista->prox, elem);
    else
        return ContaOccorrenzeRic(lista->prox, elem);
    
  return 0; 
}

ListaDiElem InsInFondo( ListaDiElem lista, TipoElemento elem ) {
    ListaDiElem punt, puntCor, puntPrec = NULL;
    puntCor = lista;
    while ( puntCor != NULL ) {
        puntPrec = puntCor;
        puntCor = puntCor->prox;
    }
    punt = (ListaDiElem) malloc(sizeof(ElemLista));
    punt->info = elem;
    punt->prox = puntCor;
    if( puntPrec == NULL )
        return punt;
    puntPrec->prox = punt;
    return lista;
}

ListaDiElem InsInFondoRic( ListaDiElem lista, TipoElemento elem ) {
    if(ListaVuota(lista))
        return InsInTesta(lista, elem);
    lista->prox = InsInFondoRic(lista->prox, elem);
    return lista;
}

ListaDiElem InsInOrd( ListaDiElem lista, TipoElemento elem ) {
    ListaDiElem punt, curr, prev;
    punt = (ListaDiElem)malloc(sizeof(ElemLista));
    punt->info = elem;
    punt->prox =  NULL;
    
    prev = curr = lista;
    while(!ListaVuota(curr) && curr->info < elem){
        prev = curr;
        curr = curr->prox;
    }
    punt->prox = curr;
    if(curr == lista)
        return punt;
    prev->prox = punt;
    return lista;
}

ListaDiElem InsInOrdRic( ListaDiElem lista, TipoElemento elem ) {	
  if(lista == NULL || lista->info >= elem)
      return InsInTesta(lista, elem);
    lista->prox = InsInOrdRic(lista->prox, elem);
  return lista; 
}


ListaDiElem CancellaUno( ListaDiElem lista, TipoElemento elem ) {
    ListaDiElem prec = lista, curr = lista;
    while(!ListaVuota(curr)){
        
        if(curr->info == elem){
            prec->prox = curr->prox;
            free(curr);
            if(curr==lista)
                return curr->prox;
            else
                return lista;
        }
        prec = curr;           
        curr = curr->prox;
    }
    return lista;
}

ListaDiElem CancellaUnoRic( ListaDiElem lista, TipoElemento elem ) {	
    ListaDiElem aux;
    if(!ListaVuota(lista)){
        if(lista->info == elem){
            aux = lista->prox;
            free(lista);
            return aux;
        }else
            lista->prox = CancellaUnoRic(lista->prox, elem);
    }
    return lista;
}

ListaDiElem CancellaTutti( ListaDiElem lista, TipoElemento elem ) {
    ListaDiElem listaOriginale = lista;
    while(!ListaVuota(lista)){
        
        if(listaOriginale->prox == NULL && listaOriginale->info == elem){
            free(listaOriginale);
            return NULL;}
        
        if(listaOriginale->info == elem)
            listaOriginale = listaOriginale->prox;
        
        lista = CancellaUno(lista, elem);
        
        if(lista->prox != NULL)
            lista = lista->prox;
        else
            return listaOriginale;
    }
    return listaOriginale;
}


ListaDiElem CancellaTuttiRic( ListaDiElem lista, TipoElemento elem ) {	
    ListaDiElem aux;
    if(!ListaVuota(lista)){
        if(lista->info == elem){
            aux = lista->prox;
            free(lista);
            lista->prox = CancellaTuttiRic(lista->prox, elem);
            return aux;
        }
        lista->prox = CancellaTuttiRic(lista->prox, elem);
    }
    return lista;
}


ListaDiElem DistruggiLista( ListaDiElem lista ) {
    ListaDiElem aux;
    while(!ListaVuota(lista)){
        aux = lista->prox;
        free(lista);
        lista = aux;
    }
    return NULL;
}

void DistruggiListaRic( ListaDiElem lista ) {
    if(!(ListaVuota(lista))){
        DistruggiListaRic(lista->prox);
        free(lista);
    }
}


void VisualizzaLista( ListaDiElem lista ) {
    if ( ListaVuota(lista) )
		printf(" --/\n");
    else if ( ListaVuota(lista->prox) )
		printf(" %d --/\n", lista->info);
    else {
    	printf(" %d -->", lista->info);
    	VisualizzaLista( lista->prox );
    }
}

void VisualizzaListaRovesciata( ListaDiElem lista ) {
    if ( ListaVuota(lista) )
		printf(" /-- ");
    else if ( ListaVuota(lista->prox) )
		printf(" /-- %d", lista->info);
    else {
    	VisualizzaListaRovesciata( lista->prox );
    	printf(" <-- %d", lista->info);
    }
}


ListaDiElem InvertiClonando( ListaDiElem lista, int keepSource ) {
    ListaDiElem lista2;
    lista2 = Inizializza();
    if(keepSource == 0)
        return lista = InvertiRiusando(lista);
    else
        return lista2 = Inverti(lista, lista2);
}


ListaDiElem InvertiRiusando( ListaDiElem lista ) {
  return lista = InvertiRiusandoRic(lista);
}


ListaDiElem InvertiRiusandoRic( ListaDiElem lista ) {
    ListaDiElem lista2;
    lista2 = Inizializza();
    lista = Inverti(lista, lista2);
    DistruggiListaRic(lista2);
    return lista; 
}


ListaDiElem OrdinaCrescente( ListaDiElem lista ) {
    int i;
    ListaDiElem ListaOriginale = lista;
    TipoElemento aux;
    for(i = Dimensione(lista); i > 1; i--){
        while(lista!= NULL && lista->prox != NULL){
            if(lista->info > lista->prox->info){
                aux = lista->info;
                lista->info = lista->prox->info;
                lista->prox->info = aux;
            }
        lista = lista->prox;
        }
    lista = ListaOriginale;
    }
  return ListaOriginale;
}


ListaDiElem OrdinaCrescenteRic( ListaDiElem lista ) {
    if(Dimensione(lista)>1){
        swap(&(lista->info), &((CercaMin(lista))->info));
        lista->prox = OrdinaCrescenteRic(lista->prox);
    }
    return lista;
}

ListaDiElem EliminaDuplicati( ListaDiElem lista ) {
    ListaDiElem lista2;
    lista2 = Inizializza();
    lista = OrdinaCrescente(lista);
    while(!ListaVuota(lista->prox)){
        if(lista->info != lista->prox->info){
           lista2 = InsInOrd(lista2, lista->info);
        }
        lista = lista->prox;
    }
    lista2 = InsInFondo(lista2, lista->info);
    DistruggiLista(lista);
    return lista2;
}

void swap(TipoElemento *elem1, TipoElemento *elem2){
    TipoElemento aux = *elem1;
    *elem1 = *elem2;
    *elem2 = aux;
}

ListaDiElem EliminaDuplicatiRic( ListaDiElem lista ) {
  if( ! ListaVuota(lista) )
    lista->prox = EliminaDuplicatiRic( CancellaTuttiRic( lista->prox, lista->info ) );
  return lista;
}

ListaDiElem Inverti(ListaDiElem lista, ListaDiElem inversa){
    if(ListaVuota(lista))
        return inversa;
    else{
        inversa = InsInTesta(inversa, lista->info);
        return inversa = Inverti(lista->prox, inversa);
    }
}

ListaDiElem CercaMin (ListaDiElem lista){
    ListaDiElem auxl = lista;
    TipoElemento auxt=0;
    if(lista == NULL)
        return NULL;
    else{
        
        auxt = lista->info;
        
        while(!ListaVuota(lista)){
            if(lista->info < auxt){
                auxt = lista->info;
                auxl = lista;
            }
            lista = lista->prox;
        }
        return auxl;
    }
}

void Stampa(ListaDiElem lista){
    if(!lista)
        return;
    
    printf("%d ", lista->info);
    return Stampa(lista->prox);
}

ListaDiElem Copia (ListaDiElem from){
    ListaDiElem aux, to=NULL;
    aux = from;
    while(aux != NULL){
        
        to = InsInFondo(to, aux->info);
        aux = aux->prox;
    }
    return to;
}


