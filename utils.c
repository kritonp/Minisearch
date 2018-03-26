#include "utils.h"


struct topK{
	int   id;
	float score;
};


int compare(const void *a, const void *b){
	struct topK *e1 = (struct topK *)a;
	struct topK *e2 = (struct topK *)b;
	return e1->score < e2->score;
}

int get_input(struct Trie* trie,int index,char **backup,int K,int line_lenght){
	char input[1024]; 
	struct topK topKs[index];
	printf("Type a Command: \n");
	fgets(input,sizeof(input),stdin);
	input[strlen(input)-1] = '\0';     

	if(strcmp(input,"/exit") == 0){
		return -1;
	}else if(strcmp(input,"/df") == 0){
		printTrie(trie);
	}else{
		char* arguments;
		char* command;

		command = strtok(input, " ");
		if (strcmp(command,"/df") == 0){	//eg: >/df leaped
			struct postingList* pL;
			while ((arguments = strtok(NULL, " ")) != NULL){
				break;	//it only gets the first word after /df command
			}

			if((pL = search(trie, arguments) )!= NULL){
				printf("%s %d\n", arguments,get_freq(pL));

			}else{
				printf("%s %d\n", arguments,0);
			}
			
		}else if(strcmp(command,"/search") == 0){
			int k,flag = 0; //I only need the first ten queries
			char queries[10][512];
			while ((arguments = strtok(NULL, " ")) != NULL){
				flag++;
				strcpy(queries[flag] , arguments);				

				if (flag==10)
					break;	
			}

			int mac=0;
			struct postingList* pL;
			int xx,id,frequency,i,num,pid,amount_docs,w=0;
			float score=0.0,avgdl,IDF;
			double temp_value;
		    printf("Total Words: %d\n", get_total_words(trie));
		    avgdl = get_total_words(trie)/ index; 				
		    
			for(i = 0; i < index; i++){	
		 	    temp_value 	= 0;
		 	    IDF 		= 0;
		 	    score 		= 0;
		 	    for(k=1;k<=flag;k++){

					if((pL = search(trie, queries[k]) )!= NULL){
				        xx = get_list_data(pL,&id,&frequency);				
				        
				        if(xx == -1)
				        	break;
				        num 		= get_numWords(id,backup,line_lenght); 	//get: How many words does the query(id) have
				        temp_value 	= (index - get_freq(pL) + 0.5) / (get_freq(pL) + 0.5);
						IDF 		= log(temp_value);
				        score = score + IDF*( (frequency * (2.2)) / (frequency + 1.2*(1 - 0.75 + (0.75 * num)/avgdl)));
				        mac++;	//How many docs has the searced words
					}//end if

				}//end for
		  		topKs[w].id    = id;
				topKs[w].score = score;	//score for every document
				w++;
			}//end for
			/* Sort Documents by id */
			qsort(topKs, w, sizeof(struct topK), compare);	

			/* Pretty Print Results */
			if(mac < K){
				K = mac;
			}
			int ls,mikos;
			char *taken;
   			char dems[] = "  \t";
   			struct winsize wsize;
   			ioctl(STDOUT_FILENO, TIOCGWINSZ, &wsize);
   			char temp[line_lenght];

			for(k = 0; k < K; k++){
				strcpy(temp,"");			//1
				strcpy(temp,backup[topKs[k].id]);	//2
				taken = strtok(temp,dems);		//3

				mikos = 0;
				printf("( %d) [%.3f] ",topKs[k].id,topKs[k].score);
				int scoreDigits,bypass=0,tempLenght=0;
				scoreDigits = floor(log10(abs(topKs[k].id))) + 1;

				ls = 12 + scoreDigits;
				int lx = ls;
				int flagger = 0,mikos_lexis=0,big_space=0;
				while(taken != NULL){
					if(flagger==1){

						for(i=1;i<flag+1;i++){	//for every search query word
							if(strcmp(taken,queries[i])==0){
									bypass = 1;
									tempLenght = mikos + strlen(taken)+ls+lx;
									mikos_lexis = strlen(taken);
									//break;
							}
						}
						if(mikos + strlen(taken) >= wsize.ws_col - lx - ls){
							printf("\n");
							if(bypass==1){
								int kr;
								for(kr = 0; kr < tempLenght-mikos_lexis; kr++){
									printf(" ");
								}
								for(kr = 0; kr < mikos_lexis; kr++){
									printf("^");
								}
								printf("\n");
								bypass=0;
								tempLenght = 0;
							}
							for(int m =0; m < lx ;m++){
								printf(" ");

							}

							ls = 0;
							mikos = 0;
						}

						mikos = strlen(taken) + mikos +1;
						printf("%s ", taken);
					}
					flagger = 1;
					taken = strtok(NULL, dems);

				}
				printf("\n");
			}
			printf("printed results: %d\n", K);
		}else if(strcmp(command,"/tf") == 0){
			int stop=0,given_id,i,id,frequency,xx;
			char word[12];
			char queri[1][12];
			struct postingList* pL;

			while ((arguments = strtok(NULL, " ")) != NULL){
				stop++;
				if(stop==1){
					given_id = atoi(arguments);
					if(given_id >= index){
						printf("There is not such id %d\n",given_id);
						printf("Type a valid id between [0,%d]\n",index-1 );
						return -1;
					}
				}
				if(stop == 2){
					strcpy(word,arguments);
					break;	//it only gets the very first word after /tf command
				}
			}//end while 
			if(arguments==NULL){
				printf("Missing arguments\n");
				printf("Example: /tf 0 lazy\n");
				return -1;
			}
			/*		A'TROPOS				*/
			/*		Find pL through trie			*/
			/*
			if((pL = search(trie, word) )!= NULL){
				for(i = 0; i < index; i++){
			        xx = get_list_data(pL,&id,&frequency);
			        //printf("[id: %d], [freq: %d]\n", id, frequency);

			        if(xx == -1)break;
			        if(id == given_id){
			        	printf("%d %s %d\n", given_id, word, frequency);
			        	break;
			        }
			    }
			}
			*/

			/* 		B TROPOS 				*/
			/* 		Find words from the array[id]		*/
			
			int term = 0;
			char *token;
			char tmp_token[line_lenght+1];
			strcpy(tmp_token,"");
			strcpy(tmp_token,backup[given_id]);

			char delims[] = "  \t";
			token = strtok(tmp_token,delims);
			while(token != NULL){
				if(strcmp(word,token)==0){
					term++;
				}

				token = strtok(NULL, delims);
			}
			printf("%d %s %d\n", given_id, word, term);
			

		}else if(strcmp(command,"/help") == 0){
			printf("1. /search q1 q2 ... q10\n");
			printf("2. /df\n");
			printf("3. /df word\n");
			printf("4. /tf doc_id word\n");
			printf("5. /exit\n");
		}
		else{
			printf("Error: Command %s not found\n", command);
			return -1;
		}


	}

	return 0;
}

