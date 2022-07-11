
//Project Overview: The program goes through song lyrics and analyses the song with a build in dictionary.
//					As an example: It takes a line at a time an analyses it. 
//					Lyrics: "I'm no hero, I'm not made of stone"  (Wrong Side of Heaven by Five Finger Death Punch)
//					The first line: "I'm no hero" The word "hero" has a flat meaning (hero means hero) then the word "no"
//					is a negation on the word hero. Therefore the first line means "Villain".
//					The second line: "I'm not made of stone" The word "stone" means invincible. There is another negation,
//					this time it applies to stone. Therefore the second line means "Broken".
//					From the lyrics, the program has derived the meaning of these two lines as "Villain" and "Broken".
//					Yet this program is only good as the dictionary provided. And the English language is complicated
//					and would need more time to further the scope of this program. 

#include <stdio.h>
#include <string.h>
FILE *f1;
typedef struct{
	char def1[20],def2[20], def3[20];
}Meaning;

typedef struct{
		char word[20];
		Meaning def;	
}Definition;

Definition createWord(char[128]);
Meaning dictionaryLookup(char[100]);
Meaning AntLookup(char[100]);
Analyzer(int , char[100][100]);
Definition normalWords[50];
Definition personWords[50];
Definition negationWords[50];
Definition adjWords[50];
Definition antonymWords[50];
Definition IgnoreWords[50];
char songLine[100][100];
int moodCounter= 0;
char anaLine[100][100];
char mood[100][100];
int tally[30]={0};
int songLineCounter = 0;
int ana = 0;
int normal =0;
int person = 0;
int adj = 0;
int neg = 0;
int ant = 0;
int ign = 0;
int wordcounter = 0;
int DeepScan = 0;

