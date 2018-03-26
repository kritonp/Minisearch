#include "trie.h"
#include "postingList.h"
#include "utils.h"

int main(int argc, char **argv){
	FILE *file;
	int i,K;
	char **array;
	char **backup;

	/*Command Line Arguments*/
	K = cmd_arguments(argc,argv);
	printf("topK = %d\n", K);
	
	/* Open File and Store Data to Memory */
	file = fopen(argv[2],"r");
	if (!file){
		perror("Error");
		return -1;
	}
	char *ln 		= NULL;            	/* NULL forces getline to allocate  */
	size_t n 		= 0;               	/* buf size, 0 use getline default  */
	ssize_t nchr 		= 0;           		/* number of chars actually read    */
	int index 		= 0;     		/* array index for number of lines  */
	int b_index 		= 0;
	size_t it 		= 0;              	/* general iterator variable        */
	size_t lmax 		= LMAX;         	/* current array pointer allocation */
	int max_length 	= 0,flag=0;
	if (!(array = calloc (LMAX, sizeof *array))) {
        fprintf (stderr, "error: memory allocation failed.");
        return 1;
    	}
	if (!(backup = calloc (LMAX, sizeof *backup))) {
	fprintf (stderr, "error: memory allocation failed.");
	return 1;
	}
	while ((nchr = getline (&ln, &n, file)) != -1){ /* read line    */  
	while (nchr > 0 && (ln[nchr-1] == '\n' || ln[nchr-1] == '\r'))
	    ln[--nchr] = 0;     /* strip newline or carriage rtn    */
	//Skip empty lines
	if (strcmp(ln,"\0") == 0){   
	    continue;
	}
	if(flag == 0){ 	//Get only the 1st line lenght 
		max_length = strlen(ln);
		flag = 1;
	}
	if(strlen(ln) > max_length){
		max_length = strlen(ln);
	}
	/* allocate & copy ln to array - this will create a block of memory
	   to hold each character in ln and copy the characters in ln to that
	   memory address. The address will then be stored in array[idx].
	   (idx++ just increases idx by 1 so it is ready for the next address) 
	   There is a lot going on in that simple: array[idx++] = strdup (ln);
	*/
	array[index++] 	  = strdup (ln);
	backup[b_index++] = strdup (ln);
	if (index == lmax) {      /* if lmax lines reached, realloc   */
	    char **tmp  = realloc (array, lmax * 2 * sizeof *array);
	    char **temp = realloc (backup, lmax * 2 * sizeof *backup);
	    if (!tmp)
		return -1;
	    array 	= tmp;
	    backup 	= temp;
	    lmax *= 2;
	}

	}
	fclose(file);        	/* close file */
	if (ln) free (ln);      /* free memory allocated to ln  */

	printf("Document Queries:\t %d\n", index);
	printf("Stored in Memory\t[DONE]\n");
	
	/* Print Array of Queries */
	//print_array(backup,index);		

	/* Initialize Trie */
	struct Trie* trie;
    	trie = initTrie();

   	 /* Parsing the Queries */
	parsing(array,index,trie,max_length);			

	/* Check if ids are consecutive */
	consecutivity(array,index);		

	/* Get User Commands */
	int res;
	while(1){
		res = get_input(trie,index,backup,K,max_length);
		if(res == -1)
			break;
	}

	/* Free Structs */
	destroyTrie(trie);
	for(i = 0; i < index; i++){
	    free(*(array+i));
	    free(*(backup+i));
	}
	free(array);
	free(backup);
	printf("Memory Freed\t\t[DONE]\n");

	return 0;
}