int consecutivity(char **array,int index){
	printf("Check Consecutivity\t[DONE]\n");
   	int i,id[index];
   	char *token; 
   	/* Get the id's and store them in an array */
   	for(i=0; i<index; i++){
		token = strtok(array[i], " ");
		id[i] = atoi(token);
		if(i == 0 && id[0] !=0 ){
			printf("First id should be equal to zero, not equal to %d\n",id[0]);
			exit(-1);
		}
   	}
   	/* Check consecutivity of id's */
 	for (int i = 0; i < index - 1; ++i){
   		if(id[i] + 1 != id[i+1]){
   			printf("Error: ID's are not consecutivies %d, %d\n", id[i],id[i+1]);
   			exit(-1);
   		}
   	}


	return 0;
}

int parsing(char **array, int index, struct Trie* trie, int line_len ){//index = grammes pinaka
	printf("Parsing Data\t\t[DONE]\n");
   	int i,j=0;
   	char *token;
   	char delims[] = "  \t";
   	char temp[line_len+1];

   	for(i=0; i<index; i++){
   		strcpy(temp,"");
   		strcpy(temp,array[i]);
   		token = strtok(temp,delims);

		j=0;
		while(token != NULL){
			j++;	//j represents the wordCount
			if(j>1){
				/* Insert word to trie */
				pushTrie(trie,token,i);	//i := id
			}
			token = strtok(NULL, delims);
		}
   	}
 
	return 0;
}

int print_array(char **array,int index){
	int i;
	for(i=0;i<index;i++){
		printf("%s\n", array[i]);
	}
}

int cmd_arguments(int argc,char* argv[]){
	if (argc < 3){
		printf("Error: Missing Arguments\n");
		exit(-1);
	}else if(argc == 3){
		//printf("Default K = 10\n");
		return 10;
	}else if(argc == 4){
		printf("Error: Missing Argument\n");
		exit(-1);
	}else if(argc > 5){
		printf("too many arguments\n");
		exit(-1);
	}else if(argc == 5){
		if (strcmp (argv[3],"-k") != 0){
			printf("%s command doesn't exists\n", argv[3]);
			exit(-1);
		}
		if (strcmp (argv[3],"-k") == 0){
			return 	atoi(argv[4]);
		}
	}
	if (strcmp (argv[1],"-i") != 0){
		if(strcmp (argv[1],"-k") == 0){
			printf("You have to give an input file first\n");
			exit(-1);
		}
		printf("%s command doesn't exists\n", argv[1]);
		exit(-1);
	}
	return 0;
}


int get_numWords(int id,char** array,int line_lenght){
	int wordCount = -1;
	char *token;
	char tmp[line_lenght];
	strcpy(tmp,"");
	strcpy(tmp,array[id]);
   	char delims[] = "  \t";

	token = strtok(tmp, delims);
	while(token != NULL){
		wordCount++;
		token = strtok(NULL, delims);

	}
	strcpy(tmp,"");

	return wordCount;
}

