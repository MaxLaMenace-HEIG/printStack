// Programme strutil
// Rosselet-Christ Maxence

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


// Function Prototype
bool password_make(const char* word, char* pwd);
bool word_find(const char* str, const char* word, int* pIndex);

/**
 * strutil program - le programme retourne les 
 * @param[in] argc Number of argument passed
 * @param[in] argv Array of arguments (string)
 * @return 0 if succeed 
 */
int main(int argc, char* argv[])
{
	if (argc == 1) return 1;
	else //for (int i=1; i<=argc; i++)
	{	int i = 1;
		if (strncmp(argv[i], "--help", strlen("--help"))==0)
		{
			printf("Usage : ./strutil --find WORD STRING\n");
			printf("        ./strutil --pwd WORD\n");
			printf("        ./strutil [OPTIONS] \n");
			printf("Options : notime\n");
			return 0;
		}
		else if (strncmp(argv[i], "--version", strlen("--version"))==0)
		{
			printf("Programme strutil version 1.0.0 maxence.rosselet-christ@heig-vd.ch\n");
			return 0;
		}
		else if (strncmp(argv[i], "--strings", strlen("--strings"))==0)
		{
			char* string_storage = "bienvenue chez les chaines de caractere !";
			printStack(&string_storage[0], &string_storage[strlen(string_storage)], ".", yel, "q"); 
			printf("\n");
			return 0;
		}
		else if (strncmp(argv[i], "--find", strlen("--find"))==0)
			if (argc < 4) return 3; 
			else
		{	
			int foundIdx = -1;
			if (word_find(argv[2], argv[3], &foundIdx)) 
			{
				printf("%d\n", foundIdx);
				return 0;
			} else return 3;
		}
		else if (strncmp(argv[i], "--pwd", strlen("--pwd"))==0)
			if (argc < 3) return 2;
			else
		{	

			//char pwd[101] = {0}; // 100+1, précaution \0
			char pwd[30] = {0}; 

				int len = strlen(argv[2]); //longueur du mot de passe
				printStack(&pwd[-xPTR], &pwd[len+yPTR], "0", yel, "x"); printf("\n"); //<- j'ai défini "x" comme 'demande le réglage du décalage pour tout le programme
				//^^imprime les limites entre les adresses avant strcopy.
			
			//strncpy(pwd, argv[2],100);
			strcpy(pwd, argv[2]);
			
				printStack(&pwd[-xPTR], &pwd[len+yPTR], "0", yel, "v"); printf("\n"); //imprime les limites entre les adresses après strcopy.
			/*^^^ version pas safe du code commenté - buffer relativement court, sans limite de copie.
			strcpy VA copier argv[2] dans buffer, peu importe si argv[2] fait dix fois la taille de buffer :D
			*/
			return (password_make(argv[2], pwd)) ? 0 : 2 ;
		}

		
	}

	return 0;
}


/**
 * Generates a new password by replacing characters to increase security.
 * [o,O] [B] [e,E]
 * 	[0]  [8]  [3]
 * @param[in] word Word to modify
 * @param[inout] pwd Modified word (must be same strlen() as word when called)
 * @return True if succeeded
 */
bool password_make(const char* word, char* pwd)
{		

	if(!pwd || !word) return false;
	size_t len = strlen(pwd);
	if(!len) return false;
	if(len != strlen(word)) return false; //condition added to ensure the write field is long enough

	//*vvvvvvvvvvvv stack print ici
	for (int i=0; i<(int)strlen(pwd); i++) 
	{	
		//xptr, yptr variables globales
		printStack(&pwd[-xPTR], &pwd[i-1], "\\0", grey, "n"); 
		//^^imprime les octets de xPTR adresses avant le pointeur pwd jusqu'à l'adresse avant pwd[i], en formattant les 0 comme des "\0" gris
		printf("%s%c%s", red, pwd[i], def); 
		//^^imprime le caractère que traite la boucle (pwd[i]) en rouge
		printStack(&pwd[i+1], &pwd[len+yPTR], "\\0", grey, "n"); printf("\n");
		//^^imprime les adresses de pwd[i+1] à yPTR octets (chars) après la fin du mot de passe, format 0 identique

		switch (word[i])
		{
			case 'o': case 'O':
				pwd[i] = '0';
				break;
			case 'B':
				pwd[i] = '8';
				break;
			case 'e': case 'E':
				pwd[i] = '3';
				break;
			case 's': case 'S':
				pwd[i] = '5';
				break;
		}
	}
	printf("%s\n", pwd);

	return true;
}

/**
 * Finds the position of a word in a character string. Returns -1 if not found
 * @bug : doesn't work with the first word :c WAIT IT DOES
 * @param[in] str char string to loop through
 * @param[in] word word to find
 * @param[inout] pIndex pointer to an int index
 * @return True if succeeded
 */
bool word_find(const char* str, const char* word, int* pIndex)
{	
	if(!str || !word || !pIndex) return false;
	int slen = strlen(str);
	int wlen = strlen(word);
	if(!slen||!wlen) return false;

		int i=0;
		int idx=0;
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



	while (i<slen)
	{
		if ((i==0)||(str[i] == ' ')) //loops through the word's spaces to run stringcompares
		{
			idx++; 
			if(i!=0)i++;
			if(strncmp(&str[i], word, wlen) == 0)
			{	
				*pIndex = idx;
				printf("%s is the %d word !\n", word, idx);
				printf("%s\n", str);
				printf("%*c\n", i+1, '^');
				return true;
			}
		}
		i++;
	}

	printf("%s not found\n", word);
	*pIndex = -1;
	return true;
}