//Main program, starts menus
int main(){
	readDictionary();
	int songchoice, choice;
	printf("Welcome to song analyizer. Which song would you like to analyze?\n");
	printf("\t1. Craddle To The Grave - Five Finger Death Punch\n");
	printf("\t2. Walking on Sunshine - Katrina & The Waves\n");
	printf("\t3. The Grey - Icon For Hire\n");
	printf("\t4. This Means War - Avenged Sevenfold\n");
	printf("\t5. The High Road - Three Days Grace\n");
	printf("\t6. Call Me - Shinedown\n");
	printf("\t7. Down With The Sickness - Disturbed\n");
	printf("\t8. Remember Everything - Five Finger Death Punch\n");
	printf("\t9. View the disclaimer for this program.\n");
	scanf("%d", &songchoice);
	switch(songchoice){
			case 1:
				printf("You have selected: 'Craddle To The Grave by Five Finger Death Punch'! What would you like to do?\n");
				FileHandler(songchoice);
				MenuCall();
				break;
			case 2:
				printf("You have selected: 'Walking on Sunshine by Katrina & The Waves'! What would you like to do?\n");
				FileHandler(songchoice);
				MenuCall();
				break;
			case 3:
				printf("You have selected: 'The Grey by Icon For Hire'! What would you like to do?\n");
				FileHandler(songchoice);
				MenuCall();
				break;
			case 4:
				printf("You have selected: 'This Means War by Avenged Sevenfold'! What would you like to do?\n");
				FileHandler(songchoice);
				MenuCall();
				break;
			case 5:
				printf("You have selected: 'The High Road by Three Days Grace'! What would you like to do?\n");
				FileHandler(songchoice);
				MenuCall();
				break;
			case 6:
				printf("You have selected: 'Call Me by Shinedown'! What would you like to do?\n");
				FileHandler(songchoice);
				MenuCall();
				break;
			case 7:
				printf("You have selected: 'Down With The Sickness by Disturbed'! What would you like to do?\n");
				FileHandler(songchoice);
				MenuCall();
				break;
			case 8:
				printf("You have selected: 'Remember Everything by Five Finger Death Punch'! What would you like to do?\n");
				FileHandler(songchoice);
				MenuCall();
				break;
			case 9:
				Disclaimer();
				break;
	}
	 printf("Goodbye!\n");
}
//Opens the files for reading
FileHandler(int song){
	if(song == 1){
		f1= fopen("CTTG.txt","r+");
	}else if(song == 2){
		f1= fopen("WOS.txt","r+");
	}else if(song == 3){
		f1= fopen("TG.txt","r+");
	}else if(song == 4){
		f1= fopen("TMW.txt","r+");
	}else if(song == 5){
		f1= fopen("THR.txt","r+");
	}else if(song == 6){
		f1= fopen("CM.txt","r+");
	}else if(song == 7){
		f1= fopen("DWTS.txt","r+");
	}else if(song == 8){
		f1= fopen("RE.txt","r+");
	}if(f1 == NULL){
		printf("File is not found :(\n");
		return -1;
	}
}
//Disclaimer for the program
Disclaimer(){
	printf("\nI do not own any of rights of the songs that are being analyzed within this program.\n");
	printf("All rights go to their respected artists, which is indicated above.\n\n");
}
//Breaks each line up to be dealt with
LineHandler(){
	printf("Reading File...\n\n");
	sleep(1);
	char line [128];
	while ( fgets ( line, sizeof line, f1 ) != NULL ){
		int i=0;
		while(line[i] != '\n'){
			if(line[i] == ' '){	
				wordcounter++;
			}
			i++;
		}
		WordHandler(line);
		Analyzer(ana,anaLine);
		wordcounter =0;
		ana =0;
		
	}
		Tally();
}
//Breaks each word up in the line to be dealt with
WordHandler(char line[128]){
		int k=0;
		char *word= strtok(line," ");
   		while (word != NULL){
			strcpy(songLine[k],word);
			k++;
        		word = strtok(NULL, " ");
  		} 
}
//Analyzes the line, with dictionary calls
Analyzer(int ana, char anaLine[100][100]){
	if(ana==0){
		int i;
		for(i=0;i<wordcounter;i++){
			Meaning def = dictionaryLookup(songLine[i]);
			if(strcmp(def.def1,"\0")!=0){
				strcpy(anaLine[ana],def.def1);
				ana++;
			}
		}
		if(ana!=0)
			Analyzer(ana,anaLine);
	}else{	
		char tempLine[100][100];
		int tempana =0;
		int i;
		for(i=0;i<ana;i++){
			if(strcmp(anaLine[i],"person") == 0 ){
				strcpy(tempLine[tempana],"person");
				tempana++;
			}
			if(strcmp(anaLine[i],"neg") == 0){
				if(strcmp(anaLine[i+1],"person") != 0 && strcmp(anaLine[i+1],"neg") != 0 && strcmp(anaLine[i+1],"\0") != 0){
					Meaning def = AntLookup(anaLine[i+1]);
					if(strcmp(def.def1,"\0")!=0){
						strcpy(tempLine[tempana],def.def1);
						tempana++;
					}	
				}
				else if(strcmp(anaLine[i-1],"person") != 0 && strcmp(anaLine[i-1],"neg") != 0 && strcmp(anaLine[i-1],"\0") != 0){
					Meaning def = AntLookup(anaLine[i-1]);
					if(strcmp(def.def1,"\0")!=0){
						strcpy(tempLine[tempana],def.def1);
						tempana++;
					}
				}
			}
			if(strcmp(anaLine[i],"person") != 0 && strcmp(anaLine[i],"neg") != 0 && strcmp(anaLine[i],"\0") != 0){
				int q;
				for(q=0;q<ana;q++){
					if(strcmp(anaLine[q],"person") != 0 && strcmp(anaLine[q],"neg") != 0 && strcmp(anaLine[q],"\0") != 0 && i!=q)
						break;
					if(strcmp(anaLine[q],"neg") == 0)
						break;
					if(q+1==ana){
						strcpy(tempLine[tempana],anaLine[i]);
						tempana++;
					}
				}
			}
		}
		int x;
		int wcounter = 0;
		int word=-1;
		for(x=0;x<tempana;x++){
			if(strcmp(tempLine[x],"neg") == 0){
				break;
			}
			if(strcmp(tempLine[x],"person") != 0 && strcmp(tempLine[x],"neg") != 0){
				if(word == -1){
					wcounter++;
					word = x;
				}else{
					if(strcmp(tempLine[x],tempLine[word]) != 0){
						break;
					}
				}					
			}
			if(x+1==tempana){
				int f;
				for(f=0;f<tempana;f++){
					if(strcmp(tempLine[f],"person") != 0 && strcmp(tempLine[f],"neg") != 0){
						Meaning def = dictionaryLookup(tempLine[f]);
						if(strcmp(def.def1,"\0")!=0){
							int v;
							int copy = 0;
							for(v=0;v<moodCounter;v++){
								if(strcmp(mood[v],def.def1)==0){
									tally[v]++;
									copy=1;
								}
							}
							if(copy==0){
								strcpy(mood[moodCounter],def.def1);
								moodCounter++;
								tally[moodCounter]=1;
							}
							
							return;
						}
					}
				}
			}
		}	
	}	

}
//Prints stats
Tally(){
	int c;
	int largest=0;
	int index;
	for(c=0;c<moodCounter;c++){
		if(tally[c]>largest){
			largest = tally[c];
			index= c;
		}
	}
	if(DeepScan==1){	
		printf("\nThe entire list of the moods where is follows: \n");
		printMood();
	}
	if(largest!=0){
		printf("\n");
		printf("The mood of the song is: %s appears %d times.\n",mood[index],largest);
		printf("The reason for this is because %s had the largest percent of the mood of the song.\n\n", mood[index]);
	}else{
		printf("There was not enough information within the dictionary to provide a mood.\n");
	}
}
//Prints every lines mood
printMood(){
	if(tally[0]==0){
		tally[0]=1;
	}
	int i;
	for(i=0;i<moodCounter;i++){
		printf("%s %d times\n",mood[i],tally[i]);
	}
	printf("\n");
}
//Prints the file that is open
printLyrics(){
	char line [128];
	while ( fgets ( line, sizeof line, f1 ) != NULL ){
			printf("%s",line);	
	}
}
//Second menu
MenuCall(){
		int choice;				
		printf("1. Print Lyrics.\n");
		printf("2. Analyze Song (Surface Scan)\n");
		printf("3. Analyze Song (Deep Scan)\n");
		scanf("%d", &choice);
		switch(choice){
			case 1:
				printLyrics();
				break;
			case 2: 
				LineHandler();
				break;
			case 3:
				DeepScan =1;
				LineHandler();
				break;
			default:
				break;
				}
}
//Reads the dictionary file then adds it to memory
readDictionary(){
	FILE *f2 = fopen("dictionary.txt","r+");
	if(f2 == NULL){
		printf("Dictionary Not Found :(\n");
		return -1;
	}
	int counter = 0;
	char line [128];
	while ( fgets ( line, sizeof line, f2 ) != NULL ){
		if(strcmp(line,"---\n")==0){
			counter++;
		}else if(counter == 1){
    			normalWords[normal] = createWord(line);
			normal++;
		}else if(counter == 2){
    			personWords[person] = createWord(line);
			person++;
		}else if(counter == 3){
    			negationWords[neg] = createWord(line);
			neg++;
		}else if(counter == 4){
    			adjWords[adj] = createWord(line);
			adj++;
		}else if(counter == 5){
    			antonymWords[ant] = createWord(line);
			ant++;
		}else if(counter == 6){
			IgnoreWords[ign] = createWord(line);
			ign++;
		}
	}
}
//creates a word from the dictionary
Definition createWord(char line[128]){
			char *word;
			Definition webster;
			Meaning def;
    			word = strtok(line, "-");
    			strcpy(webster.word,word);
			//printf("%s\n",word);
    			word = strtok (NULL, ",");
			strcpy(def.def1,word);
			word = strtok (NULL, ",");
			strcpy(def.def2,word);
			word = strtok (NULL, ",");
			word[strlen(word)-1] = 0;
			strcpy(def.def3,word);
			webster.def = def;
			return webster;
}
//Looks up (from memory) the word, to make sure that it is part of the dictionary
Meaning dictionaryLookup(char word[100]){
	int q,w,e,r,t,y;
	for(q=0;q<=normal;q++){
		//printf(".%s.\t.%s.\n",word,normalWords[q].word);
		if(strcmp(word,normalWords[q].word)==0){
			
			return normalWords[q].def;
		}
	}
	for(w=0;w<person;w++){
		if(strcmp(word,personWords[w].word)==0){
			Meaning def;
			strcpy(def.def1,"person");
			return def;
		}
	}
	for(e=0;e<neg;e++){
		if(strcmp(word,negationWords[e].word)==0){
			Meaning def;
			strcpy(def.def1,"neg");
			return def;
		}
	}
	for(r=0;r<adj;r++){
		if(strcmp(word,adjWords[r].word)==0){
			return adjWords[r].def;
		}			
	}
	for(t=0;t<ant;t++){
		if(strcmp(word,antonymWords[t].word)==0){
			return antonymWords[t].def;
		}
	}
	Meaning temp;
	strcpy(temp.def1,"\0");
	return temp;
}
//Finds antonym of given word
Meaning AntLookup(char word[100]){
	int t;
	for(t=0;t<ant;t++){
		if(strcmp(word,antonymWords[t].word)==0){
			return antonymWords[t].def;
		}
	}
	Meaning temp;
	strcpy(temp.def1,"\0");
	return temp;
}