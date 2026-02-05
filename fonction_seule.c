#include <stdio.h>
#include <stdbool.h>
#include <string.h>


//*vvvvvvvvv si envie de copier la fonction printstack dans un autre programme, inclure les variables depuis ici
const char* grey = "\033[90m";
const char* bk = "\033[30m";
const char* red = "\033[91m";
const char* blue = "\033[34m";
const char* yel = "\033[93m";
const char* cy = "\033[96m";
const char* mg = "\033[95m";
const char* def = "\033[0m";

// variables à changer pour changer la longueur imprimée par printStack (ou via mode 'x')
int xPTR = 25; 
int yPTR = 40;
/**
 * modes : 
 * v = verbose (imprime les adresses de debut et de fin)
 * n = nothing (n'imprime pas de retour ligne)
 * x = demande deux ints via scanf pour définir les marges "avant pointeur début - après pointeur fin" globales xPTR et yPTR
 * q = demande deux ints via scanf pour définir les marges une fois, pour une impression (variables locales a printstack iPTR et jPTR)
*/
void printStack(char* from_ptr, char* to_ptr, const char* ZERO_CHAR, const char* ZERO_COLOR, char* mode)
{	
	int iPTR = 0;
	int jPTR = 0;
	if (mode[0] == 'q' || mode[0] == 'x')
	{	
		printf("%s menu printStack, adresses : from_ptr=%p et to_ptr=%p. \n %s", grey, (void*)from_ptr, (void*)to_ptr, def);
		switch(mode[0])
		{
			//case 'q': printf("Merci d'entrer le décallage depuis from_ptr et to_ptr pour le prochain stackprint\n"); break;
			case 'x': printf("Merci d'entrer deux décalages (char) xPTR et yPTR pour tout le programme\n"); break;
		}
		//printf("(rappel : c'est illégal dans un programme fini, là c'est pour apprendre)\n");
		printf("format : > x,y \n>");
		int limits[2];
		if (scanf(" %d,%d", limits, limits+1) != 2) printf("erreur. je change rien.");
		else 
		switch(mode[0])
		{
			case 'q': iPTR = limits[0]; jPTR = limits[1]; break;
			case 'x': 
			iPTR = xPTR+limits[0]; jPTR = -yPTR+limits[1];  //règle aussi i et jptr parce que les adresse sont déjà passées avec les premiers paramètres
			xPTR = -limits[0]; yPTR = limits[1];  
			 
			break;
		}
		//if (mode[1] != 0) mode[0] = mode[1]; //passe la lettre suivante si c'est pas la fin du paramètre.
		printf("\n\n");
	}


	unsigned char* pStart = ((unsigned char*)from_ptr + iPTR);
	unsigned char* pEnd = ((unsigned char*)to_ptr + jPTR);
	if (mode[0] == 'v')
	{
		printf("pStart %p \t", (void*)pStart);
		printf("pEnd %p \n", (void*)pEnd);
	}
	bool is0 = false;
	while (pStart<=pEnd)
	{	
		switch(*pStart)
		{
			case 0:
				if (!is0) {printf("%s", ZERO_COLOR); is0 = true;}
				printf("%s", ZERO_CHAR);
				break;
			case '\n' : printf("%c", *pStart); break;
			default:
				if (is0) {printf("%s", def); is0 = false;}
				if(*pStart < 32) printf("%s%2X%s", cy, (int)*pStart, def);
				else if(*pStart > 127) printf("%s%2x%s", mg, (int)*pStart, def);
				else printf("%c", *pStart);
				break;
		}
		pStart++;
		//uintptr_t pdist[2] = {(uintptr_t)pStart-(uintptr_t)ptr, (uintptr_t)ptr - (uintptr_t)pStart};
		//if (pdist[0]<=1 || pdist[1]<1) printf("%s_._%s",red,def);
		//if (pdist[0]<=3 || pdist[1]<3) printf("   ");
		//else if (pdist[0]<=5 || pdist[1]<=5) printf(" ");
	}
	printf("%s", def);
	if(mode[0] != 'n') printf("\n");
}
//* FIN DE LA FONCTION PRINTSTACK ET DEBUT DU CODE MODIFIE

// code de main non testé, avec du bol ça marche en copiant collant
int main(int argc, char* argv[])
{
    
  char* string_storage = "bienvenue chez les chaines de caractere !";
		printStack(&string_storage[0], &string_storage[strlen(string_storage)], ".", yel, "q"); 
			printf("\n");
  if (argc>1)
  {
  char* str = argv[1];
  char* word = argv[argc];
  
      printf("\n\nIMPRIMER AUTOUR DE ARGV, entrer décalage avant argv[0] et après argv[2] (conseil : au moins -60,120 )\n");
		printStack((char*)str, (char*)word + strlen(word), "\\0", yel, "q"); //imprime scanf en demandant les offsets (0s en jaune)
		  printf("\n\nIMPRIMER AUTOUR DE pINDEX (finit dans main, mémoire arbitraire)\n");
		printStack((char*)pIndex, (char*)pIndex, "\\0", grey, "q"); // imprime le pointeur vers l'adresse pIndex dans main en demandant les offsets en plus
		  printf("\n\nVeux-tu imprimer toute la mémoire entre pIndex et argV (qui sont pas du tout au même endroit) ? y = oui\n\n");
		char buf[2] = {0};
		if (scanf(" %1[yY]", buf) == 1)
			printStack((char*)pIndex, (char*)word + strlen(word), "\\0", grey, "q"); // imprime du pointeur de main JUSQU'A la fin du mot :'D
		while (getchar() != '\n'); //vide le buffer
		printf("\n\n");
  }
  
}
